#pragma once

#include <vector>
#include "cocos2d.h"
#include "UIPanel.h"
#include "UIPoker.h"
#include "ui/UIButton.h"

USING_NS_CC;
using namespace ui;

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
	//ˢ���Լ��������
	void refreshSelfPoker(vector<MessageDataPoker> &pokerList, bool state = true);
	//ˢ��״̬
	void refreshState(MessageUpdateStateRsp* proto);
	//����UI
	void createUI();
	//��ʾ������UI
	void setGradUIEnabled(bool state);
	//��ʾ����UI
	void setOutUIEnabled(bool state);
	//����ʱ�ӵ���ʱ(pos��0���Լ���2.�¼ң�3.�¼ң�
	void setCountDown(int pos, int counts, function<void()> callback = NULL);
	//�е�����ť�����а�ť�ص�����(state �Ƿ�е�����
	void gradButtonCallback(bool state);
	//���ư�ť��������ť�ص�����(state �Ƿ���ƣ�
	void outButtonCallback(bool state);
	//��������Ƶ�����(�ϼҺ��¼ң�
	void setPlayerPokerNumber(int up, int down);

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
	//�Ƕ��ڴ�����
	bool touching;

	//ʱ��Sprite
	Sprite* bellSprite;
	//�е���Button
	ui::Button* gradButton;
	//����Button
	ui::Button* notGradButton;
	//����Button
	ui::Button* outButton;
	//����Button
	ui::Button* notOutButton;
	//�ŵ����Ƶ�Node
	Node* landlordPokerNode;
	//�������Ƶ�Node
	Node* deskPokerNode;
};

