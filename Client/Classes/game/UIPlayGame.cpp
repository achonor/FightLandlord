#include "stdafx.h"
#include "GGData.h"
#include "UIPlayGame.h"
#include "Event/UserEvent.h"
#include "UIPoker.h"

#include <algorithm>

//ƥ����ͼ��TAG
const int MATCHINGSPRITETAG = 100;

//�м��Ƶ�TAG
const int MIDPOKERTAG = 110;
//�ϼ��Ƶ�TAG
const int UPPLAYERPOKERTAG = 120;
//�¼��Ƶ�TAG
const int DOWNPLAYERPOKERTAG = 130;

//�ϼ������ֵ�TAG
const int UPPLAYERPOKERNUMTAG = 140;
//�¼������ֵ�TAG
const int DOWNPLAYERPOKERNUMTAG = 150;

//�Լ��Ƶ�TAG(����ʱ����Ч��
const int SELFPOKERTAG = 160;

//ִ�ж������Ƶ�TAG
const int ACTIONPOKERTAG = 170;

//���濨����ʾ����
const float BACKPOKERSCALE = 0.5;

//�Լ�������ʾ����
const float SELFPOKERSCALE = 0.80;

//���ƶ�ʱ����key
const std::string DEALSCHEDULERKEY = "DEALSCHEDULERKEY";

//������֮��ļ��
const float POKERDIS = 35.0f;

//�Լ��Ƶĳ�ʼYλ��
const float SELFPOKERY = 0;

//����ѡ�к����Ƶĸ߶�
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
	//����
	auto backSprite = Sprite::create("card_desk.png");
	backSprite->setPosition(Vec2(My_visibleSize.width * 0.5, My_visibleSize.height * 0.5));
	backSprite->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(backSprite);

	//���Ƶ�Node
	this->pokerNode = Node::create();
	this->pokerNode->setPosition(Vec2(My_visibleSize.width * 0.5 + 60, 170 * 0.5 * SELFPOKERSCALE + 10));
	this->addChild(this->pokerNode);

	//�����¼�
	this->recvPokerlistener = UserEvent::addEventListener("MessageDealRsp", [&](EventCustom* event) {
		//�Ƴ�ƥ���ж���
		auto matchingSp = this->getChildByTag(MATCHINGSPRITETAG);
		if ((NULL != matchingSp)) {
			matchingSp->removeFromParent();
		}
		//�Ƴ����е���
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
		//����
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
			//��������
			auto tmpPokerSp = UIPoker::create(&(tmpPokerList[i]));
			tmpPokerSp->setPosition(Vec2((i + 0.5 - 0.5 * pokerSum) * POKERDIS, SELFPOKERY));
			tmpPokerSp->setScale(SELFPOKERSCALE);
			tmpPokerSp->setVisible(false);
			this->pokerNode->addChild(tmpPokerSp, i, SELFPOKERTAG);

			//����
			this->poker.push_back(tmpPokerSp);
		}
		cout << endl;
		//��ʾ���ƶ���
		this->showDealAction();
	});

	//����ʼ��Ϸ
	this->requestStartGame();

	//��ʾ����ƥ�����
	auto matchingSp = Sprite::create("imgword/matching.png");
	matchingSp->setPosition(Vec2(My_visibleSize.width * 0.5, My_visibleSize.height * 0.5));
	this->addChild(matchingSp, 1, MATCHINGSPRITETAG);

	return true;
}

void UIPlayGame::onEnter() {
	UIPanel::onEnter();
}

//��ʾ���ƶ���
void UIPlayGame::showDealAction() {
	//���ŵ���,�м�
	auto backSp_mid = UIPoker::create();
	backSp_mid->setPosition(Vec2(My_visibleSize.width * 0.5, My_visibleSize.height * 0.5));
	backSp_mid->setScale(BACKPOKERSCALE);
	this->addChild(backSp_mid, 1, MIDPOKERTAG);
	//�ϼ�
	auto backSp_up = UIPoker::create();
	backSp_up->setPosition(Vec2(150, 280));
	backSp_up->setScale(BACKPOKERSCALE);
	this->addChild(backSp_up, 1, UPPLAYERPOKERTAG);
	//�¼�
	auto backSp_down = UIPoker::create();
	backSp_down->setPosition(Vec2(810, 280));
	backSp_down->setScale(BACKPOKERSCALE);
	this->addChild(backSp_down, 1, DOWNPLAYERPOKERTAG);

	static int pokerNum = 0;
	pokerNum = this->poker.size();

	this->schedule([&](float t) {
		auto pokerSum = this->poker.size();
		auto pokerIdx = pokerSum - pokerNum;
		//��������
		auto actionPoker = UIPoker::create();
		actionPoker->setPosition(Vec2(My_visibleSize.width * 0.5, My_visibleSize.height * 0.5));
		actionPoker->setScale(BACKPOKERSCALE);
		this->addChild(actionPoker, 1, ACTIONPOKERTAG);
		//����
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
			//����ִ���꣬��ʼ��Ϸ
			this->startGame();
		}), NULL));

		pokerNum = pokerNum - 1;
		//�ϼң��¼��Ƶ�����
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

//��ʼ��Ϸ
void UIPlayGame::startGame() {
	this->gameing = true;
	//�����м����
	auto midPokerSp = this->getChildByTag(MIDPOKERTAG);
	if (NULL != midPokerSp) {
		midPokerSp->removeFromParent();
	}
	//������Ϸ״̬
	this->recvStateListener = UserEvent::addEventListener("MessageUpdateStateRsp", [&](EventCustom* event) {
		//ˢ��״̬
		auto rProto = (MessageUpdateStateRsp*)event->getUserData();
		this->refreshState(rProto);
	});
}


//ˢ����Ϸ״̬
void UIPlayGame::refreshState(MessageUpdateStateRsp *proto) {
	if (1 == proto->statetype) {
		//������

	} else if (2 == proto->statetype) {
		//����
	}
	//��ʾʱ��
}



//����һ�����Ƶ�״̬(��������)
void UIPlayGame::setPokerState(int idx, bool state) {
	auto tmpPoker = this->poker[idx];
	if (tmpPoker->isSelectEnabled() == state) {
		return;
	}
	tmpPoker->setSelectEnabled(state);
	auto tmpPos = tmpPoker->getPosition();
}
//�������п���
void UIPlayGame::resetAllPoker() {
	for (int i = 0; i < this->poker.size(); i++) {
		this->setPokerState(i, false);
		this->poker[i]->setPositionY(SELFPOKERY);
	}
	this->selPoker.clear();
}

//�޸�һ��������Ƶ�״̬
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

//�жϴ��������Ǹ�����
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


//����ʼ��Ϸ
void UIPlayGame::requestStartGame() {
	//����ʼ��Ϸ
	MessageStartGameReq proto;
	My_client->request(&proto, [&](google::protobuf::Message* rProto) {
		rProto = (MessageStartGameRsp*)rProto;
		//ƥ����� ��ʼ��Ϸ

	});
}
//�����ȡ��
void UIPlayGame::requestGetPoker() {
	MessageDealReq proto;
	My_client->request(&proto, [&](google::protobuf::Message* rProto) {
		//�¼������ĵط�����
	});
}


bool UIPlayGame::touchBegan(Touch *touch, Event* event) {
	if (false == gameing) {
		//��Ϸ��û��ʼ
		return true;
	}

	this->lastMovePos = touch->getLocation();
	//���������Ǹ�����
	this->beganIdx = this->checkTouchInPoker(this->lastMovePos);
	if (-1 == this->beganIdx) {
		//��ԭѡ�еĿ���
		this->resetAllPoker();
		return false;
	}
	//���濨��״̬
	for (int i = 0; i < this->poker.size(); i++) {
		this->lastPokerState[i] = this->poker[i]->isSelectEnabled();
	}
	this->setStateInInterval(this->beganIdx, this->beganIdx);
	return true;
}
void UIPlayGame::touchMoved(Touch *touch, Event* event) {
	if (false == gameing) {
		//��Ϸ��û��ʼ
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
		//��Ϸ��û��ʼ
		return;
	}
	this->beganIdx = -1;
	this->selPoker.clear();
	for (int i = 0; i < this->poker.size(); i++) {
		if (false == this->poker[i]->isSelectEnabled()) {
			//û��ѡ��
			this->poker[i]->setPositionY(SELFPOKERY);
		} else {
			//ѡ�е�����
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
