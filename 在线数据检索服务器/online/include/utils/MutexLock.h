#ifndef _MUTEXLOCK_H_
#define _MUTEXLOCK_H_

#include "Noncopyable.h"
#include <pthread.h>

namespace zyh
{

class MutexLock : Noncopyable
{
public:
	MutexLock();
	~MutexLock();

	void lock();
	void unlock();
	
	pthread_mutex_t * getMutexLockPtr();


private:
	pthread_mutex_t mutex_;
	bool isLocked_;
};


class MutexLockGuard
{
public:
	MutexLockGuard(MutexLock & mutex);
	~MutexLockGuard();

private:
	MutexLock & mutex_;
};

}// end of namespace zyh

#endif
