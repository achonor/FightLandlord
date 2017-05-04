#include "stdafx.h"
#include "Client.h"
#include "GGData.h"
#include "cocos2d.h"
#include <map>

USING_NS_CC;
using namespace std;

//��ʱʱ��
const int M_Timeout = 10;

//�������ݼ��
const float SOCKET_TICK_TIME = 0.1f;

//��ͷ����
const int LENGTH_HEAD = 4;

//���ν�����󳤶�
const int DATA_MAX_LENGTH = 4096;

//������ʱ��Ϳͻ���ʱ��Ĳ�
int ServerTImeOffect = 0;

//�����Ψһ���
int RequestIdx = 1;

//����ص�����
map<int, function<void(google::protobuf::Message*)> > callMap;

Client::Client()
{	

}


bool Client::init() {

	return true;
}

bool Client::initNet(std::string &addr, int port) {
	//���ӷ�����
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
	//������
	clientSocket.setRecvTimeOut(1);
	clientSocket.setSendTimeOut(1);

	//��Ӽ���
	this->recvDataListener = UserEvent::addEventListener(EVENT_RECEIVE_DATA, [&](EventCustom *event) {
		auto tmpBuffer = (char*)(event->getUserData());
		this->receiveData(tmpBuffer);
	});
	//���ӳɹ���������ʱ����������
	this->onReceive();

	return true;
}


void Client::receiveData(const char *data) {
	MainProto proto;
	proto.ParseFromString(data);
	proto.PrintDebugString();
	//��ȡ������Э������
	google::protobuf::Message* message = My_CreateMessage(proto.messagename());
	if (NULL == message) {
		cerr << "messagename not is protobuf class!!!" << endl;
		return;
	}
	message->ParseFromString(proto.messagedata());

	//��ӡ
	cout << endl << proto.messagename() << ":" << endl;
	message->PrintDebugString();

	//У��������ʱ��
	this->setServerTime(proto.servertime());

	//cout << this->getServerTime() << endl;

	//����Э���¼�
	UserEvent::dispatchEvent(proto.messagename(), (void*)message);

	//����ص�����
	auto callback = callMap[proto.messageid()];
	if (NULL != callback) {
		callback(message);
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

	//����ص�����
	callMap[mainProto.messageid()] = callback;

	string mainProtoStr = My_Serialization(&mainProto);
	this->sendData(mainProtoStr.c_str());
	return;
}


//���÷�����ʱ��
void Client::setServerTime(int tm) {
	int localTime = time(NULL);
	ServerTImeOffect = tm - localTime;
}
//��ȡ������ʱ��
int Client::getServerTime() {
	int localTime = time(NULL);
	return localTime + ServerTImeOffect;
}

void Client::onReceive() {

	//�������ݵĺ���
	auto receive = [this](Client* self, char *buffer, int len) {
		if (DATA_MAX_LENGTH < len) {
			cerr << "receive lenght > DATA_MAX_LENGTH" << endl;
			return 0;
		}else {
			int ret = (self->clientSocket).Recv(buffer, len);
			if (ret == SOCKET_ERROR) {
				//cerr << "error: " << (self->clientSocket).GetError() << endl;
				return 0;
			} else {
				buffer[ret] = '\0';
				//if (0 < ret) {
				//	cout << "recvData: " << buffer[ret] << endl;
				//}
				return ret;
			}
		}
	};

	//��ǰ���յ�״̬
	enum RecvState
	{
		idle = 0, //����״̬
		head = 1, //���հ�ͷ
		body = 2, //����������
		die = 3   //����ʧ��
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
	//���հ�ͷ
	auto head_func = [&](Client* self) {
		char buffer[LENGTH_HEAD + 2];
		int ret = receive(self, buffer, receiveLen);
		if (-1 == ret) {
			switch_die();
			return;
		}
		if (ret <= 0) {
			return;
		}
		int bodyLen = My_char4ToInt(buffer);
		switch_body(bodyLen);
	};
	//��������
	auto body_func = [&](Client* self) {
		static char lastBuffer[DATA_MAX_LENGTH << 2];

		char buffer[DATA_MAX_LENGTH];
		int ret = receive(self, buffer, receiveLen);
		if (-1 == ret) {
			switch_die();
			return;
		}
		if (ret <= 0) {
			return;
		}
		if (0 < strlen(lastBuffer)) {
			//��Ҫƴ������
			strcat(lastBuffer, buffer);
		} else {
			strcpy(lastBuffer, buffer);
		}
		if (ret < receiveLen) {
			//����û�н�����
			switch_body(receiveLen - ret);
		} else {
			//���ݽ������
			UserEvent::dispatchEvent(EVENT_RECEIVE_DATA, (void*)lastBuffer);
			lastBuffer[0] = '\0';
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

void Client::sendData(const char* str) {
	(this->clientSocket).Send(str, strlen(str));
}







Client::~Client()
{
	//�ر��׽���
	clientSocket.Close();
	clientSocket.Clean();
}
