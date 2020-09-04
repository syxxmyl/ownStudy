#ifndef _NONCOPYABLE_H_
#define _NONCOPYABLE_H_

namespace zyh
{

class Noncopyable
{
protected:
	Noncopyable(){}
private:
	Noncopyable(const Noncopyable & rhs);
	Noncopyable & operator=(const Noncopyable & rhs);
};

}//end of namespace zyh
#endif
