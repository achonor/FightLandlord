#include "stdafx.h"
#include "GGData.h"
#include "GameScene.h"
#include <iostream>

USING_NS_CC;
using namespace std;

Scene* GameLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//ÇëÇóµÇÂ½
	this->requestLogin();
    return true;
}


//ÇëÇóµÇÂ½
bool GameLayer::requestLogin() {

	//test
	auto testRequest = []() {
		MessagePeopleReq proto;
		proto.set_peopleid(100);
		My_Client->request(&proto, [](google::protobuf::Message* rProto) {
		});
	};

	auto listener = UserEvent::addEventListener("MessagePeopleRsp", [&](EventCustom *event) {
		this->scheduleOnce([=](float t) {
			testRequest();
		}, 0.1, "testRequest");
	});
	//end test


	MessageLoginReq proto;
	My_Client->request(&proto, [=](google::protobuf::Message *rProto) {
		//µÇÂ½³É¹¦
		auto sProto = (MessageLoginRsp*)rProto;
		cout << "login success: " << sProto->playerid() << endl;
		//±£´æÍæ¼ÒID
		My_playerID = sProto->playerid();

		//test
		testRequest();
	});
	return true;
}



void GameLayer::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
