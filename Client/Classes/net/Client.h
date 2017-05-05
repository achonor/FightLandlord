#pragma once
#ifndef CLIENT_H
#define CLIENT_H

#include "cocos2d.h"

#include <iostream>

class Client:public Node
{
	//Client��ǰ��״̬
protected:
	int state;
	//client��ǰ��Socket
	MySocket clientSocket;
	//�������ݼ���
	UserEvent* recvDataListener;
	//��������
	void sendData(const char* str, int len);
	//��������
	void onReceive();
	//�յ����ݺ�Ĵ���
	void receiveData(const string *data);
	//���÷�����ʱ��
	void setServerTime(int tm);

public:
	//����
	void request(google::protobuf::Message* proto, function<void(google::protobuf::Message*)> callback);
	//��ȡ������ʱ��
	int getServerTime();


public:
	Client();
	virtual ~Client();
	CREATE_FUNC(Client);

	virtual bool init();

	bool initNet(std::string &addr, int port);
};

#endif