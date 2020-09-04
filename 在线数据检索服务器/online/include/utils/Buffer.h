#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "Noncopyable.h"
#include "MutexLock.h"
#include "Condition.h"
#include <queue>
#include <functional>

namespace zyh
{

class Buffer : Noncopyable
{
public:
	typedef std::function<void()> Task;
	Buffer(size_t size);

	void push(Task task);
	Task pop();

	bool full();
	bool empty();

	void wakeup_empty();
	void set_flag(bool flag);

private:
	MutexLock          mutex_;
	Condition          notFull_;
	Condition          notEmpty_;
	size_t             size_;
	std::queue<Task>  que_;
	bool               flag_;
};

}// end of namespace zyh

#endif
