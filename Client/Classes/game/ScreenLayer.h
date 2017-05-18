#ifndef SCREENLAYER_H
#define SCREENLAYER_H
#pragma once

#include "cocos2d.h"
#include "UIPanel.h"

USING_NS_CC;

class ScreenLayer:public CCLayerColor {
public:
	ScreenLayer();
	~ScreenLayer();
	CREATE_FUNC(ScreenLayer);

	virtual void setVisible(bool state);

protected:
	//´¥ÃþÊÂ¼þ
	EventListenerTouchOneByOne* touchListener;
	virtual bool init();
};

#endif