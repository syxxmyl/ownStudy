#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include "Buffer.h"
#include <vector>
#include <functional>

namespace zyh
{
class Thread;

class Threadpool
{
public:
	typedef std::function<void()> Task;
	Threadpool(size_t threadsNum, size_t bufNum);
	~Threadpool();

	void start();
	void stop();

	void addTask(Task task);

private:
	void threadFunc();
	Task getTask();

private:
	size_t threadsNum_;
	std::vector<Thread *> vecThreads_;
	Buffer buf_;
	bool isExit_;
};

}// end of namespace zyh

#endif
