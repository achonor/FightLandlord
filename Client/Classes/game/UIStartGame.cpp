#include "stdafx.h"
#include "GGData.h"
#include "UIStartGame.h"
#include "ui/UIButton.h"
#include "UIPlayGame.h"
#include "controls/UIMessageBox.h"
#include "UIPoker.h"
#include "audioManage.h"

#include "GGText.h"

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
		if (tType == Widget::TouchEventType::ENDED) {
			this->startGame();
		}
	});

	return true;
}

void UIStartGame::showing() {
	//播放背景音乐
	My_audioManage->playMusic("sound/music/MusicEx_Welcome", true);
}
void UIStartGame::hideing() {
	//停止音乐
	My_audioManage->stopMusic();
}

void UIStartGame::onEnter() {
	UIPanel::onEnter();
	//this->startGame();
}

void UIStartGame::startGame() {
	cout << "startGame...." << endl;
	UIPlayGame* uiPlayGame = NULL;
	//if (NULL != uiPlayGame) {
	//	uiPlayGame->removeFromParent();
	//	uiPlayGame = NULL;
	//}

	uiPlayGame = UIPlayGame::create();
	My_gameScene->pushPanel(uiPlayGame);
}