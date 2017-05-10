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
	//��ʾ����ѡ��Ч��
	void setSelectEnabled(bool state);
	//��ȡ״̬
	bool isSelectEnabled();

	static UIPoker* create(MessageDataPoker* poker = NULL);

	//��ȡ�Ƶ�ֵ
	MessageDataPoker getPoker();

protected:
	//�Ƶ�ֵ
	MessageDataPoker poker;
	//ѡ��Ч��ͼ
	Sprite* selectSp;
};

#endif