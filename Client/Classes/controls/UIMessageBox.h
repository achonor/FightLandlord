#ifndef UIMESSAGEBOX_H
#define UIMESSAGEBOX_H
#pragma once

#include "cocos2d.h"
#include "game/UIPanel.h"

USING_NS_CC;
using namespace ui;

class My_MessageBox :
	public UIPanel {
public:
	enum CLICKTYPE{
		YES = 1,
		CANCEL = 2,
		CLOSE = 3,
	};
public:
	My_MessageBox();
	virtual ~My_MessageBox();

	CREATE_FUNC(My_MessageBox);
	virtual bool init();
	static My_MessageBox* create(const std::string &text, function<void(CLICKTYPE cType)> call = NULL);
	//设置提示文字
	void setText(const std::string &text);
	
	void setCallback(function<void(CLICKTYPE cType)> call);

protected:
	//按钮回调函数
	void _callBacck(CLICKTYPE cType);

protected:
	//放文字的Label
	Label* textLabel;
	//回调函数
	function<void(CLICKTYPE cType)> callback;
};

#endif