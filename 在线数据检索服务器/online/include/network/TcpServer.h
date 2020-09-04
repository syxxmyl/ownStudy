#ifndef _TCPSERVER_H_
#define _TCPSERVER_H_

#include "InetAddress.h"
#include "Socket.h"
#include "EpollPoller.h"

namespace zyh
{

class TcpServer
{
public:
	typedef TcpConnection::TcpConnectionCallback TcpServerCallback;

	TcpServer(unsigned short port);
	TcpServer(const char * pIp, unsigned short port);

	void start();
	void stop();

	void setConnectionCallback(TcpServerCallback cb);
	void setMessageCallback(TcpServerCallback cb);
	void setCloseCallback(TcpServerCallback cb);

private:
	InetAddress inetAddr_;
	Socket sockfd_;
	EpollPoller epollfd_;

	TcpServerCallback onConnectionCb_;
	TcpServerCallback onMessageCb_;
	TcpServerCallback onCloseCb_;
};

}// end of namespace zyh

#endif
