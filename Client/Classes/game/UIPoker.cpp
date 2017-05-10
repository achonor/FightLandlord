#include "UIPoker.h"
#include <iostream>

UIPoker::UIPoker() {
	selectSp = NULL;
	this->poker.set_color(0);
	this->poker.set_number(0);
}


UIPoker::~UIPoker() {

}


UIPoker* UIPoker::create(MessageDataPoker* poker)
{ 
	UIPoker *pRet = new(std::nothrow) UIPoker();
	if (pRet && pRet->initWithPoker(poker)) {
		pRet->autorelease();
		return pRet;
	} else {
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool UIPoker::initWithPoker(MessageDataPoker* poker) {
	std::string path = "poker_card/pokerpoker_back_1.png";
	if (NULL != poker) {
		path = "poker_card/poker_" + std::to_string(poker->color()) + "_" + std::to_string(poker->number()) + ".png";
	}
	if (!Sprite::initWithFile(path)) {
		return false;
	}

	//����ѡ��Ч��
	this->selectSp = Sprite::create("poker_card/poker_select.png");
	Size tmpSize = this->selectSp->getContentSize();
	this->selectSp->setPosition(Vec2(tmpSize.width * 0.5, tmpSize.height * 0.5));
	this->addChild(this->selectSp);
	this->setSelectEnabled(false); //Ĭ������

	return true;
}

void UIPoker::setSelectEnabled(bool state) {
	if (NULL == this->selectSp) {
		return;
	}
	this->selectSp->setVisible(state);
}


bool UIPoker::isSelectEnabled() {
	if (NULL == this->selectSp) {
		return false;
	}
	return this->selectSp->isVisible();
}

//��ȡ�Ƶ�ֵ
MessageDataPoker UIPoker::getPoker() {
	return this->poker;
}