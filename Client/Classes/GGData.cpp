#include "stdafx.h"
#include "GGData.h"

CCNode *GGNode;
rapidjson::Document My_config;
//Client My_Client;
 MyScheduler *My_Scheduler;


void My_InitGGData() {
	//����Node
	GGNode = Node::create();
	GGNode->retain();
	//��Ϸ�����ļ�
	My_config = My_getJsonData("config.json");
	//ȫ�ֶ�ʱ��������
	My_Scheduler = MyScheduler::getInstance();
	GGNode->addChild(My_Scheduler);

}

void My_ClearGGData() {
	GGNode->release();
}