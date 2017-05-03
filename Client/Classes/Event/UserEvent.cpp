#include "stdafx.h"
#include "UserEvent.h"



UserEvent::UserEvent(const string &name, const std::function<void(EventCustom*)> callback)
{
	//注册事件
	this->listener = EventListenerCustom::create(name, callback);
	//添加到事件分发器
	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithFixedPriority(this->listener, 1);
}

UserEvent::~UserEvent()
{	//移除事件
	this->removeEventListener();
}

void UserEvent::removeEventListener() {
	Director::getInstance()->getEventDispatcher()->
		removeEventListener(this->listener);
}

void UserEvent::dispatchEvent(const string &name, void *data) {
	EventCustom event(name);
	//设置数据
	event.setUserData(data);
	//触发事件
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}