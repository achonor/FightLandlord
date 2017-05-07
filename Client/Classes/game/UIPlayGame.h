#pragma once

#include "cocos2d.h"
#include "UIPanel.h"

USING_NS_CC;

class UIPlayGame: public UIPanel{
public:
	UIPlayGame();
	virtual ~UIPlayGame();
	CREATE_FUNC(UIPlayGame);
private:
	virtual bool init();
	void onEnter();
};

