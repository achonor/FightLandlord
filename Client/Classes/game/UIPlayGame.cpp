#include "stdafx.h"
#include "GGData.h"
#include "UIPlayGame.h"



UIPlayGame::UIPlayGame() {
}


bool UIPlayGame::init() {
	if (!UIPanel::init()) {
		return false;
	}
	
	auto backSprite = Sprite::create("card_desk.png");
	backSprite->setPosition(Vec2(My_visibleSize.width * 0.5, My_visibleSize.height * 0.5));
	backSprite->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(backSprite);

	//请求开始游戏
	this->requestStartGame();
	
	return true;
}

void UIPlayGame::onEnter() {
	UIPanel::onEnter();

	

	//this->schedule([&](float t) {
	//	static int counts = 15;
	//	int COUNTSDOWNSPTAG = 100;
	//	if (NULL != this->getChildByTag(COUNTSDOWNSPTAG)) {
	//		this->removeChildByTag(COUNTSDOWNSPTAG);
	//	}
	//	auto tmpNumSp = My_getSpriteNumber("number/number_white.png", counts);
	//	tmpNumSp->setPosition(Vec2(My_visibleSize.width* 0.5, My_visibleSize.height * 0.5));
	//	this->addChild(tmpNumSp, 1, COUNTSDOWNSPTAG);
	//	counts--;
	//}, 1, "testCountDown");

}

//请求开始游戏
void UIPlayGame::requestStartGame() {
	//请求开始游戏
	MessageStartGameReq proto;
	My_client->request(&proto, [&](google::protobuf::Message* rProto) {
		rProto = (MessageStartGameRsp*)rProto;
		//匹配完成 开始游戏

	});
}
//请求获取牌
void UIPlayGame::requestGetPoker() {

}


UIPlayGame::~UIPlayGame() {
}
