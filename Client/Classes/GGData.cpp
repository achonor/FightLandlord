#include "stdafx.h"
#include "GGData.h"

CCNode *GGNode;
rapidjson::Document My_config;
Client* My_Client;
string EVENT_RECEIVE_DATA = "EVENT_RECEIVE_DATA";


void My_InitGGData() {
	//公共Node
	GGNode = Node::create();
	GGNode->retain();
	//游戏配置文件
	My_config = My_getJsonData("config.json");
	//游戏客户端
	My_Client = Client::create();
}

void My_ClearGGData() {
	GGNode->release();
}