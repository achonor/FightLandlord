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
	//����ʼ��Ϸ
	void requestStartGame();
	//�����ȡ��
	void requestGetPoker();
};

