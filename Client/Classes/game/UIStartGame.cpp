#include "stdafx.h"
#include "GGData.h"
#include "UIStartGame.h"
#include "ui/UIButton.h"
#include "UIPlayGame.h"

USING_NS_CC;
using namespace ui;

bool UIStartGame::init() {
	if (!UIPanel::init()) {
		return false;
	}

	//读取背景
	auto backSprite = Sprite::create("start_back.png");
	backSprite->setPosition(Vec2(My_visibleSize.width * 0.5, My_visibleSize.height * 0.5));
	backSprite->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(backSprite);


	//开始游戏按钮
	auto startButton = ui::Button::create("start_button_n.png", "start_button_h.png");
	startButton->setPosition(Vec2(My_visibleSize.width * 0.5, 100));
	startButton->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(startButton);

	//开始游戏按钮事件
	startButton->addTouchEventListener([&](Ref* node, ui::Widget::TouchEventType tType) {
		switch (tType)
		{
		case Widget::TouchEventType::BEGAN:
			break;

		case Widget::TouchEventType::MOVED:
			break;

		case Widget::TouchEventType::ENDED:
			this->startGame();
			break;
		case Widget::TouchEventType::CANCELED:
			break;
		default:
			break;
		}
	});
	return true;
}

void UIStartGame::startGame() {
	cout << "开始游戏" << endl;
	auto uiPlayGame = UIPlayGame::create();
	My_gameScene->pushPanel(uiPlayGame);
}