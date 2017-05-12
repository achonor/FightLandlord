#include "stdafx.h"
#include "GGData.h"

//数据初始化
Size My_visibleSize = Size(0, 0);

int My_playerID = -1;

CCNode *GGNode = NULL;

rapidjson::Document My_config;

Client* My_client= NULL;

GameLayer* My_gameScene = NULL;


string EVENT_RECEIVE_DATA = "EVENT_RECEIVE_DATA";


void My_InitGGData() {
	//公共Node
	GGNode = Node::create();
	GGNode->retain();
	//游戏配置文件
	My_config = My_getJsonData("config/config.json");
	//游戏客户端
	My_client = Client::create();
}

void My_ClearGGData() {
	GGNode->release();
}