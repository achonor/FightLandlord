﻿#include "stdafx.h"
#include "MyGame.h"
#include "GameScene.h"

USING_NS_CC;
using namespace std;

game::game()
{
}


void game::init() {
	//添加搜索路径
	CCFileUtils::getInstance()->addSearchPath("../../config");

	//初始化GGData
	My_InitGGData();
	
	//初始化网络
    std::string tmpAddr = My_config["loginAddr"].GetString();
    My_client->initNet(tmpAddr, My_config["serverPort"].GetInt());
}
	
void game::start() {
	//设计分辨率
	auto designResolutionSize = cocos2d::Size(My_config["resWidth"].GetInt(), My_config["resHeight"].GetInt());

	// 导演
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		glview = GLViewImpl::createWithRect("FightLandlord", Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
		glview = GLViewImpl::create("FightLandlord");
#endif
		director->setOpenGLView(glview);
	}

	// 左下角显示fps
	director->setDisplayStats(false);

	// 每秒刷新次数（帧数）
	director->setAnimationInterval(1.0 / 30);

	// 设置设计分辨率
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::FIXED_WIDTH);

	//保存屏幕尺寸
	My_visibleSize = Director::getInstance()->getVisibleSize();

	// 创建初始场景
	auto scene = Scene::create();
	My_gameScene = GameLayer::create();
	scene->addChild(My_gameScene);
	//切换到场景
	director->runWithScene(scene);
	scene->addChild(My_client);
}

game::~game()
{
}
