#include "stdafx.h"
#include "GGData.h"
#include "UIPlayGame.h"
#include "Event/UserEvent.h"
#include "UIPoker.h"
#include "checkPoker.h"

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
const float SELFPOKERSCALE = 0.90;

//发牌定时器的key
const std::string DEALSCHEDULERKEY = "DEALSCHEDULERKEY";

//自己两张牌之间的间距
const float SELFPOKERDIS = 35.0f;

//自己牌的初始Y位置
const float SELFPOKERY = 0;

//卡牌选中后上移的高度
const float POKERSELECTUPDIS = 20.0f;

//上家牌的位置
const Vec2 UPPLAYERPOKERPOS = Vec2(150, 280);
//上家牌的比例
const float UPPLAYERPOKERSCALAE = 0.4;
//下家牌的位置
const Vec2 DOWNPLAYERPOKERPOS = Vec2(810, 280);
//下家牌的比例
const float DOWNPLAYERPOKERSCALE = 0.4;

//时钟的位置
const Vec2 BELLPOS[3] = {Vec2(480, 200), Vec2(740, 280), Vec2(220, 280)};
//时钟的比例
const float BELLSCALE[3] = { 0.7, 0.6, 0.6 };

//地主冒的位置
const Vec2 LANDLORDSPRITEPOS[3] = { Vec2(160, 50), Vec2(860, 250), Vec2(100, 250) };
//地主冒缩放比例
const float LANDLORDSPRITESCALE[3] = { 0.7, 0.6, 0.6 };


//不叫按钮和不要按钮的位置
const Vec2 NOTGRADPOS = Vec2(300, 200);
//叫地主按钮和出牌按钮的位置
const Vec2 GRADPOS = Vec2(660, 200);

//地主牌Node位置
const Vec2 LANDLORDPOKERNODEPOS = Vec2(480, 500);
//地主牌缩放比例
const float LANDLORDPOKERNODESCALE = 0.4;
//地主牌之间距离
const float LANDLORDPOKERDIS = 50;

//牌桌方牌Node的位置
const Vec2 DESKPOKERNODEPOS = Vec2(480, 300);
//牌桌上牌的缩放比例
const float DESKPOKERNODESCALE = 0.5;
//牌桌上牌之间的距离
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
	deskPokerNode(NULL),
	notOutSprite(NULL),
	notGradSprite(NULL),
	gradSprite(NULL),
	landlordSprite(NULL),
	recvResultListener(NULL)
{
	lastMovePos = Vec2(0, 0);
	memset(this->lastPokerState, false, sizeof(this->lastPokerState));
}


bool UIPlayGame::init() {
	if (!UIPanel::init()) {
		return false;
	}
	this->createUI();
	
	//游戏结束监听
	this->recvResultListener = UserEvent::addEventListener("MessageGameResultRsp", [&](EventCustom* event) {
		MessageGameResultRsp* rProto = (MessageGameResultRsp*)event->getUserData();
		this->gameOver(rProto);
	});

	//发牌事件
	this->recvPokerlistener = UserEvent::addEventListener("MessageDealRsp", [&](EventCustom* event) {
		//移除匹配中动画
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

//创建UI
void UIPlayGame::createUI() {
	//背景
	auto backSprite = Sprite::create("card_desk.png");
	backSprite->setPosition(Vec2(My_visibleSize.width * 0.5, My_visibleSize.height * 0.5));
	backSprite->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(backSprite);

	//地主冒
	this->landlordSprite = Sprite::create("landlord.png");
	this->landlordSprite->setVisible(false);
	this->landlordSprite->setPosition(LANDLORDSPRITEPOS[0]);
	this->landlordSprite->setScale(LANDLORDSPRITESCALE[0]);
	this->addChild(this->landlordSprite);

	//放自己牌的Node
	this->pokerNode = Node::create();
	this->pokerNode->setPosition(Vec2(My_visibleSize.width * 0.5 + 80, 170 * 0.5 * SELFPOKERSCALE + 5));
	this->pokerNode->setScale(SELFPOKERSCALE);
	this->addChild(this->pokerNode);
	//放地主牌的Node
	this->landlordPokerNode = Node::create();
	this->landlordPokerNode->setPosition(LANDLORDPOKERNODEPOS);
	this->landlordPokerNode->setScale(LANDLORDPOKERNODESCALE);
	this->addChild(this->landlordPokerNode);
	//牌桌上牌的Node
	this->deskPokerNode = Node::create();
	this->deskPokerNode->setPosition(DESKPOKERNODEPOS);
	this->deskPokerNode->setScale(DESKPOKERNODESCALE);
	this->addChild(this->deskPokerNode);
	//不出Sprite
	this->notOutSprite = Sprite::create("not_out.png");
	this->notOutSprite->setPosition(BELLPOS[0]); //倒计时钟放一个位置
	this->notOutSprite->setVisible(false);
	this->addChild(this->notOutSprite);
	//不抢Sprite
	this->notGradSprite = Sprite::create("not_grad.png");
	this->notGradSprite->setPosition(BELLPOS[0]); //倒计时钟放一个位置
	this->notGradSprite->setVisible(false);
	this->addChild(this->notGradSprite);
	//抢地主Sprite
	this->gradSprite = Sprite::create("grad.png");
	this->gradSprite->setPosition(BELLPOS[0]); //倒计时钟放一个位置
	this->gradSprite->setVisible(false);
	this->addChild(this->gradSprite);

	//上家牌
	auto backSp_up = UIPoker::create();
	backSp_up->setPosition(UPPLAYERPOKERPOS);
	backSp_up->setScale(UPPLAYERPOKERSCALAE);
	backSp_up->setVisible(false);
	this->addChild(backSp_up, 1, UPPLAYERPOKERTAG);
	//下家牌
	auto backSp_down = UIPoker::create();
	backSp_down->setPosition(DOWNPLAYERPOKERPOS);
	backSp_down->setScale(DOWNPLAYERPOKERSCALE);
	backSp_down->setVisible(false);
	this->addChild(backSp_down, 1, DOWNPLAYERPOKERTAG);

	//创建时钟
	this->bellSprite = Sprite::create("bell.png");
	this->bellSprite->setPosition(BELLPOS[0]);
	this->bellSprite->setScale(BELLSCALE[0]);
	this->addChild(bellSprite);
	this->bellSprite->setVisible(false);

	//创建抢地主Button
	this->gradButton = ui::Button::create("grad_landlord_n.png", "grad_landlord_h.png");
	this->gradButton->setPosition(GRADPOS);
	this->addChild(this->gradButton);
	this->gradButton->addTouchEventListener([&](Ref* node, ui::Widget::TouchEventType tType) {
		if (Widget::TouchEventType::ENDED == tType) {
			this->gradButtonCallback(true);
		}
	});
	//不叫Button
	this->notGradButton = ui::Button::create("not_grad_landlord_n.png", "not_grad_landlord_h.png");
	this->notGradButton->setPosition(NOTGRADPOS);
	this->addChild(this->notGradButton);
	this->notGradButton->addTouchEventListener([&](Ref* node, ui::Widget::TouchEventType tType) {
		if (Widget::TouchEventType::ENDED == tType) {
			this->gradButtonCallback(false);
		}
	});
	//出牌
	this->outButton = ui::Button::create("out_n.png", "out_h.png");
	this->outButton->setPosition(GRADPOS);
	this->addChild(this->outButton);
	this->outButton->addTouchEventListener([&](Ref* node, ui::Widget::TouchEventType tType) {
		if (Widget::TouchEventType::ENDED == tType) {
			this->outButtonCallback(true);
		}
	});
	//不出
	this->notOutButton = ui::Button::create("not_out_n.png", "not_out_h.png");
	this->notOutButton->setPosition(NOTGRADPOS);
	this->addChild(this->notOutButton);
	this->notOutButton->addTouchEventListener([&](Ref* node, ui::Widget::TouchEventType tType) {
		if (Widget::TouchEventType::ENDED == tType) {
			this->outButtonCallback(false);
		}
	});
	//默认隐藏
	this->setGradUIEnabled(false);
	this->setOutUIEnabled(false);
	//this->setCountDown(2, 10);

	//test
	//MessageUpdateStateRsp proto;
	//proto.set_playeridx(1);
	//proto.set_statetype(1);
	//proto.set_endtime(My_client->getServerTime() + 10.0);
	//for (int i = 0; i < 5; i++) {
	//	auto tmpPoker = proto.add_midpoker();
	//	tmpPoker->set_color(1);
	//	tmpPoker->set_number(10);
	//}
	//for (int i = 0; i < 3; i++) {
	//	auto tmpPoker = proto.add_landlordpoker();
	//	tmpPoker->set_color(1);
	//	tmpPoker->set_number(13);
	//}
	//this->refreshState(&proto);
	//end test
}

//显示抢地主UI
void UIPlayGame::setGradUIEnabled(bool state) {
	this->gradButton->setVisible(state);
	this->notGradButton->setVisible(state);
}
//显示出牌UI
void UIPlayGame::setOutUIEnabled(bool state, bool showNoOut) {
	this->outButton->setVisible(state);
	this->notOutButton->setVisible(state);

	if (true == state) {
		this->notOutButton->setEnabled(showNoOut);
		//更新按钮状态
		this->updateOutButtonState();
	}
}
//设置时钟倒计时(pos：0，自己，2.下家，3.下家）
void UIPlayGame::setCountDown(int pos, int counts, function<void()> callback) {
	static function<void()> _callback = callback;
	_callback = callback;
	static int lastTime = 0;
	lastTime = counts;
	//隐藏上一个时钟
	this->bellSprite->setVisible(false);
	//取消上一个倒计时
	this->unschedule("CountDown");
	if (lastTime <= 0) {
		if (NULL != _callback) {
			_callback();
		}
		return;
	}
	//时钟位置
	this->bellSprite->setPosition(BELLPOS[pos]);
	//时钟比例
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


//叫地主按钮，不叫按钮回调函数(state 是否叫地主）
void UIPlayGame::gradButtonCallback(bool state) {
	this->setGradUIEnabled(false);
	this->setOutUIEnabled(false);
	cout << "gradButtonCallback: state = " << state << endl;
	MessageGradLandlordReq proto;
	proto.set_isgrad(state);
	My_client->request(&proto, [](google::protobuf::Message* rProto) {

	});
}
//出牌按钮，不出按钮回调函数(state 是否出牌）
void UIPlayGame::outButtonCallback(bool state) {
	this->setGradUIEnabled(false);
	this->setOutUIEnabled(false);
	cout << "outButtonCallback: state = " << state << endl;
	MessageOutPokerReq proto;
	if (true == state) {
		for (int i = 0; i < this->selPoker.size(); i++) {
			auto tmpPoker = this->selPoker[i];
			auto addPoker= proto.add_poker();
			addPoker->set_color(tmpPoker->getPoker().color());
			addPoker->set_number(tmpPoker->getPoker().number());
		}
	}
	My_client->request(&proto, [&](google::protobuf::Message* rProto) {
		this->selPoker.clear();
	});
}

//设置玩家牌的数量(上家和下家）
void UIPlayGame::setPlayerPokerNumber(int up, int down) {
	auto tmpUpSp = this->getChildByTag(UPPLAYERPOKERTAG);
	if (NULL != tmpUpSp) {
		tmpUpSp->setVisible(true);
		tmpUpSp->removeChildByTag(UPPLAYERPOKERNUMTAG);
		auto tmpUpNumSp = My_getSpriteNumber("number/number_blue.png", up);
		Size tmpSize = tmpUpSp->getContentSize();
		tmpUpNumSp->setPosition(Vec2(tmpSize.width * 0.5, tmpSize.height * 0.5));
		tmpUpNumSp->setScale(3.0);
		tmpUpSp->addChild(tmpUpNumSp, 1, UPPLAYERPOKERNUMTAG);
	}
	auto tmpDownSp = this->getChildByTag(DOWNPLAYERPOKERTAG);
	if (NULL != tmpDownSp) {
		tmpDownSp->setVisible(true);
		tmpDownSp->removeChildByTag(DOWNPLAYERPOKERNUMTAG);
		auto tmpDownNumSp = My_getSpriteNumber("number/number_blue.png", down);
		Size tmpSize = tmpDownSp->getContentSize();
		tmpDownNumSp->setPosition(Vec2(tmpSize.width * 0.5, tmpSize.height * 0.5));
		tmpDownNumSp->setScale(3.0);
		tmpDownSp->addChild(tmpDownNumSp, 1, DOWNPLAYERPOKERNUMTAG);
	}
}


//更新出牌按钮的状态
void UIPlayGame::updateOutButtonState() {
	int selSize = this->selPoker.size();
	int deskSize = this->deskPoker.size();
	if (0 == selSize) {
		this->outButton->setEnabled(false);
		return;
	}
	vector<MessageDataPoker > vecSel;
	vector<MessageDataPoker > vecDesk;
	int len = selSize < deskSize ? deskSize : selSize;
	for (int i = 0; i < len; i++) {
		if (i < selSize) {
			vecSel.push_back(this->selPoker[i]->getPoker());
		}
		if (i < deskSize) {
			vecDesk.push_back(this->deskPoker[i]->getPoker());
		}
	}
	this->outButton->setEnabled(My_pokerCmp(vecSel, vecDesk));
}

//播放叫地主音效
void UIPlayGame::playGradEffect(bool isGrad) {
	std::string fileName;
	if (true == isGrad) {
		fileName = "sound/effect/Man_Order";
	} else {
		fileName = "sound/effect/Man_NoOrder";
	}
	My_audioManage->playEffect(fileName.c_str());
}
//播放出牌音效
void UIPlayGame::playOutEffect(vector<MessageDataPoker> &pokerList) {
	if (0 == pokerList.size()) {
		//没出
		My_audioManage->playEffect("sound/effect/Man_buyao1");
		return;
	}
	std::string str = My_pokerListToString(pokerList);
	checkResult result = checkPoker::checkType(str);
	if (result.pType == pokerType::illegal) {
		return;
	}
	std::string fileName = "sound/effect/" ;
	if (result.pType == pokerType::rocket) {
		//王炸
		fileName += "Man_wangzha";
	} else if (result.pType == pokerType::bomb) {
		//炸弹
		fileName += "Man_zhadan";

	} else if (result.pType == pokerType::single) {
		if ('h' == result.maxChar) {
			//小王
			fileName += "Man_6_16";
		}else if('i' == result.maxChar){
			//大王
			fileName += "Man_5_16";
		} else if (1 < pokerList.size()) {
			//顺子
			fileName += "Man_shunzi";
		} else {
			//单牌
			char tmpStr[15];
			sprintf(tmpStr, "Man_%d", pokerList[0].number());
			fileName += tmpStr;
		}
	} else if (result.pType == pokerType::couple) {
		if (2 < pokerList.size()) {
			//连对
			fileName += "Man_liandui";
		} else {
			//一对
			char tmpStr[15];
			sprintf(tmpStr, "Man_dui%d", My_charToPokerValue(result.maxChar));
			fileName += tmpStr;
		}
	} else if (result.pType == pokerType::three) {
		if (6 < pokerList.size()) {
			//飞机
			fileName += "Man_feiji";
		} else {
			//三个
			char tmpStr[15];
			sprintf(tmpStr, "Man_tuple%d", My_charToPokerValue(result.maxChar));
			fileName += tmpStr;
		}
	} else{
		//四个
	}
	My_audioManage->playEffect(fileName.c_str());
}

void UIPlayGame::showing() {
	//随机一个背景音乐
	char tmpFileName[35];
	srand(time(NULL));
	int tmpMusicID = rand() % 2 + 1;
	sprintf(tmpFileName, "sound/music/MusicEx_Normal%d", tmpMusicID);
	My_audioManage->playMusic(tmpFileName, true);
}
void UIPlayGame::hideing() {
	//停止音乐音效
	My_audioManage->stopMusic();
	My_audioManage->stopAllEffects();
}]

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
	//隐藏UI
	this->setGradUIEnabled(false);
	this->setOutUIEnabled(false);
	this->setCountDown(0, 0);

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
		}), NULL));
		pokerNum = pokerNum - 1;
		//上家，下家牌的数字
		this->setPlayerPokerNumber(pokerSum - pokerNum, pokerSum - pokerNum);

		if (0 < pokerNum) {
			return;
		}
		//动画执行完，开始游戏
		cout << "startGame: " << pokerNum << endl;
		this->startGame();
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


//刷新自己手中的牌
void UIPlayGame::refreshSelfPoker(vector<MessageDataPoker> &pokerList, bool state) {
	if (0 == pokerList.size()) {
		return;
	}
	//移除现有的牌
	this->poker.clear();
	this->pokerNode->removeAllChildren();

	//排序
	sort(pokerList.begin(), pokerList.end(), My_pokerCmd);
	auto pokerSum = pokerList.size();
	for (int i = 0; i < pokerSum; i++) {
		//创建卡牌
		auto tmpPokerSp = UIPoker::create(&(pokerList[i]));
		tmpPokerSp->setPosition(Vec2((i + 0.5 - 0.5 * pokerSum) * SELFPOKERDIS, SELFPOKERY));
		tmpPokerSp->setVisible(state);
		this->pokerNode->addChild(tmpPokerSp, i, SELFPOKERTAG);

		//保存
		this->poker.push_back(tmpPokerSp);
	}
}

//刷新游戏状态
void UIPlayGame::refreshState(MessageUpdateStateRsp *proto) {
	this->gameing = true;
	this->setGradUIEnabled(false);
	this->setOutUIEnabled(false);
	this->notOutSprite->setVisible(false);
	this->notGradSprite->setVisible(false);
	this->gradSprite->setVisible(false);
	this->landlordSprite->setVisible(false);

	//显示玩家手牌
	this->setPlayerPokerNumber(proto->uppokernum(), proto->downpokernum());

	//显示倒计时
	auto lastTIme = (proto->lavetime());
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
		//显示地主牌
		vector<MessageDataPoker> tmpLandlordPokerList;
		for (int i = 0; i < proto->landlordpoker_size(); i++) {
			tmpLandlordPokerList.push_back(proto->landlordpoker(i));
		}
		//排序
		sort(tmpLandlordPokerList.begin(), tmpLandlordPokerList.end(), My_pokerCmd);
		this->landlordPokerNode->removeAllChildren();
		auto pokerSum = tmpLandlordPokerList.size();
		for (int i = 0; i < pokerSum; i++) {
			auto tmpPoker = UIPoker::create(&(tmpLandlordPokerList[i]));
			tmpPoker->setPosition(Vec2((i + 0.5 - 0.5 * pokerSum) * LANDLORDPOKERDIS, 0));
			this->landlordPokerNode->addChild(tmpPoker, i);
		}

	}
	


	if (1 == proto->statetype()) {
		//抢地主
		this->setGradUIEnabled(0 == proto->playeridx());
		//显示上一个操作者的操作
		//位置(当前操作者的上家）
		auto tmpIdx = (proto->playeridx() + 3 - 1) % 3;
		if (0 == proto->lastisgrad()) {
			//没有上一个操作者
		} else if (1 == proto->lastisgrad()) {
			//上一个操作者抢地主了
			this->gradSprite->setVisible(true);
			this->gradSprite->setPosition(BELLPOS[tmpIdx]);
		} else if (2 == proto->lastisgrad()) {
			//上一个操作者没抢
			this->notGradSprite->setVisible(true);
			this->notGradSprite->setPosition(BELLPOS[tmpIdx]);
		}
		//播放音效
		if (1 == proto->lastisgrad() || 2 == proto->lastisgrad()) {
			this->playGradEffect(1 == proto->lastisgrad());
		}

	} else if (2 == proto->statetype()) {
		//出牌
		if (0 == proto->lastoutplayeridx() || 0 < proto->midpoker_size()) {
			//上一个手牌是自己出的或者有新的牌， 清空缓存的牌桌上的牌， 不需要比较大小就能出牌
			this->deskPoker.clear();
		}
		//显示牌桌的牌
		vector<MessageDataPoker> tmpDeskPokerList;
		if (0 < proto->midpoker_size()) {
			for (int i = 0; i < proto->midpoker_size(); i++) {
				tmpDeskPokerList.push_back(proto->midpoker(i));
			}
			//排序
			sort(tmpDeskPokerList.begin(), tmpDeskPokerList.end(), My_pokerCmd);
			this->deskPokerNode->removeAllChildren();
			auto pokerSum = tmpDeskPokerList.size();
			for (int i = 0; i < pokerSum; i++) {
				auto tmpPoker = UIPoker::create(&(tmpDeskPokerList[i]));
				tmpPoker->setPosition(Vec2((i + 0.5 - 0.5 * pokerSum) * DESKPOKERDIS, 0));
				this->deskPokerNode->addChild(tmpPoker, i);
				this->deskPoker.push_back(tmpPoker);
			}
		}
		//播放音效
		if (1 == proto->lastisout() || 2 == proto->lastisout()) {
			this->playOutEffect(tmpDeskPokerList);
		}

		//操作人人是自己就显示, 上一个出牌人不是自己‘不要’按钮可点击
		this->setOutUIEnabled(0 == proto->playeridx(), (1 == proto->lastoutplayeridx() || 2 == proto->lastoutplayeridx()));
		//位置(当前操作者的上家）
		auto tmpIdx = (proto->playeridx() + 3 - 1) % 3;
		if (0 == proto->lastisout()) {
			//没有上一个操作者
		} else if (1 == proto->lastisout()) {
			//上一个操作者出牌

		} else if(2 == proto->lastisout()){
			//上一个操作者没有出牌
			this->notOutSprite->setVisible(true);
			this->notOutSprite->setPosition(BELLPOS[tmpIdx]);
		}
		//地主冒的位置
		this->landlordSprite->setVisible(true);
		this->landlordSprite->setScale(LANDLORDSPRITESCALE[proto->landlordidx()]);
		this->landlordSprite->setPosition(LANDLORDSPRITEPOS[proto->landlordidx()]);
	}

	//刷新自己的手牌
	int pokerSize = proto->selfpoker_size();
	vector<MessageDataPoker>tmpPokerList;
	for (int i = 0; i < pokerSize; i++) {
		MessageDataPoker tmpPoker = proto->selfpoker(i);
		tmpPokerList.push_back(tmpPoker);
	}
	this->refreshSelfPoker(tmpPokerList);
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
		this->touching = false;
		return true;
	}
	//保存卡牌状态
	for (int i = 0; i < this->poker.size(); i++) {
		this->lastPokerState[i] = this->poker[i]->isSelectEnabled();
	}
	this->setStateInInterval(this->beganIdx, this->beganIdx);
	this->touching = true;
	return true;
}
void UIPlayGame::touchMoved(Touch *touch, Event* event) {
	if (false == gameing || false == touching) {
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
	if (false == gameing || false == touching) {
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
	//更新按钮状态
	this->updateOutButtonState();
	this->touching = false;
}


//游戏结束
void UIPlayGame::gameOver(MessageGameResultRsp* rProto) {
	this->gameing = false;
	//隐藏所有UI
	this->setGradUIEnabled(false);
	this->setOutUIEnabled(false);
	this->notOutSprite->setVisible(false);
	this->notGradSprite->setVisible(false);
	this->gradSprite->setVisible(false);
	this->landlordSprite->setVisible(false);
	//音乐文件名
	std::string fileName;
	Sprite* resultSp = NULL;
	if (true == rProto->iswinning()) {
		fileName = "sound/music/MusicEx_Win";
		resultSp = Sprite::create("winning.png");
	} else {
		fileName = "sound/music/MusicEx_Lose";
		resultSp = Sprite::create("failure.png");
	}
	resultSp->setPosition(My_visibleSize.width * 0.5, My_visibleSize.height * 0.5);
	this->addChild(resultSp, 100);

	//播放音乐
	My_audioManage->playMusic(fileName.c_str());

	this->scheduleOnce([](float t) {
		//退出界面
		My_gameScene->popPanel();
	}, 3.5, "gameOver");

}
void UIPlayGame::onExit() {
	UIPanel::onExit();
	if (NULL != this->recvPokerlistener) {
		this->recvPokerlistener->removeEventListener();
		this->recvPokerlistener = NULL;
	}
	if (NULL != this->recvStateListener) {
		this->recvStateListener->removeEventListener();
		this->recvStateListener = NULL;

	}
	if (NULL != this->recvResultListener) {
		this->recvResultListener->removeEventListener();
		this->recvResultListener = NULL;

	}
}

UIPlayGame::~UIPlayGame() {
	//if(NULL != this->recvPokerlistener){
	//	this->recvPokerlistener->removeEventListener();
	//}
}
