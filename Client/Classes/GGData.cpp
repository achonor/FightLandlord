#include "stdafx.h"
#include "GGData.h"

//���ݳ�ʼ��
int My_playerID = -1;
CCNode *GGNode = NULL;
rapidjson::Document My_config;
Client* My_Client= NULL;
string EVENT_RECEIVE_DATA = "EVENT_RECEIVE_DATA";


void My_InitGGData() {
	//����Node
	GGNode = Node::create();
	GGNode->retain();
	//��Ϸ�����ļ�
	My_config = My_getJsonData("config.json");
	//��Ϸ�ͻ���
	My_Client = Client::create();
}

void My_ClearGGData() {
	GGNode->release();
}