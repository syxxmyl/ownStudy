#include "TcpConnection.h"
#include "EpollPoller.h"
#include <string.h>
#include <stdio.h>


namespace zyh
{

TcpConnection::TcpConnection(int sockfd, EpollPoller * loop)//知道要给哪个IO线程注册回调函数
: sockfd_(sockfd)
, sockIO_(sockfd)
, localAddr_(zyh::Socket::getLocalAddr(sockfd))
, peerAddr_(zyh::Socket::getPeerAddr(sockfd))
, isShutdownWrite_(false)
, loop_(loop)
{}


TcpConnection::~TcpConnection()
{
	if(!isShutdownWrite_)
	{
		isShutdownWrite_ = true;
		shutdown();
	}
	printf("~TcpConnection()\n");
}

std::string TcpConnection::receive()
{
	char buf[1024];
	memset(buf, 0, sizeof(buf));
	size_t ret = sockIO_.readline(buf, sizeof(buf));
	if(ret == 0)
	{
		return std::string();
	}
	else
		return std::string(buf);
}

void TcpConnection::send(const std::string & msg)
{
	sockIO_.writen(msg.c_str(), msg.size());
}

//针对php服务器
void TcpConnection::sendAndClose(const std::string & msg)
{
	send(msg);
	shutdown();
}

//让发送信息延迟给IO线程进行，而不是计算线程,即让EpollPoller对象执行发送信息的操作
void TcpConnection::sendInLoop(const std::string & msg)
{
	loop_->runInLoop(std::bind(&TcpConnection::send, this, msg));
}

//关闭写端
void TcpConnection::shutdown()
{
	if(!isShutdownWrite_)
		sockfd_.shutdownWrite();
	isShutdownWrite_ = true;
}


//返回两端ip地址及端口号
std::string TcpConnection::toString()
{
	char str[100];
	snprintf(str, sizeof(str), "%s:%d -> %s:%d",
			 localAddr_.ip().c_str(),
			 localAddr_.port(),
			 peerAddr_.ip().c_str(),
			 peerAddr_.port());
	return std::string(str);
}

//EpollPoller中调用，注册回调函数处理连接
void TcpConnection::setConnectionCallback(TcpConnectionCallback cb)
{
	onConnectionCb_ = cb;
}

void TcpConnection::setMessageCallback(TcpConnectionCallback cb)
{
	onMessageCb_ = cb;
}

void TcpConnection::setCloseCallback(TcpConnectionCallback cb)
{
	onCloseCb_ = cb;
}

//EpollPoller中调用，执行之前注册的连接处理函数
void TcpConnection::handleConnectionCallback()
{
	if(onConnectionCb_)
		onConnectionCb_(shared_from_this());
}

void TcpConnection::handleMessageCallback()
{
	if(onMessageCb_)
		onMessageCb_(shared_from_this());
}

void TcpConnection::handleCloseCallback()
{
	if(onCloseCb_)
		onCloseCb_(shared_from_this());
}

}// end of namespace zyh
