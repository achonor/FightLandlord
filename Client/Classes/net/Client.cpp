#include "stdafx.h"
#include "Client.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

//��ʱʱ��
const int M_Timeout = 10;

Client::Client()
{	

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

	//���ӳɹ���������ʱ����������


	return true;
}







Client::~Client()
{
	//�ر��׽���
	clientSocket.Close();
	clientSocket.Clean();
}
