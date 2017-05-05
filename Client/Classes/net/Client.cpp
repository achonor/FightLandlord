#include "stdafx.h"
#include "Client.h"
#include "GGData.h"
#include "cocos2d.h"
#include <map>

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

//服务器时间和客户端时间的差
int ServerTImeOffect = 0;

//请求的唯一编号
int RequestIdx = 1;

//保存回调函数
map<int, function<void(google::protobuf::Message*)> > callMap;

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

	//char buffer[20];
	//int ret = (this->clientSocket).Recv(buffer, 4);
	//buffer[ret] = '\0';
	//cout << My_char4ToInt(buffer) << endl;
	//非阻塞
	clientSocket.setRecvTimeOut(1);
	clientSocket.setSendTimeOut(1);

	//添加监听
	this->recvDataListener = UserEvent::addEventListener(EVENT_RECEIVE_DATA, [&](EventCustom *event) {
		auto tmpBuffer = (std::string*)(event->getUserData());
		this->receiveData(tmpBuffer);
	});
	//连接成功，启动定时器接受数据
	this->onReceive();

	return true;
}


void Client::receiveData(const string *data) {
	MainProto proto;
	proto.ParseFromString(*data);
	//proto.PrintDebugString();
	//获取真正的协议数据
	google::protobuf::Message* message = My_CreateMessage(proto.messagename());
	if (NULL == message) {
		cerr << "messagename not is protobuf class!!!" << endl;
		return;
	}
	message->ParseFromString(proto.messagedata());

	//打印
	cout << endl << proto.messagename() << ":" << endl;
	message->PrintDebugString();

	//校正服务器时间
	this->setServerTime(proto.servertime());

	//cout << this->getServerTime() << endl;

	//激活协议事件
	UserEvent::dispatchEvent(proto.messagename(), (void*)message);

	//激活回调函数
	try {
		auto callback = callMap[proto.messageid()];
		if (NULL != callback) {
			callback(message);
		}
		callMap.erase(proto.messageid());
	} catch(std::exception e){
		cerr << "Error: " << e.what() << endl;
	}
	delete message;
}

void Client::request(google::protobuf::Message* proto, function<void(google::protobuf::Message*)> callback) {
	string protoStr = proto->SerializeAsString();

	MainProto mainProto;
	mainProto.set_playerid(My_playerID);
	mainProto.set_messageid(RequestIdx++);
	mainProto.set_messagename(proto->GetTypeName());
	mainProto.set_messagedata(protoStr);

	//保存回调函数
	callMap[mainProto.messageid()] = callback;

	string mainProtoStr = My_Serialization(&mainProto);
	this->sendData(mainProtoStr.c_str(), mainProtoStr.length());
	return;
}


//设置服务器时间
void Client::setServerTime(int tm) {
	int localTime = time(NULL);
	ServerTImeOffect = tm - localTime;
}
//获取服务器时间
int Client::getServerTime() {
	int localTime = time(NULL);
	return localTime + ServerTImeOffect;
}

void Client::onReceive() {
	//接受数据的函数
	auto receive = [this](Client* self, std::string &buffer, int len) {
		if (DATA_MAX_LENGTH < len) {
			len = DATA_MAX_LENGTH;
		}else {
			char chrBuffer[DATA_MAX_LENGTH + 2];
			int ret = (self->clientSocket).Recv(chrBuffer, len);
			if (ret <= 0) {
				//cerr << "error: " << (self->clientSocket).GetError() << endl;
				return 0;
			} else{
				buffer =std::string(chrBuffer, ret);
				//if (0 < ret) {
				//	cout << "recvData: " << buffer[ret] << endl;
				//}
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

	static RecvState status = idle;
	static int receiveLen = 0;

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
	auto head_func = [&](Client* self) {
		std::string buffer;
		int ret = receive(self, buffer, receiveLen);
		if (-1 == ret) {
			switch_die();
			return;
		}
		if (ret <= 0) {
			return;
		}
		int bodyLen = My_char4ToInt(buffer.c_str());
		switch_body(bodyLen);
	};
	//接受数据
	auto body_func = [&](Client* self) {
		static string lastBuffer;
		std::string buffer;
		int ret = receive(self, buffer, receiveLen);
		if (-1 == ret) {
			switch_die();
			return;
		}
		if (ret <= 0) {
			return;
		}
		if (0 < lastBuffer.length()) {
			//需要拼接数据
			lastBuffer = lastBuffer + buffer;
		} else {
			lastBuffer = buffer;
		}
		if (ret < receiveLen) {
			//数据没有接收完
			switch_body(receiveLen - ret);
		} else {
			//数据接收完成
			UserEvent::dispatchEvent(EVENT_RECEIVE_DATA, (void*)&lastBuffer);
			lastBuffer.clear();
			switch_idle();
		}
	};
	auto die_func = [&]() {
		//pass
	};

	auto __tick = [&, this](float t) {
		switch (status)
		{
		case idle: idle_func(); break;
		case head: head_func(this);  break;
		case body: body_func(this);  break;
		case die: head_func(this);  break;
		default:
			idle_func(); break;
		}
	};
	this->schedule(__tick, SOCKET_TICK_TIME, "RECVDATALOOP");
}

void Client::sendData(const char* str, int len) {
	(this->clientSocket).Send(str, len);
}







Client::~Client()
{
	//关闭套接字
	clientSocket.Close();
	clientSocket.Clean();
}
