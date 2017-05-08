#include "stdafx.h"
#include "GGData.h"
#include "GameScene.h"
#include "game/UIStartGame.h"
#include "controls/UIMessageBox.h"
#include <iostream>

USING_NS_CC;
using namespace std;

const int PANELNODE = 1;
const int SCREENLAYER = 2;
const int TOPNODE = 3;

GameLayer::GameLayer(): 
	screenLayer(NULL),
	panelNode(NULL),
	topNode(NULL)
{

}

GameLayer::~GameLayer() {

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


	//初始化数据
	this->curPanelNumber = 0;
	memset(panelList, 0, sizeof(this->panelList));
	//最上层的Node
	topNode = Node::create();
	topNode->setPosition(Vec2(0, 0));
	this->addChild(topNode, TOPNODE);
	//创建panelNode
	panelNode = Node::create();
	panelNode->setPosition(Vec2(0, 0));
	this->addChild(panelNode, PANELNODE);

	//创建菊花层
	screenLayer = ScreenLayer::create();
	this->addChild(screenLayer, SCREENLAYER);

	//注册回退按钮事件
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [](EventKeyboard::KeyCode code, Event* event) {
		if(code == EventKeyboard::KeyCode::KEY_BACK){
			static My_MessageBox* tmpMessageBox = NULL;
			if (tmpMessageBox) {
				return;
			}
			tmpMessageBox = My_MessageBox::create(GGText_tuichuyouxi, [](My_MessageBox::CLICKTYPE cType) {
				if (cType == My_MessageBox::CLICKTYPE::YES) {
					Director::getInstance()->end();
				}
				tmpMessageBox = NULL;
			});
			My_gameScene->pushPanel(tmpMessageBox, true);
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	//请求登陆
	this->requestLogin();
    return true;
}


void GameLayer::onEnter() {
	Layer::onEnter();

	//加载开始游戏界面
	auto uiStartGame = UIStartGame::create();
	this->pushPanel(uiStartGame);
}

//显示或隐藏菊花
void GameLayer::setSrceenVisible(bool state) {
	this->screenLayer->setVisible(state);
}


void GameLayer::pushPanel(Node *panel, bool isTop) {
	if (MAX_PANEL_NUM <= this->curPanelNumber) {
		throw std::exception("ERROR: panel is full");
		return;
	}
	if (this->curPanelNumber > 0) {
		//隐藏当前界面
		//this->panelList[this->curPanelNumber - 1]->setVisible(false);
	}
	this->panelList[this->curPanelNumber++] = panel;
	if (false == isTop) {
		this->panelNode->addChild(panel, this->curPanelNumber);
	} else {
		this->topNode->addChild(panel);
	}
}

void GameLayer::popPanel() {
	if (this->curPanelNumber <= 0) {
		throw std::exception("ERROR: don't have panel");
		return;
	}
	this->panelList[--this->curPanelNumber]->removeFromParent();
	if (this->curPanelNumber > 0) {
		//显示上一个界面
		this->panelList[this->curPanelNumber - 1]->setVisible(true);
	}
}

//请求登陆
bool GameLayer::requestLogin() {
	static int counts = 1;
	/*//test
	auto testRequest = [](float t) {
		cout << counts++ << endl;
		MessagePeopleReq proto;
		proto.set_peopleid(100);
		proto.set_ischina(true);
		My_client->request(&proto, [](google::protobuf::Message* rProto) {
		});
	};

	
	auto listener = UserEvent::addEventListener("MessagePeopleRsp", [&](EventCustom *event) {
		this->scheduleOnce([=](float t) {
			testRequest();
		}, 0.1, "testRequest");
	});
	//end test
	*/

	MessageLoginReq proto;
	My_client->request(&proto, [=](google::protobuf::Message *rProto) {
		//登陆成功
		auto sProto = (MessageLoginRsp*)rProto;
		cout << "login success: " << sProto->playerid() << endl;
		//保存玩家ID
		My_playerID = sProto->playerid();
	});
	return true;
}

