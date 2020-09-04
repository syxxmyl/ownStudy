#include "Threadpool.h"
#include "Thread.h"
#include <stdio.h>

namespace zyh
{
Threadpool::Threadpool(size_t threadsNum, size_t bufNum)
	: threadsNum_(threadsNum),//线程数量
	  buf_(bufNum),//任务队列最大任务数
	  isExit_(false)//是否停止服务
{
	printf("Threadpool()\n");
}

Threadpool::~Threadpool()
{
	if(!isExit_)
	{
		stop();
	}
}

void Threadpool::start()
{
	for(size_t idx = 0; idx != threadsNum_; ++idx)//创建线程池
	{
		Thread * pThread = new Thread(
			std::bind(&Threadpool::threadFunc, this));//给每个线程注册回调函数
		vecThreads_.push_back(pThread);
	}

	std::vector<Thread *>::iterator it;
	for(it = vecThreads_.begin(); it != vecThreads_.end(); ++it)
	{
		(*it)->start();//让每个线程都开始运行
	}
	printf("Threadpool::start()\n");
}


void Threadpool::stop()
{
	if(!isExit_)
	{
		isExit_ = true;
		buf_.set_flag(false);
		buf_.wakeup_empty();//唤醒所有线程,防止由于线程执行速度过快导致阻塞在了getTask位置

		std::vector<Thread *>::iterator it;
		for(it = vecThreads_.begin(); it != vecThreads_.end(); ++it)
		{
			(*it)->join();
			delete (*it);
		}
		vecThreads_.clear();
	}
}


//typedef std::function<void()> Task;
//Task是函数对象

void Threadpool::addTask(Task task)
{
	printf("Threadpool::addTask()\n");
	buf_.push(task);
}

Threadpool::Task Threadpool::getTask()
{
	return buf_.pop();
}

void Threadpool::threadFunc()
{
	while(!isExit_)
	{
		//Task task = buf_.pop();
		Task task = getTask();
		if(task)
		{
			task();
		}
	}
}


}// end of namespace zyh
