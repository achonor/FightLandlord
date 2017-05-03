#pragma once
#ifndef CLIENT_H
#define CLIENT_H

#include "Request.h"
#include "cocos2d.h"

#include <iostream>

class Client:public Node
{
	//Client当前的状态
protected:
	int state;
	//client当前的Socket
	MySocket clientSocket;
	//接收数据监听
	UserEvent* recvDataListener;
	//发送数据
	void sendData(const char* str);
	//接收数据
	void onReceive();
	//收到数据后的处理
	void receiveData(const char *data);


public:
	Client();
	virtual ~Client();
	CREATE_FUNC(Client);

	virtual bool init();

	bool initNet(std::string &addr, int port);
};

#endif