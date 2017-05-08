#pragma once

#include "cocos2d.h"
#include "UIPanel.h"

USING_NS_CC;

class UIPlayGame: public UIPanel{
public:
	UIPlayGame();
	virtual ~UIPlayGame();
	CREATE_FUNC(UIPlayGame);
protected:
	virtual bool init();
	void onEnter();

public:
	//请求开始游戏
	void requestStartGame();
	//请求获取牌
	void requestGetPoker();
};

