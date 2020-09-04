#include "EpollPoller.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <sys/eventfd.h>


namespace zyh
{

//创建epoll监听描述符
int createEpollFd()
{
	int efd = ::epoll_create1(0);
	if(-1 == efd)
	{
		perror("epoll_create1 error");
		exit(EXIT_FAILURE);
	}
	return efd;
}

//创建eventfd描述符，用于IO线程和计算线程间通信
int createEventFd()
{
	int evtfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
	if(-1 == evtfd)
	{
		perror("eventfd create error");
	}
	return evtfd;
}

//添加监听读事件
void addEpollFdRead(int efd, int fd)
{
	struct epoll_event ev;
	ev.data.fd = fd;
	ev.events = EPOLLIN;
	int ret = epoll_ctl(efd, EPOLL_CTL_ADD, fd, &ev);
	if(-1 == ret)
	{
		perror("epoll_ctl add error");
		exit(EXIT_FAILURE);
	}
}

//删除监听读事件
void delEpollReadFd(int efd, int fd)
{
	struct epoll_event ev;
	ev.data.fd = fd;
	int ret = epoll_ctl(efd, EPOLL_CTL_DEL, fd, &ev);
	if(-1 == ret)
	{
		perror("epoll_ctl del error");
		exit(EXIT_FAILURE);
	}
}

//接收连接请求，返回建立连接的文件描述符
int acceptConnFd(int listenfd)
{
	int peerfd = ::accept(listenfd, NULL, NULL);
	if(peerfd == -1)
	{
		perror("accept error");
		exit(EXIT_FAILURE);
	}
	return peerfd;
}


//预览数据,msg_peek并不实际移走缓冲区的数据
size_t recvPeek(int sockfd, void * buf, size_t len)
{
	int nread;
	do
	{
		nread = ::recv(sockfd, buf, len, MSG_PEEK);
	}while(nread == -1 && errno == EINTR);
	return nread;
}

//通过预览数据，判断conn是否关闭
bool isConnectionClosed(int sockfd)
{
	char buf[1024];
	int nread = recvPeek(sockfd, buf, sizeof(buf));
	if(-1 == nread)
	{
		perror("recvPeek--- ");
		return true;
		//exit(EXIT_FAILURE);//若peer端已关闭连接，会导致server端崩溃
	}
	return (0 == nread);
}

//==========================================


EpollPoller::EpollPoller(int listenfd)
: epollfd_(createEpollFd())
, listenfd_(listenfd)
, wakeupfd_(createEventFd())
, isLooping_(false)
, eventsList_(1024)
{
	addEpollFdRead(epollfd_, listenfd_);
	addEpollFdRead(epollfd_, wakeupfd_);
}


EpollPoller::~EpollPoller()
{
	::close(epollfd_);
}

void EpollPoller::loop()
{
	isLooping_ = true;
	while(isLooping_)
	{
		waitEpollfd();
	}
}

void EpollPoller::unloop()
{
	if(isLooping_)
		isLooping_ = false;
}

//计算线程调用该方法注册回调函数
void EpollPoller::runInLoop(const Functor & cb)
{
	{
	MutexLockGuard mlg(mutex_);
	pendingFunctors_.push_back(cb);
	}
	wakeup();
}

//IO线程中执行计算线程注册的回调函数
void EpollPoller::doPendingFunctors()
{
	printf("doPendingFunctors()\n");
	std::vector<Functor> functors;
	{
	MutexLockGuard mlg(mutex_);
	functors.swap(pendingFunctors_);
	}
	
	for(size_t i = 0; i < functors.size(); ++i)
	{
		functors[i]();
	}
}

//eventfd写事件,通知计算操作已完成
void EpollPoller::wakeup()
{
	uint64_t one = 1;
	ssize_t n = ::write(wakeupfd_, &one, sizeof(one));
	if(n != sizeof(one))
	{
		perror("EpollPoller::wakeup() n != 8");
	}
}

//对eventfd进行处理，防止一直触发
void EpollPoller::handleRead()
{
	uint64_t one = 1;
	ssize_t n = ::read(wakeupfd_, &one, sizeof(one));
	if(n != sizeof(one))
	{
		perror("EpollPoller::handleRead() n != 8");
	}
}

//这里是拷贝，因为不同的新连接都需要注册一遍连接建立、消息处理、连接关闭三个回调函数
//如果用std::move的话只能注册给第一个连接
void EpollPoller::setConnectionCallback(EpollCallback cb)
{
	onConnectionCb_ = cb;
}

void EpollPoller::setMessageCallback(EpollCallback cb)
{
	onMessageCb_ = cb;
}

void EpollPoller::setCloseCallback(EpollCallback cb)
{
	onCloseCb_ = cb;
}

void EpollPoller::waitEpollfd()
{
	int nready;
	do
	{
        //监听epoll
		nready = ::epoll_wait(epollfd_, 
							  &(*eventsList_.begin()),
							  eventsList_.size(),
							  5000);
	}while(nready == -1 && errno == EINTR);

	if(nready == -1)//异常退出
	{
		perror("epoll_wait error");
		exit(EXIT_FAILURE);
	}
	else if(nready == 0)//超时，超过5秒
	{
		printf("epoll_wait timeout\n");	
	}
	else//监听到了事件
	{
		//如果已达到当前监听的上限，则对vector做一个手动扩容的操作，自动扩容必须发生在插入操作时，那时候就晚了
		if(nready == static_cast<int>(eventsList_.size()))
		{
			eventsList_.resize(eventsList_.size() * 2);
		}
		
		//遍历每一个激活的文件描述符
		for(int idx = 0; idx != nready; ++idx)
		{
			if(eventsList_[idx].data.fd == listenfd_)//如果是新连接请求
			{
				if(eventsList_[idx].events & EPOLLIN)
				{
					handleConnection();
				}
			}
			else if(eventsList_[idx].data.fd == wakeupfd_)//如果是计算线程通知计算完成
			{
				printf("wakeupfd light\n");
				if(eventsList_[idx].events & EPOLLIN)
				{
					handleRead();//处理eventfd防止一直触发
					doPendingFunctors();//IO线程处理信息的发送
				}
			}
			else
			{
				if(eventsList_[idx].events & EPOLLIN)//正常消息传递
				{
					handleMessage(eventsList_[idx].data.fd);
				}
			}
		}//end for
	}//end else
}


//处理新连接
void EpollPoller::handleConnection()
{
	int peerfd = acceptConnFd(listenfd_);
	addEpollFdRead(epollfd_, peerfd);

    //给新连接注册从TcpServer一路注册过来的回调函数
	TcpConnectionPtr conn(new TcpConnection(peerfd, this));
	//conn->send("welcome to server.\n");
	conn->setConnectionCallback(onConnectionCb_);
	conn->setMessageCallback(onMessageCb_);
	conn->setCloseCallback(onCloseCb_);

	std::pair<ConnectionMap::iterator, bool> ret;
	ret = connMap_.insert(std::make_pair(peerfd, conn));
	assert(ret.second == true);
	(void)ret;
	//connMap_[peerfd] = conn;

	conn->handleConnectionCallback();//新的连接执行连接建立回调函数
}

//处理消息传递
void EpollPoller::handleMessage(int peerfd)
{
	bool isClosed = isConnectionClosed(peerfd);
	ConnectionMap::iterator it = connMap_.find(peerfd);
	assert(it != connMap_.end());

	if(isClosed)
	{
		it->second->handleCloseCallback();
		delEpollReadFd(epollfd_, peerfd);
		connMap_.erase(it);
	}
	else
	{
		it->second->handleMessageCallback();
	}
}

}// end of namespace zyh
