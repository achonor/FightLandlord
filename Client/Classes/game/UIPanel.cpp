#include "UIPanel.h"

#include <iostream>

UIPanel::UIPanel(){
}


UIPanel::~UIPanel() {
}

bool UIPanel::init() {
	//灰色背景
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 120))){
		return false;
	}
	//创建监听器
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(UIPanel::touchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(UIPanel::touchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(UIPanel::touchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(UIPanel::touchCancelled, this);
	//监听器状态设置为吞并触摸消息
	listener->setSwallowTouches(true);
	//将监听器与当前节点建立关系并注册到事件分配器
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
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