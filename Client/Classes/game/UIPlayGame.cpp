#include "stdafx.h"
#include "GGData.h"
#include "UIPlayGame.h"
#include "Event/UserEvent.h"
#include <algorithm>

//匹配中图的TAG
const int MATCHINGSPRITETAG = 100;

//中间牌的TAG
const int MIDPOKERTAG = 110;
//上家牌的TAG
const int UPPLAYERPOKERTAG = 120;
//下家牌的TAG
const int DOWNPLAYERPOKERTAG = 130;

//上家牌数字的TAG
const int UPPLAYERPOKERNUMTAG = 140;
//下家牌数字的TAG
const int DOWNPLAYERPOKERNUMTAG = 150;

//自己牌的TAG(发牌时候有效）
const int SELFPOKERTAG = 160;

//执行动画的牌的TAG
const int ACTIONPOKERTAG = 170;

//背面卡牌显示比例
const float BACKPOKERSCALE = 0.5;

//自己卡牌显示比例
const float SELFPOKERSCALE = 0.68;

//发牌定时器的key
const std::string DEALSCHEDULERKEY = "DEALSCHEDULERKEY";

//两张牌之间的间距
const float POKERDIS = 35.0f;


UIPlayGame::UIPlayGame():
	upNum(0),
	downNum(0),
	recvPokerlistener(NULL),
	pokerNode(NULL)
{
}


bool UIPlayGame::init() {
	if (!UIPanel::init()) {
		return false;
	}
	//背景
	auto backSprite = Sprite::create("card_desk.png");
	backSprite->setPosition(Vec2(My_visibleSize.width * 0.5, My_visibleSize.height * 0.5));
	backSprite->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(backSprite);

	//放牌的Node
	this->pokerNode = Node::create();
	this->pokerNode->setPosition(Vec2(My_visibleSize.width * 0.5 + 60, 170 * 0.5 * SELFPOKERSCALE + 10));
	this->addChild(this->pokerNode);

	this->recvPokerlistener = UserEvent::addEventListener("MessageDealRsp", [&](EventCustom* event) {
		//移除匹配中动画
		auto matchingSp = this->getChildByTag(MATCHINGSPRITETAG);
		if ((NULL != matchingSp)) {
			matchingSp->removeFromParent();
		}

		MessageDealRsp* rProto = (MessageDealRsp*)event->getUserData();
		int pokerSize = rProto->pokerlist_size();
		this->poker.clear();
		for (int i = 0; i < pokerSize; i++) {
			MessageDataPoker tmpPoker = rProto->pokerlist(i);
			cout << tmpPoker.color() << tmpPoker.number() << " ";
			this->poker.push_back(tmpPoker);
		}
		cout << endl;
		//排序
		sort(this->poker.begin(), this->poker.end(), [](MessageDataPoker &a, MessageDataPoker &b) {
			if (a.number() != b.number()) {
				return b.number() < a.number();
			}else if(a.color() != b.color()) {
				return a.color() < b.color();
			}
			return false;
		});

		for (int i = 0; i < this->poker.size(); i++) {
			cout << this->poker[i].color() << this->poker[i].number() << " ";
		}
		cout << endl;
		//显示发牌动画
		this->showDealAction();
	});

	//请求开始游戏
	this->requestStartGame();

	//显示正在匹配玩家
	auto matchingSp = Sprite::create("imgword/matching.png");
	matchingSp->setPosition(Vec2(My_visibleSize.width * 0.5, My_visibleSize.height * 0.5));
	this->addChild(matchingSp, 1, MATCHINGSPRITETAG);

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

//显示发牌动画
void UIPlayGame::showDealAction() {
	//铺着的牌,中间
	auto backSp_mid = Sprite::create("poker_card/pokerpoker_back_1.png");
	backSp_mid->setPosition(Vec2(My_visibleSize.width * 0.5, My_visibleSize.height * 0.5));
	backSp_mid->setScale(BACKPOKERSCALE);
	this->addChild(backSp_mid, 1, MIDPOKERTAG);
	//上家
	auto backSp_up = Sprite::create("poker_card/pokerpoker_back_1.png");
	backSp_up->setPosition(Vec2(150, 280));
	backSp_up->setScale(BACKPOKERSCALE);
	this->addChild(backSp_up, 1, UPPLAYERPOKERTAG);
	//下家
	auto backSp_down = Sprite::create("poker_card/pokerpoker_back_1.png");
	backSp_down->setPosition(Vec2(810, 280));
	backSp_down->setScale(BACKPOKERSCALE);
	this->addChild(backSp_down, 1, DOWNPLAYERPOKERTAG);

	static int pokerNum = 0;
	pokerNum = this->poker.size();

	this->schedule([&](float t) {
		auto pokerSum = this->poker.size();
		auto pokerIdx = pokerSum - pokerNum;
		//创建卡牌
		char tmpName[35];
		sprintf(tmpName, "poker_card/poker_%d_%d.png", this->poker[pokerIdx].color(), this->poker[pokerIdx].number());
		auto tmpPokerSp = Sprite::create(std::string(tmpName));
		tmpPokerSp->setPosition(Vec2((pokerIdx + 0.5 - 0.5 * pokerSum) * POKERDIS, 0));
		tmpPokerSp->setScale(SELFPOKERSCALE);
		tmpPokerSp->setVisible(false);
		this->pokerNode->addChild(tmpPokerSp, pokerIdx, SELFPOKERTAG);
		//动作卡牌
		auto actionPoker = Sprite::create("poker_card/pokerpoker_back_1.png");
		actionPoker->setPosition(Vec2(My_visibleSize.width * 0.5, My_visibleSize.height * 0.5));
		actionPoker->setScale(BACKPOKERSCALE);
		this->addChild(actionPoker, 1, ACTIONPOKERTAG);
		//动画
		auto tmpPos = this->pokerNode->convertToWorldSpace(tmpPokerSp->getPosition());
		auto tmpMove = MoveTo::create(0.2, tmpPos);
		actionPoker->runAction(Sequence::create(tmpMove, CallFunc::create([&]() {
			this->removeChildByTag(ACTIONPOKERTAG);
			auto tmpSelfPokerSp = this->pokerNode->getChildByTag(SELFPOKERTAG);
			if (NULL != tmpSelfPokerSp) {
				tmpSelfPokerSp->setVisible(true);
				tmpSelfPokerSp->setTag(-1);
			}
			if (1 < pokerNum) {
				return;
			}
			auto midPokerSp = this->getChildByTag(MIDPOKERTAG);
			if (NULL != midPokerSp) {
				midPokerSp->removeFromParent();
			}
		}), NULL));

		pokerNum = pokerNum - 1;
		//上家，下家牌的数字
		auto tmpUpSp = this->getChildByTag(UPPLAYERPOKERTAG);
		if (NULL != tmpUpSp) {
			tmpUpSp->removeChildByTag(UPPLAYERPOKERNUMTAG);
			auto tmpUpNumSp = My_getSpriteNumber("number/number_blue.png", pokerSum - pokerNum);
			Size tmpSize = tmpUpSp->getContentSize();
			tmpUpNumSp->setPosition(Vec2(tmpSize.width * 0.5, tmpSize.height * 0.5));
			tmpUpNumSp->setScale(3.0);
			tmpUpSp->addChild(tmpUpNumSp, 1, UPPLAYERPOKERNUMTAG);
		}
		auto tmpDownSp = this->getChildByTag(DOWNPLAYERPOKERTAG);
		if (NULL != tmpDownSp) {
			tmpDownSp->removeChildByTag(DOWNPLAYERPOKERNUMTAG);
			auto tmpDownNumSp = My_getSpriteNumber("number/number_blue.png", pokerSum - pokerNum);
			Size tmpSize = tmpDownSp->getContentSize();
			tmpDownNumSp->setPosition(Vec2(tmpSize.width * 0.5, tmpSize.height * 0.5));
			tmpDownNumSp->setScale(3.0);
			tmpDownSp->addChild(tmpDownNumSp, 1, DOWNPLAYERPOKERNUMTAG);
		}

	}, 0.1, pokerNum - 1, 0.0, "DEALSCHEDULERKEY");

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
	MessageDealReq proto;
	My_client->request(&proto, [&](google::protobuf::Message* rProto) {
		//事件监听的地方处理
	});
}


UIPlayGame::~UIPlayGame() {
	//if(NULL != this->recvPokerlistener){
	//	this->recvPokerlistener->removeEventListener();
	//}
}
