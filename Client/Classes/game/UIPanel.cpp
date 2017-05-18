#include "UIPanel.h"

#include <iostream>

UIPanel::UIPanel():
	touchListener(NULL)
{
}


UIPanel::~UIPanel() {
}

bool UIPanel::init() {
	//灰色背景
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 120))){
		return false;
	}
	this->addTouchListener();
	return true;
}

//添加监听事件
void UIPanel::addTouchListener() {

	this->removeTouchListener();
	//创建监听器
	this->touchListener = EventListenerTouchOneByOne::create();
	this->touchListener->onTouchBegan = CC_CALLBACK_2(UIPanel::touchBegan, this);
	this->touchListener->onTouchMoved = CC_CALLBACK_2(UIPanel::touchMoved, this);
	this->touchListener->onTouchEnded = CC_CALLBACK_2(UIPanel::touchEnded, this);
	this->touchListener->onTouchCancelled = CC_CALLBACK_2(UIPanel::touchCancelled, this);
	//监听器状态设置为吞并触摸消息
	this->touchListener->setSwallowTouches(true);
	//将监听器与当前节点建立关系并注册到事件分配器
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(this->touchListener, this);
}

//移除触摸事件
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

void UIPanel::showing() {
}
void UIPanel::hideing() {
}