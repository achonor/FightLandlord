#pragma once
#ifndef CLIENT_H
#define CLIENT_H

//#include "MySocket.h"
#include "Request.h"
#include "cocos2d.h"

#include <iostream>

class Client
{
	//Client当前的状态
protected:
	int state;
	//client当前的Socket
	MySocket clientSocket;

	/*/发送数据
	void sendData(const char* str);
	//接收数据
	void onReceive();*/

public:
	Client();
	virtual ~Client();

	bool initNet(std::string &addr, int port);
};

#endif