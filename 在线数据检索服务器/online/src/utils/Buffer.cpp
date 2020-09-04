#include "Buffer.h"

namespace zyh
{
Buffer::Buffer(size_t size)
	:	mutex_(),
		notFull_(mutex_),
		notEmpty_(mutex_),
		size_(size),
		flag_(true)
{
}

//任务队列是否已满
bool Buffer::full()
{
	return size_ == que_.size();
}

bool Buffer::empty()
{
	return 0 == que_.size();
}
	  
//生产者线程调用
void Buffer::push(Task task)
{
	MutexLockGuard guard(mutex_);//局部对象
	while(full())//使用while是为了被异常唤醒,仍然会根据任务队列是否已满判断是否可以放入新任务
	{
		notFull_.wait();
	}
	que_.push(task);//放入新任务
	
	notEmpty_.notify();//唤醒消费者线程，取任务执行

}

//消费者线程调用
Buffer::Task Buffer::pop()
{
	MutexLockGuard guard(mutex_);

	while(empty() && flag_)
	{
		notEmpty_.wait();
	}

	if(flag_)//线程池是否继续运行
	{
		Task task = que_.front();
		que_.pop();

		notFull_.notify();//唤醒生产者线程可以放入任务了
		return task;
	}
	else
	{
		return NULL;
	}
}


void Buffer::wakeup_empty()
{
	notEmpty_.notifyall();
}

void Buffer::set_flag(bool flag)
{
	flag_ = flag;
}

}//end of namespace zyh
