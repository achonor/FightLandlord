#include "UIPanel.h"



UIPanel::UIPanel(){
}


UIPanel::~UIPanel() {
}

bool UIPanel::init() {
	//灰色背景
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 120))){
		return false;
	}
	
	//添加向下触摸屏蔽
	auto callback = [](Touch *, Event *){
		return true;
	};
	//创建监听器
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = callback;
	//监听器状态设置为吞并触摸消息
	listener->setSwallowTouches(true);
	//将监听器与当前节点建立关系并注册到事件分配器
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}
