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
	//�¼�����
	string eventName;
	//�¼����
	EventListenerCustom *listener;
	//�ص�����
	std::function <void(EventCustom*)> callback;
public:
	virtual ~UserEvent();
	//ע���¼�
	static UserEvent* addEventListener(const string& eventName, const std::function<void(EventCustom*)> callback);
	//�¼�ע��
	void removeEventListener();
	//�¼�����
	static void dispatchEvent(const string &eventName, void *data);
	
};

#endif