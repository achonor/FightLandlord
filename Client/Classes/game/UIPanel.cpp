#include "UIPanel.h"

#include <iostream>

UIPanel::UIPanel():
	touchListener(NULL)
{
}


UIPanel::~UIPanel() {
}

bool UIPanel::init() {
	//��ɫ����
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 120))){
		return false;
	}
	this->addTouchListener();
	return true;
}

//��Ӽ����¼�
void UIPanel::addTouchListener() {

	this->removeTouchListener();
	//����������
	this->touchListener = EventListenerTouchOneByOne::create();
	this->touchListener->onTouchBegan = CC_CALLBACK_2(UIPanel::touchBegan, this);
	this->touchListener->onTouchMoved = CC_CALLBACK_2(UIPanel::touchMoved, this);
	this->touchListener->onTouchEnded = CC_CALLBACK_2(UIPanel::touchEnded, this);
	this->touchListener->onTouchCancelled = CC_CALLBACK_2(UIPanel::touchCancelled, this);
	//������״̬����Ϊ�̲�������Ϣ
	this->touchListener->setSwallowTouches(true);
	//���������뵱ǰ�ڵ㽨����ϵ��ע�ᵽ�¼�������
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(this->touchListener, this);
}

//�Ƴ������¼�
void UIPanel::removeTouchListener() {
	if (NULL != this->touchListener) {
		Director::getInstance()->getEventDispatcher()->removeEventListener(this->touchListener);
		this->touchListener = NULL;
	}
}


void UIPanel::onExit() {
	CCLayerColor::onExit();
	this->removeTouchListener();
}


bool UIPanel::touchBegan(Touch *touch, Event* event) {
	return true;
}
void UIPanel::touchMoved(Touch *touch, Event* event) {

}
void UIPanel::touchEnded(Touch *touch, Event* event) {

}
void UIPanel::touchCancelled(Touch *touch, Event* event) {

}