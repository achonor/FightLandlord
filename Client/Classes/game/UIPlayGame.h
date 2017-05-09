#pragma once

#include <vector>
#include "cocos2d.h"
#include "UIPanel.h"
#include "UIPoker.h"

USING_NS_CC;

//最多有多少牌
const int MAXPOKERNUM = 20;


class UIPlayGame: public UIPanel{
public:
	UIPlayGame();
	virtual ~UIPlayGame();
	CREATE_FUNC(UIPlayGame);
protected:
	virtual bool init();
	void onEnter();

	//显示发牌动画
	void showDealAction();
	//是否选中卡牌
	void setPokerState(int idx, bool state);
	//重设所有卡牌
	void resetAllPoker();
	//反转一个区间的牌的状态
	void setStateInInterval(int startIdx, int endIdx);
	//判断触摸点在那个牌上, 没找到返回-1
	int checkTouchInPoker(Vec2 &pos);
	//开始游戏（发牌完成，可以选择牌）
	void startGame();
	//刷新状态
	void refreshState(MessageUpdateStateRsp* proto);

public:
	//请求开始游戏
	void requestStartGame();
	//请求获取牌
	void requestGetPoker();

public:
	virtual bool touchBegan(Touch *touch, Event* event);
	virtual void touchMoved(Touch *touch, Event* event);
	virtual void touchEnded(Touch *touch, Event* event);
protected:
	//触摸开始的牌的索引
	int beganIdx;
	//上一次触发touchMove的位置
	Vec2 lastMovePos;

protected:
	//上家牌的数量
	int upNum;
	//下家牌的数量
	int downNum;
	//自己的牌
	vector<UIPoker*> poker;
	//接收发牌协议事件
	UserEvent* recvPokerlistener;
	//接收游戏状态事件
	UserEvent* recvStateListener;
	//放自己牌的Node
	Node* pokerNode;
	//选中的牌
	vector<UIPoker*> selPoker;
	//触摸开始前卡牌的状态列表
	bool lastPokerState[MAXPOKERNUM + 1];
	//游戏是否开始
	bool gameing;
};

