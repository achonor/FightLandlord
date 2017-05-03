#include "stdafx.h"
#include "GGData.h"

CCNode *GGNode;
rapidjson::Document My_config;
//Client My_Client;
 MyScheduler *My_Scheduler;


void My_InitGGData() {
	//公共Node
	GGNode = Node::create();
	GGNode->retain();
	//游戏配置文件
	My_config = My_getJsonData("config.json");
	//全局定时器生成器
	My_Scheduler = MyScheduler::getInstance();
	GGNode->addChild(My_Scheduler);

}

void My_ClearGGData() {
	GGNode->release();
}