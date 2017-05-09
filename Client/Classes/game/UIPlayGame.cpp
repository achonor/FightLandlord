#include "stdafx.h"
#include "GGData.h"
#include "UIPlayGame.h"
#include "Event/UserEvent.h"
#include "UIPoker.h"

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
const float SELFPOKERSCALE = 0.80;

//发牌定时器的key
const std::string DEALSCHEDULERKEY = "DEALSCHEDULERKEY";

//两张牌之间的间距
const float POKERDIS = 35.0f;

//自己牌的初始Y位置
const float SELFPOKERY = 0;

//卡牌选中后上移的高度
const float POKERSELECTUPDIS = 20.0f;


UIPlayGame::UIPlayGame() :
	upNum(0),
	downNum(0),
	recvPokerlistener(NULL),
	pokerNode(NULL),
	beganIdx(-1),
	recvStateListener(NULL),
	gameing(false)
{
	lastMovePos = Vec2(0, 0);
	memset(this->lastPokerState, false, sizeof(this->lastPokerState));
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

	//发牌事件
	this->recvPokerlistener = UserEvent::addEventListener("MessageDealRsp", [&](EventCustom* event) {
		//移除匹配中动画
		auto matchingSp = this->getChildByTag(MATCHINGSPRITETAG);
		if ((NULL != matchingSp)) {
			matchingSp->removeFromParent();
		}
		//移除现有的牌
		this->poker.clear();
		this->pokerNode->removeAllChildren();

		MessageDealRsp* rProto = (MessageDealRsp*)event->getUserData();
		int pokerSize = rProto->pokerlist_size();
		
		vector<MessageDataPoker>tmpPokerList;
		for (int i = 0; i < pokerSize; i++) {
			MessageDataPoker tmpPoker = rProto->pokerlist(i);
			cout << tmpPoker.color() << tmpPoker.number() << " ";
			tmpPokerList.push_back(tmpPoker);
		}
		cout << endl;
		//排序
		sort(tmpPokerList.begin(), tmpPokerList.end(), [](MessageDataPoker &a, MessageDataPoker &b) {
			if (a.number() != b.number()) {
				return b.number() < a.number();
			}else if(a.color() != b.color()) {
				return a.color() < b.color();
			}
			return false;
		});
		auto pokerSum = tmpPokerList.size();
		for (int i = 0; i < pokerSum; i++) {
			//创建卡牌
			auto tmpPokerSp = UIPoker::create(&(tmpPokerList[i]));
			tmpPokerSp->setPosition(Vec2((i + 0.5 - 0.5 * pokerSum) * POKERDIS, SELFPOKERY));
			tmpPokerSp->setScale(SELFPOKERSCALE);
			tmpPokerSp->setVisible(false);
			this->pokerNode->addChild(tmpPokerSp, i, SELFPOKERTAG);

			//保存
			this->poker.push_back(tmpPokerSp);
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
}

//显示发牌动画
void UIPlayGame::showDealAction() {
	//铺着的牌,中间
	auto backSp_mid = UIPoker::create();
	backSp_mid->setPosition(Vec2(My_visibleSize.width * 0.5, My_visibleSize.height * 0.5));
	backSp_mid->setScale(BACKPOKERSCALE);
	this->addChild(backSp_mid, 1, MIDPOKERTAG);
	//上家
	auto backSp_up = UIPoker::create();
	backSp_up->setPosition(Vec2(150, 280));
	backSp_up->setScale(BACKPOKERSCALE);
	this->addChild(backSp_up, 1, UPPLAYERPOKERTAG);
	//下家
	auto backSp_down = UIPoker::create();
	backSp_down->setPosition(Vec2(810, 280));
	backSp_down->setScale(BACKPOKERSCALE);
	this->addChild(backSp_down, 1, DOWNPLAYERPOKERTAG);

	static int pokerNum = 0;
	pokerNum = this->poker.size();

	this->schedule([&](float t) {
		auto pokerSum = this->poker.size();
		auto pokerIdx = pokerSum - pokerNum;
		//动作卡牌
		auto actionPoker = UIPoker::create();
		actionPoker->setPosition(Vec2(My_visibleSize.width * 0.5, My_visibleSize.height * 0.5));
		actionPoker->setScale(BACKPOKERSCALE);
		this->addChild(actionPoker, 1, ACTIONPOKERTAG);
		//动画
		auto tmpPos = this->pokerNode->convertToWorldSpace(this->poker[pokerIdx]->getPosition());
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
			//动画执行完，开始游戏
			this->startGame();
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

//开始游戏
void UIPlayGame::startGame() {
	this->gameing = true;
	//隐藏中间的牌
	auto midPokerSp = this->getChildByTag(MIDPOKERTAG);
	if (NULL != midPokerSp) {
		midPokerSp->removeFromParent();
	}
	//监听游戏状态
	this->recvStateListener = UserEvent::addEventListener("MessageUpdateStateRsp", [&](EventCustom* event) {
		//刷新状态
		auto rProto = (MessageUpdateStateRsp*)event->getUserData();
		this->refreshState(rProto);
	});
}


//刷新游戏状态
void UIPlayGame::refreshState(MessageUpdateStateRsp *proto) {
	if (1 == proto->statetype) {
		//抢地主

	} else if (2 == proto->statetype) {
		//出牌
	}
	//显示时钟
}



//设置一个卡牌的状态(不往上移)
void UIPlayGame::setPokerState(int idx, bool state) {
	auto tmpPoker = this->poker[idx];
	if (tmpPoker->isSelectEnabled() == state) {
		return;
	}
	tmpPoker->setSelectEnabled(state);
	auto tmpPos = tmpPoker->getPosition();
}
//重设所有卡牌
void UIPlayGame::resetAllPoker() {
	for (int i = 0; i < this->poker.size(); i++) {
		this->setPokerState(i, false);
		this->poker[i]->setPositionY(SELFPOKERY);
	}
	this->selPoker.clear();
}

//修改一个区间的牌的状态
void UIPlayGame::setStateInInterval(int startIdx, int endIdx) {
	if (endIdx < startIdx) {
		swap(startIdx, endIdx);
	}
	for (int i = 0; i < this->poker.size(); i++) {
		bool state = this->lastPokerState[i];
		if (startIdx <= i && i <= endIdx) {
			state = (!state);
		}
		this->setPokerState(i, state);
	}
}

//判断触摸点在那个牌上
int UIPlayGame::checkTouchInPoker(Vec2 &pos) {
	auto touchPos = this->pokerNode->convertToNodeSpace(pos);
	for (int i = this->poker.size() - 1; 0 <= i; i--) {
		auto tmpPoker = this->poker[i];
		if (tmpPoker->getBoundingBox().containsPoint(touchPos)) {
			return i;
		}
	}
	return -1;
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


bool UIPlayGame::touchBegan(Touch *touch, Event* event) {
	if (false == gameing) {
		//游戏还没开始
		return true;
	}

	this->lastMovePos = touch->getLocation();
	//触摸点在那个卡牌
	this->beganIdx = this->checkTouchInPoker(this->lastMovePos);
	if (-1 == this->beganIdx) {
		//还原选中的卡牌
		this->resetAllPoker();
		return false;
	}
	//保存卡牌状态
	for (int i = 0; i < this->poker.size(); i++) {
		this->lastPokerState[i] = this->poker[i]->isSelectEnabled();
	}
	this->setStateInInterval(this->beganIdx, this->beganIdx);
	return true;
}
void UIPlayGame::touchMoved(Touch *touch, Event* event) {
	if (false == gameing) {
		//游戏还没开始
		return;
	}
	auto tmpPos = touch->getLocation();
	if (1.0 < My_calcPostionDis(this->lastMovePos, tmpPos)) {
		this->lastMovePos = tmpPos;
		auto tmpIdx = this->checkTouchInPoker(this->lastMovePos);
		if (0 <= tmpIdx) {
			this->setStateInInterval(this->beganIdx, tmpIdx);
		}
	}
}
void UIPlayGame::touchEnded(Touch *touch, Event* event) {
	if (false == gameing) {
		//游戏还没开始
		return;
	}
	this->beganIdx = -1;
	this->selPoker.clear();
	for (int i = 0; i < this->poker.size(); i++) {
		if (false == this->poker[i]->isSelectEnabled()) {
			//没有选中
			this->poker[i]->setPositionY(SELFPOKERY);
		} else {
			//选中的上移
			this->poker[i]->setPositionY(POKERSELECTUPDIS);
			selPoker.push_back(this->poker[i]);
		}
	}
}



UIPlayGame::~UIPlayGame() {
	//if(NULL != this->recvPokerlistener){
	//	this->recvPokerlistener->removeEventListener();
	//}
}
