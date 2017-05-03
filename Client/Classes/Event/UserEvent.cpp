#include "stdafx.h"
#include "UserEvent.h"



UserEvent::UserEvent(const string &name, const std::function<void(EventCustom*)> callback)
{
	//ע���¼�
	this->listener = EventListenerCustom::create(name, callback);
	//��ӵ��¼��ַ���
	Director::getInstance()->getEventDispatcher()
		->addEventListenerWithFixedPriority(this->listener, 1);
}

UserEvent::~UserEvent()
{	//�Ƴ��¼�
	this->removeEventListener();
}

UserEvent* UserEvent::addEventListener(const string &name, const std::function<void(EventCustom*)> callback) {
	UserEvent* listener = new UserEvent(name, callback);
	return listener;
}

void UserEvent::removeEventListener() {
	Director::getInstance()->getEventDispatcher()->
		removeEventListener(this->listener);
	delete this;
}

void UserEvent::dispatchEvent(const string &name, void *data) {
	EventCustom event(name);
	//��������
	event.setUserData(data);
	//�����¼�
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}