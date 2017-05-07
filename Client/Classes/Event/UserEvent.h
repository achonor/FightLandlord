#ifndef USEREVENT_H
#define USEREVENT_H
#pragma once

#include <iostream>
#include <functional>

#include "cocos2d.h"
#include "base/CCEventCustom.h"

USING_NS_CC;
using namespace std;

class UserEvent
{
protected:
	UserEvent(const string& eventName, const std::function<void(EventCustom*)> callback);
	//事件名称
	string eventName;
	//事件句柄
	EventListenerCustom *listener;
	//回调函数
	std::function <void(EventCustom*)> callback;
public:
	virtual ~UserEvent();
	//注册事件
	static UserEvent* addEventListener(const string& eventName, const std::function<void(EventCustom*)> callback);
	//事件注销
	void removeEventListener();
	//事件触发
	static void dispatchEvent(const string &eventName, void *data);
	
};

#endif