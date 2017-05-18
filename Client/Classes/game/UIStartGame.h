#ifndef UISTARTGAME_H
#define UISTARTGAME_H
#pragma once

#include "cocos2d.h"
#include "UIPanel.h"

USING_NS_CC;

class UIStartGame:public UIPanel{

private:
	virtual bool init();

	//开始游戏
	void startGame();

	virtual void onEnter();

	virtual void showing();
	virtual void hideing();

public:
	CREATE_FUNC(UIStartGame);
};

#endif