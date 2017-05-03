#include "stdafx.h"
#include "Client.h"
#include "GGData.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

//超时时间
const int M_Timeout = 10;

//接收数据间隔
const float SOCKET_TICK_TIME = 0.1f;

//包头长度
const int LENGTH_HEAD = 4;

//单次接收最大长度
const int DATA_MAX_LENGTH = 4096;

Client::Client()
{	

}


bool Client::init() {

	return true;
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

	cout << "connect success:" << addr << ": " << port << endl;
	//非阻塞
	clientSocket.setRecvTimeOut(0);

	//添加监听
	this->recvDataListener = UserEvent::addEventListener(EVENT_RECEIVE_DATA, [&](EventCustom *event) {
		auto tmpBuffer = (char*)(event->getUserData());
		this->receiveData(tmpBuffer);
	});
	//连接成功，启动定时器接受数据
	this->onReceive();

	return true;
}


void Client::receiveData(const char *data) {
	cout << data << endl;
}


void Client::onReceive() {

	//接受数据的函数
	auto receive = [&](char *buffer, int len) {
		if (DATA_MAX_LENGTH < len) {
			cerr << "receive lenght > DATA_MAX_LENGTH" << endl;
			return 0;
		}else {
			int ret = clientSocket.Recv(buffer, len);
			if (ret == SOCKET_ERROR) {
				return 0;
			} else {
				buffer[ret] = '\0';
				return ret;
			}
		}
	};

	//当前接收的状态
	enum RecvState
	{
		idle = 0, //空闲状态
		head = 1, //接收包头
		body = 2, //接收数据体
		die = 3   //接收失败
	};

	RecvState status = idle;
	int receiveLen = 0;

	auto switch_idle = [&]() {
		status = idle;
		receiveLen = 0;
	};
	auto switch_head = [&]() {
		status = head;
		receiveLen = LENGTH_HEAD;
	};
	auto switch_die = [&]() {
		status = die;
		receiveLen = 0;
	};
	auto switch_body = [&](int len) {
		status = body;
		receiveLen = len;
	};

	auto idle_func = [&]() {
		switch_head();
	};
	//接收包头
	auto head_func = [&]() {
		char buffer[LENGTH_HEAD + 2];
		int ret = receive(buffer, receiveLen);
		if (0 == ret) {
			switch_die();
		}
		int bodyLen = My_char4ToInt(buffer);
		switch_body(bodyLen);
	};
	//接受数据
	auto body_func = [&]() {
		char buffer[DATA_MAX_LENGTH + 2];
		int ret = receive(buffer, receiveLen);
		if (0 == ret) {
			switch_die();
		}

		UserEvent::dispatchEvent(EVENT_RECEIVE_DATA, (void*)buffer);
		switch_idle();
	};
	auto die_func = [&]() {
		//pass
	};

	auto __tick = [&](float t) {
		cout << status << t << endl;
		switch (status)
		{
		case idle: idle_func(); break;
		case head: head_func();  break;
		case body: body_func();  break;
		case die: die_func();  break;
		default:
			idle_func(); break;
		}
	};
	this->schedule(__tick, SOCKET_TICK_TIME, "RECVDATALOOP");
}

void Client::sendData(const char* str) {

}







Client::~Client()
{
	//关闭套接字
	clientSocket.Close();
	clientSocket.Clean();
}
