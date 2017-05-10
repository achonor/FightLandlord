#pragma once
#ifndef UIPOKER_H
#define UIPOKER_H

#include "cocos2d.h"
#include "proto/cmd.pb.h"

USING_NS_CC;

class UIPoker :
	public Sprite {
public:
	UIPoker();
	virtual ~UIPoker();
	virtual bool initWithPoker(MessageDataPoker* poker);
	//显示隐藏选中效果
	void setSelectEnabled(bool state);
	//获取状态
	bool isSelectEnabled();

	static UIPoker* create(MessageDataPoker* poker = NULL);

	//获取牌的值
	MessageDataPoker getPoker();

protected:
	//牌的值
	MessageDataPoker poker;
	//选中效果图
	Sprite* selectSp;
};

#endif