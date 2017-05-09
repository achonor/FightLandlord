#ifndef UIPANEL_H
#define UIPANEL_H
#pragma once
#include "cocos2d.h"
#include <iostream>

USING_NS_CC;

class UIPanel:public CCLayerColor{
public:
	UIPanel();
	virtual ~UIPanel();

protected:
	virtual bool init();
	CREATE_FUNC(UIPanel);

public:
	virtual bool touchBegan(Touch *touch, Event* event);
	virtual void touchMoved(Touch *touch, Event* event);
	virtual void touchEnded(Touch *touch, Event* event);
	virtual void touchCancelled(Touch *touch, Event* event);
};

#endif
