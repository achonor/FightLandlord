#include "UIPanel.h"

#include <iostream>

UIPanel::UIPanel(){
}


UIPanel::~UIPanel() {
}

bool UIPanel::init() {
	//��ɫ����
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 120))){
		return false;
	}
	//����������
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(UIPanel::touchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(UIPanel::touchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(UIPanel::touchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(UIPanel::touchCancelled, this);
	//������״̬����Ϊ�̲�������Ϣ
	listener->setSwallowTouches(true);
	//���������뵱ǰ�ڵ㽨����ϵ��ע�ᵽ�¼�������
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