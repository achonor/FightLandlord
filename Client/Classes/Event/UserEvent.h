#ifndef USEREVENT_H
#define USEREVENT_H
#pragma once

#include <iostream>
#include <functional>

#include "cocos2d.h"
#include "base\CCEventCustom.h"

USING_NS_CC;
using namespace std;

class UserEvent
{
protected:
	//�¼�����
	string eventName;
	//�¼����
	EventListenerCustom *listener;
	//�ص�����
	std::function <void(EventCustom*)> callback;
public:
	UserEvent(const string& eventName, const std::function<void(EventCustom*)> callback);
	virtual ~UserEvent();
	//�¼�ע��
	void removeEventListener();
	//�¼�����
	static void dispatchEvent(const string &eventName, void *data);
	
};

#endif