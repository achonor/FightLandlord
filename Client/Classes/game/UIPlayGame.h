#pragma once

#include <vector>
#include "cocos2d.h"
#include "UIPanel.h"

USING_NS_CC;

class UIPlayGame: public UIPanel{
public:
	UIPlayGame();
	virtual ~UIPlayGame();
	CREATE_FUNC(UIPlayGame);
protected:
	virtual bool init();
	void onEnter();

	//��ʾ���ƶ���
	void showDealAction();

public:
	//����ʼ��Ϸ
	void requestStartGame();
	//�����ȡ��
	void requestGetPoker();

protected:
	//�ϼ��Ƶ�����
	int upNum;
	//�¼��Ƶ�����
	int downNum;
	//�Լ�����
	vector<MessageDataPoker>poker;
	//���ܷ���Э���¼�
	UserEvent* recvPokerlistener;
	//���Լ��Ƶ�Node
	Node* pokerNode;
};

