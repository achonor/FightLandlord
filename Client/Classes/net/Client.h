#pragma once
#ifndef CLIENT_H
#define CLIENT_H

//#include "MySocket.h"
#include "Request.h"
#include "cocos2d.h"

#include <iostream>

class Client
{
	//Client��ǰ��״̬
protected:
	int state;
	//client��ǰ��Socket
	MySocket clientSocket;

	/*/��������
	void sendData(const char* str);
	//��������
	void onReceive();*/

public:
	Client();
	virtual ~Client();

	bool initNet(std::string &addr, int port);
};

#endif