#pragma once
#include "cocos2d.h"

USING_NS_CC;

class UIPanel:public CCLayerColor{
public:
	UIPanel();
	virtual ~UIPanel();

protected:
	virtual bool init();
	CREATE_FUNC(UIPanel);
};

