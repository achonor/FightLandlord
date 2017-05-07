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


	return true;
}



UIPlayGame::~UIPlayGame() {
}
