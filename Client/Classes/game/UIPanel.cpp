#include "UIPanel.h"



UIPanel::UIPanel(){
}


UIPanel::~UIPanel() {
}

bool UIPanel::init() {
	//��ɫ����
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 120))){
		return false;
	}
	
	//������´�������
	auto callback = [](Touch *, Event *){
		return true;
	};
	//����������
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = callback;
	//������״̬����Ϊ�̲�������Ϣ
	listener->setSwallowTouches(true);
	//���������뵱ǰ�ڵ㽨����ϵ��ע�ᵽ�¼�������
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}
