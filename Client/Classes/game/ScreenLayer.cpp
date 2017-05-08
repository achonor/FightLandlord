#include "ScreenLayer.h"
#include "GGData.h"


const int LOOPSPTAG = 100;

ScreenLayer::ScreenLayer() :
	touchListener(NULL)
{
}


ScreenLayer::~ScreenLayer() {
}


bool ScreenLayer::init() {
	//��ɫ����
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 100))) {
		return false;
	}

	//������´�������
	auto callback = [](Touch *, Event *) {
		return true;
	};
	//����������
	this->touchListener = EventListenerTouchOneByOne::create();
	this->touchListener->onTouchBegan = callback;
	//���������뵱ǰ�ڵ㽨����ϵ��ע�ᵽ�¼�������
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(this->touchListener, this);
	this->setVisible(false);


	//�ջ�Ȧ
	auto loopSp = Sprite::create("loading.png");
	loopSp->setPosition(Vec2(My_visibleSize.width * 0.5, My_visibleSize.height * 0.5));
	this->addChild(loopSp, 1, LOOPSPTAG);

	this->schedule([&](float t) {
		auto tmpNode = this->getChildByTag(LOOPSPTAG);
		if (NULL == tmpNode) {
			return;
		}
		tmpNode->setRotation(tmpNode->getRotation() + 3.0);
	}, 0.01, "LOOPSP");
	return true;
}

void ScreenLayer::setVisible(bool state) {
	if (NULL == this->touchListener) {
		return;
	}
	this->CCLayerColor::setVisible(state);
	//�Ƿ���û������Ϣ
	this->touchListener->setSwallowTouches(state);
}