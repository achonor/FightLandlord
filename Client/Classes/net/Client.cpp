#include "stdafx.h"
#include "Client.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

//超时时间
const int M_Timeout = 10;

Client::Client()
{	

}

bool Client::initNet(std::string &addr, int port) {
	//连接服务器
	clientSocket.Init();
	if ((clientSocket).Create(AF_INET, SOCK_STREAM, 0) == false) {
		cerr << "Create clientSocket fail!!!" << endl;
		return false;
	}
	if ((clientSocket).Connect(addr.c_str(), port) == false) {
		cerr << "connect Server fail!!!: " << addr.c_str() << ": " << port << endl;
		return false;
	}

	//连接成功，启动定时器接受数据


	return true;
}







Client::~Client()
{
	//关闭套接字
	clientSocket.Close();
	clientSocket.Clean();
}
