#ifndef _SOCKET_H_
#define _SOCKET_H_

#include "Noncopyable.h"

namespace zyh
{
class InetAddress;
class Socket : Noncopyable
{
public:
	Socket(int sockfd);
	Socket();
	~Socket();

	void ready(const InetAddress & addr);

	int accept();
	void shutdownWrite();
	int fd(){	return sockfd_;	}

	static InetAddress getLocalAddr(int sockfd);
	static InetAddress getPeerAddr(int sockfd);

private:
	void bindAddress(const InetAddress & addr);
	void listen();
	void setReuseAddr(bool flag);
	void setReusePort(bool flag);
private:
	int sockfd_;
};
}// end of namespace zyh

#endif
