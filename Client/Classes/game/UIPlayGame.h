#pragma once

#include <vector>
#include "cocos2d.h"
#include "UIPanel.h"
#include "UIPoker.h"

USING_NS_CC;

//����ж�����
const int MAXPOKERNUM = 20;


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
	//�Ƿ�ѡ�п���
	void setPokerState(int idx, bool state);
	//�������п���
	void resetAllPoker();
	//��תһ��������Ƶ�״̬
	void setStateInInterval(int startIdx, int endIdx);
	//�жϴ��������Ǹ�����, û�ҵ�����-1
	int checkTouchInPoker(Vec2 &pos);
	//��ʼ��Ϸ��������ɣ�����ѡ���ƣ�
	void startGame();
	//ˢ��״̬
	void refreshState(MessageUpdateStateRsp* proto);

public:
	//����ʼ��Ϸ
	void requestStartGame();
	//�����ȡ��
	void requestGetPoker();

public:
	virtual bool touchBegan(Touch *touch, Event* event);
	virtual void touchMoved(Touch *touch, Event* event);
	virtual void touchEnded(Touch *touch, Event* event);
protected:
	//������ʼ���Ƶ�����
	int beganIdx;
	//��һ�δ���touchMove��λ��
	Vec2 lastMovePos;

protected:
	//�ϼ��Ƶ�����
	int upNum;
	//�¼��Ƶ�����
	int downNum;
	//�Լ�����
	vector<UIPoker*> poker;
	//���շ���Э���¼�
	UserEvent* recvPokerlistener;
	//������Ϸ״̬�¼�
	UserEvent* recvStateListener;
	//���Լ��Ƶ�Node
	Node* pokerNode;
	//ѡ�е���
	vector<UIPoker*> selPoker;
	//������ʼǰ���Ƶ�״̬�б�
	bool lastPokerState[MAXPOKERNUM + 1];
	//��Ϸ�Ƿ�ʼ
	bool gameing;
};

