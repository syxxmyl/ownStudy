#ifndef _CONDITION_H_
#define _CONDITION_H_

#include "Noncopyable.h"
#include <pthread.h>

namespace zyh
{

class MutexLock;

class Condition : Noncopyable
{
public:
	Condition(MutexLock & mutex);
	~Condition();

	void wait();
	void notify();
	void notifyall();

private:
	pthread_cond_t cond_;
	MutexLock & mutex_;
};

}//end of namespace zyh

#endif
