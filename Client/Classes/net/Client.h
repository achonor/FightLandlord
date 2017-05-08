#pragma once
#ifndef CLIENT_H
#define CLIENT_H

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
	//正在请求的数量
	int requestNumber;
	//发送数据
	void sendData(const char* str, int len);
	//接收数据
	void onReceive();
	//收到数据后的处理
	void receiveData(const string *data);
	//设置服务器时间
	void setServerTime(int tm);

public:
	//请求
	void request(google::protobuf::Message* proto, function<void(google::protobuf::Message*)> callback);
	//获取服务器时间
	int getServerTime();


public:
	Client();
	virtual ~Client();
	CREATE_FUNC(Client);

	virtual bool init();

	bool initNet(std::string &addr, int port);
};

#endif