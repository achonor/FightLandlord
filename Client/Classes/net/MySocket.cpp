//#include "stdafx.h"
#include "MySocket.h"
#include "stdio.h"

#ifdef WIN32
#pragma comment(lib, "wsock32")
#endif

MySocket::MySocket(SOCKET sock)
{
	mySocket = sock;
}

MySocket::~MySocket()
{
}

int MySocket::Init()
{
	static bool isInit = false;
	if (isInit)
		return 0;
#ifdef WIN32
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 0);
	int ret = WSAStartup(version, &wsaData);//win sock start up
	if (ret) {
		return -1;
	}
#endif
	isInit = true;
	return 0;
}

int MySocket::Clean()
{
#ifdef WIN32
	return (WSACleanup());
#endif
	return 0;
}

MySocket& MySocket::operator = (SOCKET s)
{
	mySocket = s;
	return (*this);
}

MySocket::operator SOCKET ()
{
	return mySocket;
}

void MySocket::setNonBlocking()
{
#ifdef WIN32
	u_long mode = 1;
	ioctlsocket(mySocket, FIONBIO, &mode);
#else
	int cflags = fcntl(mySocket, F_GETFL, 0);
	fcntl(mySocket, F_SETFL, cflags | O_NONBLOCK);
#endif
}

void MySocket::setSendTimeOut(int time)
{
#ifdef WIN32
	setsockopt(mySocket, SOL_SOCKET, SO_SNDTIMEO, (char*)&time, sizeof(int));
#else
	int second = time * 0.001;
	int millisecond = time % 1000;
	struct timeval timeout = { second, millisecond };
	setsockopt(mySocket, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, sizeof(struct timeval));
#endif
}

void MySocket::setRecvTimeOut(int time)
{
#ifdef WIN32
	setsockopt(mySocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&time, sizeof(int));
#else
	int second = time * 0.001;
	int millisecond = time % 1000;
	struct timeval timeout = { second, millisecond };
	setsockopt(mySocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(struct timeval));
#endif
}

bool MySocket::Create(int af, int type, int protocol)
{
	mySocket = socket(af, type, protocol);
	if (mySocket == INVALID_SOCKET) {
		return false;
	}
	return true;
}

bool MySocket::Connect(const char* ip, unsigned short port)
{
	struct sockaddr_in svraddr;
	svraddr.sin_family = AF_INET;
	svraddr.sin_addr.s_addr = inet_addr(ip);
	svraddr.sin_port = htons(port);
	int ret = connect(mySocket, (struct sockaddr*)&svraddr, sizeof(svraddr));
	if (ret == SOCKET_ERROR) {
		return false;
	}
	return true;
}

bool MySocket::Bind(unsigned short port)
{
	struct sockaddr_in svraddr;
	svraddr.sin_family = AF_INET;
	svraddr.sin_addr.s_addr = INADDR_ANY;
	svraddr.sin_port = htons(port);

	int opt = 1;
	if (setsockopt(mySocket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0)
		return false;

	int ret = bind(mySocket, (struct sockaddr*)&svraddr, sizeof(svraddr));
	if (ret == SOCKET_ERROR) {
		return false;
	}
	return true;
}


bool MySocket::Listen(int backlog)
{
	int ret = listen(mySocket, backlog);
	if (ret == SOCKET_ERROR) {
		return false;
	}
	return true;
}

bool MySocket::Accept(MySocket& s, char* fromip)
{
	struct sockaddr_in cliaddr;
	socklen_t addrlen = sizeof(cliaddr);
	SOCKET sock = accept(mySocket, (struct sockaddr*)&cliaddr, &addrlen);
	if (sock == SOCKET_ERROR) {
		return false;
	}

	s = sock;
	if (fromip != NULL)
		sprintf(fromip, "%s", inet_ntoa(cliaddr.sin_addr));

	return true;
}

int MySocket::Send(const char* buf, int len, int flags)
{
	int bytes;
	int count = 0;

	while (count < len) {

		bytes = send(mySocket, buf + count, len - count, flags);
		if (bytes == -1 || bytes == 0)
			return -1;
		count += bytes;
	}

	return count;
}

int MySocket::Recv(char* buf, int len, int flags)
{
	return (recv(mySocket, buf, len, flags));
}

int MySocket::Close()
{
#ifdef WIN32
	return (closesocket(mySocket));
#else
	return (close(mySocket));
#endif
}

int MySocket::GetError()
{
#ifdef WIN32
	return (WSAGetLastError());
#else
	return (-1);
#endif
}

bool MySocket::DnsParse(const char* domain, char* ip)
{
	struct hostent* p;
	if ((p = gethostbyname(domain)) == NULL)
		return false;

	sprintf(ip,
		"%u.%u.%u.%u",
		(unsigned char)p->h_addr_list[0][0],
		(unsigned char)p->h_addr_list[0][1],
		(unsigned char)p->h_addr_list[0][2],
		(unsigned char)p->h_addr_list[0][3]);

	return true;
}
