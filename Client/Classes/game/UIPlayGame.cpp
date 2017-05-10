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

//�Լ�������֮��ļ��
const float SELFPOKERDIS = 35.0f;

//�Լ��Ƶĳ�ʼYλ��
const float SELFPOKERY = 0;

//����ѡ�к����Ƶĸ߶�
const float POKERSELECTUPDIS = 20.0f;

//�ϼ��Ƶ�λ��
const Vec2 UPPLAYERPOKERPOS = Vec2(150, 280);
//�ϼ��Ƶı���
const float UPPLAYERPOKERSCALAE = 0.4;
//�¼��Ƶ�λ��
const Vec2 DOWNPLAYERPOKERPOS = Vec2(810, 280);
//�¼��Ƶı���
const float DOWNPLAYERPOKERSCALE = 0.4;

//ʱ�ӵ�λ��
const Vec2 BELLPOS[3] = {Vec2(480, 200), Vec2(220, 280), Vec2(740, 280)};
//ʱ�ӵı���
const float BELLSCALE[3] = { 0.8, 0.6, 0.6 };


//���а�ť�Ͳ�Ҫ��ť��λ��
const Vec2 NOTGRADPOS = Vec2(300, 200);
//�е�����ť�ͳ��ư�ť��λ��
const Vec2 GRADPOS = Vec2(660, 200);

//������Nodeλ��
const Vec2 LANDLORDPOKERNODEPOS = Vec2(480, 320);
//���������ű���
const float LANDLORDPOKERNODESCALE = 0.35;
//������֮�����
const float LANDLORDPOKERDIS = 50;

//��������Node��λ��
const Vec2 DESKPOKERNODEPOS = Vec2(480, 240);
//�������Ƶ����ű���
const float DESKPOKERNODESCALE = 0.5;
//��������֮��ľ���
const float DESKPOKERDIS = 40;

UIPlayGame::UIPlayGame() :
	upNum(0),
	downNum(0),
	recvPokerlistener(NULL),
	pokerNode(NULL),
	beganIdx(-1),
	recvStateListener(NULL),
	gameing(false),
	touching(false),
	bellSprite(NULL),
	gradButton(NULL),
	notGradButton(NULL),
	outButton(NULL),
	notOutButton(NULL),
	landlordPokerNode(NULL),
	deskPokerNode(NULL)
{
	lastMovePos = Vec2(0, 0);
	memset(this->lastPokerState, false, sizeof(this->lastPokerState));
}


bool UIPlayGame::init() {
	if (!UIPanel::init()) {
		return false;
	}
	this->createUI();

	//�����¼�
	this->recvPokerlistener = UserEvent::addEventListener("MessageDealRsp", [&](EventCustom* event) {
		//�Ƴ�ƥ���ж���
		auto matchingSp = this->getChildByTag(MATCHINGSPRITETAG);
		if ((NULL != matchingSp)) {
			matchingSp->removeFromParent();
		}
		MessageDealRsp* rProto = (MessageDealRsp*)event->getUserData();
		int pokerSize = rProto->pokerlist_size();

		vector<MessageDataPoker>tmpPokerList;
		for (int i = 0; i < pokerSize; i++) {
			MessageDataPoker tmpPoker = rProto->pokerlist(i);
			tmpPokerList.push_back(tmpPoker);
		}
		
		this->refreshSelfPoker(tmpPokerList, false);
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

//����UI
void UIPlayGame::createUI() {
	//����
	auto backSprite = Sprite::create("card_desk.png");
	backSprite->setPosition(Vec2(My_visibleSize.width * 0.5, My_visibleSize.height * 0.5));
	backSprite->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(backSprite);

	//���Լ��Ƶ�Node
	this->pokerNode = Node::create();
	this->pokerNode->setPosition(Vec2(My_visibleSize.width * 0.5 + 60, 170 * 0.5 * SELFPOKERSCALE + 10));
	this->pokerNode->setScale(SELFPOKERSCALE);
	this->addChild(this->pokerNode);
	//�ŵ����Ƶ�Node
	this->landlordPokerNode = Node::create();
	this->landlordPokerNode->setPosition(LANDLORDPOKERNODEPOS);
	this->landlordPokerNode->setScale(LANDLORDPOKERNODESCALE);
	this->addChild(this->landlordPokerNode);
	//�������Ƶ�Node
	this->deskPokerNode = Node::create();
	this->deskPokerNode->setPosition(DESKPOKERNODEPOS);
	this->deskPokerNode->setScale(DESKPOKERNODESCALE);
	this->addChild(this->deskPokerNode);

	//����ʱ��
	this->bellSprite = Sprite::create("bell.png");
	this->bellSprite->setPosition(BELLPOS[0]);
	this->bellSprite->setScale(BELLSCALE[0]);
	this->addChild(bellSprite);
	this->bellSprite->setVisible(false);


	//����������Button
	this->gradButton = ui::Button::create("grad_landlord_n.png", "grad_landlord_h.png");
	this->gradButton->setPosition(GRADPOS);
	this->addChild(this->gradButton);
	this->gradButton->addTouchEventListener([&](Ref* node, ui::Widget::TouchEventType tType) {
		if (Widget::TouchEventType::ENDED == tType) {
			this->gradButtonCallback(true);
		}
	});
	//����Button
	this->notGradButton = ui::Button::create("not_grad_landlord_n.png", "not_grad_landlord_h.png");
	this->notGradButton->setPosition(NOTGRADPOS);
	this->addChild(this->notGradButton);
	this->notGradButton->addTouchEventListener([&](Ref* node, ui::Widget::TouchEventType tType) {
		if (Widget::TouchEventType::ENDED == tType) {
			this->gradButtonCallback(false);
		}
	});
	//����
	this->outButton = ui::Button::create("out_n.png", "out_h.png");
	this->outButton->setPosition(GRADPOS);
	this->addChild(this->outButton);
	this->outButton->addTouchEventListener([&](Ref* node, ui::Widget::TouchEventType tType) {
		if (Widget::TouchEventType::ENDED == tType) {
			this->outButtonCallback(true);
		}
	});
	//����
	this->notOutButton = ui::Button::create("not_out_n.png", "not_out_h.png");
	this->notOutButton->setPosition(NOTGRADPOS);
	this->addChild(this->notOutButton);
	this->notOutButton->addTouchEventListener([&](Ref* node, ui::Widget::TouchEventType tType) {
		if (Widget::TouchEventType::ENDED == tType) {
			this->outButtonCallback(false);
		}
	});
	//Ĭ������
	this->setGradUIEnabled(false);
	this->setOutUIEnabled(false);
	//this->setCountDown(2, 10);

	//test
	MessageUpdateStateRsp proto;
	proto.set_playeridx(1);
	proto.set_statetype(1);
	proto.set_endtime(My_client->getServerTime() + 10.0);
	for (int i = 0; i < 5; i++) {
		auto tmpPoker = proto.add_midpoker();
		tmpPoker->set_color(1);
		tmpPoker->set_number(10);
	}
	for (int i = 0; i < 3; i++) {
		auto tmpPoker = proto.add_landlordpoker();
		tmpPoker->set_color(1);
		tmpPoker->set_number(13);
	}
	this->refreshState(&proto);
	//end test
}

//��ʾ������UI
void UIPlayGame::setGradUIEnabled(bool state) {
	this->gradButton->setVisible(state);
	this->notGradButton->setVisible(state);
}
//��ʾ����UI
void UIPlayGame::setOutUIEnabled(bool state) {
	this->outButton->setVisible(state);
	this->notOutButton->setVisible(state);
}
//����ʱ�ӵ���ʱ(pos��0���Լ���2.�¼ң�3.�¼ң�
void UIPlayGame::setCountDown(int pos, int counts, function<void()> callback) {
	static function<void()> _callback = callback;
	_callback = callback;
	static int lastTime = 0;
	lastTime = counts;
	if (lastTime <= 0) {
		if (NULL != _callback) {
			_callback();
		}
		return;
	}
	//ʱ��λ��
	this->bellSprite->setPosition(BELLPOS[pos]);
	//ʱ�ӱ���
	this->bellSprite->setScale(BELLSCALE[pos]);

	this->schedule([&](float t) {
		this->bellSprite->setVisible(true);
		this->bellSprite->removeAllChildren();

		auto tmpNode = My_getSpriteNumber("number/number_red.png", lastTime);
		auto tmpSize = this->bellSprite->getContentSize();
		tmpNode->setPosition(Vec2(tmpSize.width * 0.5, tmpSize.height * 0.5));
		this->bellSprite->addChild(tmpNode);
		if (lastTime <= 0){
			this->bellSprite->setVisible(false);
			if (NULL != _callback) {
				_callback();
			}
		}
		lastTime = lastTime - 1;
	}, 1.0, counts, 0, "CountDown");
}


//�е�����ť�����а�ť�ص�����(state �Ƿ�е�����
void UIPlayGame::gradButtonCallback(bool state) {
	cout << "gradButtonCallback: state = " << state << endl;
	MessageGradLandlordReq proto;
	proto.set_isgrad(state);
	My_client->request(&proto, [](google::protobuf::Message* rProto) {

	});
}
//���ư�ť��������ť�ص�����(state �Ƿ���ƣ�
void UIPlayGame::outButtonCallback(bool state) {
	cout << "outButtonCallback: state = " << state << endl;
	MessageOutPokerReq proto;
	if (true == state) {
		for (int i = 0; i < this->selPoker.size(); i++) {
			auto tmpPoker = this->selPoker[i];
			auto addPoker= proto.add_poker();
			(*addPoker) = tmpPoker->getPoker();
		}
	}
	My_client->request(&proto, [](google::protobuf::Message* rProto) {

	});
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
	backSp_up->setPosition(UPPLAYERPOKERPOS);
	backSp_up->setScale(UPPLAYERPOKERSCALAE);
	this->addChild(backSp_up, 1, UPPLAYERPOKERTAG);
	//�¼�
	auto backSp_down = UIPoker::create();
	backSp_down->setPosition(DOWNPLAYERPOKERPOS);
	backSp_down->setScale(DOWNPLAYERPOKERSCALE);
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


//ˢ���Լ����е���
void UIPlayGame::refreshSelfPoker(vector<MessageDataPoker> &pokerList, bool state) {
	if (0 == pokerList.size()) {
		return;
	}
	//�Ƴ����е���
	this->poker.clear();
	this->pokerNode->removeAllChildren();

	//����
	sort(pokerList.begin(), pokerList.end(), My_pokerCmd);
	auto pokerSum = pokerList.size();
	for (int i = 0; i < pokerSum; i++) {
		//��������
		auto tmpPokerSp = UIPoker::create(&(pokerList[i]));
		tmpPokerSp->setPosition(Vec2((i + 0.5 - 0.5 * pokerSum) * SELFPOKERDIS, SELFPOKERY));
		tmpPokerSp->setVisible(state);
		this->pokerNode->addChild(tmpPokerSp, i, SELFPOKERTAG);

		//����
		this->poker.push_back(tmpPokerSp);
	}
}

//ˢ����Ϸ״̬
void UIPlayGame::refreshState(MessageUpdateStateRsp *proto) {
	this->setGradUIEnabled(false);
	this->setOutUIEnabled(false);
	//��ʾ����ʱ
	auto lastTIme = (proto->endtime() - My_client->getServerTime());
	this->setCountDown(proto->playeridx(), int(lastTIme - 0.5), [&]() {
		this->setGradUIEnabled(false);
		this->setOutUIEnabled(false);

		//vector<MessageDataPoker> tmpList;
		//auto tmp1 = MessageDataPoker();
		//tmp1.set_color(3);
		//tmp1.set_number(3);
		//tmpList.push_back(tmp1);
		//this->refreshSelfPoker(tmpList);

	});
	if (0 < proto->landlordpoker_size()) {
		//��ʾ������
		vector<MessageDataPoker> tmpLandlordPokerList;
		for (int i = 0; i < proto->landlordpoker_size(); i++) {
			tmpLandlordPokerList.push_back(proto->landlordpoker(i));
		}
		//����
		sort(tmpLandlordPokerList.begin(), tmpLandlordPokerList.end(), My_pokerCmd);
		this->landlordPokerNode->removeAllChildren();
		auto pokerSum = tmpLandlordPokerList.size();
		for (int i = 0; i < pokerSum; i++) {
			auto tmpPoker = UIPoker::create(&(tmpLandlordPokerList[i]));
			tmpPoker->setPosition(Vec2((i + 0.5 - 0.5 * pokerSum) * LANDLORDPOKERDIS, 0));
			this->landlordPokerNode->addChild(tmpPoker, i);
		}

	}
	if (0 < proto->midpoker_size()) {
		//��ʾ��������
		vector<MessageDataPoker> tmpDeskPokerList;
		for (int i = 0; i < proto->midpoker_size(); i++) {
			tmpDeskPokerList.push_back(proto->midpoker(i));
		}
		//����
		sort(tmpDeskPokerList.begin(), tmpDeskPokerList.end(), My_pokerCmd);
		this->deskPokerNode->removeAllChildren();
		auto pokerSum = tmpDeskPokerList.size();
		for (int i = 0; i < pokerSum; i++) {
			auto tmpPoker = UIPoker::create(&(tmpDeskPokerList[i]));
			tmpPoker->setPosition(Vec2((i + 0.5 - 0.5 * pokerSum) * DESKPOKERDIS, 0));
			this->deskPokerNode->addChild(tmpPoker, i);
		}
	}

	if (1 == proto->statetype()) {
		//������
		this->setGradUIEnabled(0 == proto->playeridx());


	} else if (2 == proto->statetype()) {
		//����
		//�����������Լ�����ʾ
		this->setOutUIEnabled(0 == proto->playeridx());
	}
	//ˢ���Լ�������
	int pokerSize = proto->selfpoker_size();
	vector<MessageDataPoker>tmpPokerList;
	for (int i = 0; i < pokerSize; i++) {
		MessageDataPoker tmpPoker = proto->selfpoker(i);
		tmpPokerList.push_back(tmpPoker);
	}
	this->refreshSelfPoker(tmpPokerList);
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
		this->touching = false;
		return true;
	}
	//���濨��״̬
	for (int i = 0; i < this->poker.size(); i++) {
		this->lastPokerState[i] = this->poker[i]->isSelectEnabled();
	}
	this->setStateInInterval(this->beganIdx, this->beganIdx);
	this->touching = true;
	return true;
}
void UIPlayGame::touchMoved(Touch *touch, Event* event) {
	if (false == gameing || false == touching) {
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
	if (false == gameing || false == touching) {
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
