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
	//灰色背景
	if (!CCLayerColor::initWithColor(ccc4(0, 0, 0, 100))) {
		return false;
	}

	//添加向下触摸屏蔽
	auto callback = [](Touch *, Event *) {
		return true;
	};
	//创建监听器
	this->touchListener = EventListenerTouchOneByOne::create();
	this->touchListener->onTouchBegan = callback;
	//将监听器与当前节点建立关系并注册到事件分配器
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(this->touchListener, this);
	this->setVisible(false);


	//菊花圈
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
	//是否吞没触摸消息
	this->touchListener->setSwallowTouches(state);
}