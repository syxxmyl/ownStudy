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

//��������Ƿ�����
bool Buffer::full()
{
	return size_ == que_.size();
}

bool Buffer::empty()
{
	return 0 == que_.size();
}
	  
//�������̵߳���
void Buffer::push(Task task)
{
	MutexLockGuard guard(mutex_);//�ֲ�����
	while(full())//ʹ��while��Ϊ�˱��쳣����,��Ȼ�������������Ƿ������ж��Ƿ���Է���������
	{
		notFull_.wait();
	}
	que_.push(task);//����������
	
	notEmpty_.notify();//�����������̣߳�ȡ����ִ��

}

//�������̵߳���
Buffer::Task Buffer::pop()
{
	MutexLockGuard guard(mutex_);

	while(empty() && flag_)
	{
		notEmpty_.wait();
	}

	if(flag_)//�̳߳��Ƿ��������
	{
		Task task = que_.front();
		que_.pop();

		notFull_.notify();//�����������߳̿��Է���������
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
