#pragma once

#include <vector>
#include "cocos2d.h"
#include "UIPanel.h"
#include "UIPoker.h"
#include "ui/UIButton.h"

USING_NS_CC;
using namespace ui;

//最多有多少牌
const int MAXPOKERNUM = 20;


class UIPlayGame: public UIPanel{
public:
	UIPlayGame();
	virtual ~UIPlayGame();
	CREATE_FUNC(UIPlayGame);
protected:
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

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
	//游戏结束
	void gameOver(MessageGameResultRsp* rProto);
	//刷新自己手里的牌
	void refreshSelfPoker(vector<MessageDataPoker> &pokerList, bool state = true);
	//刷新状态
	void refreshState(MessageUpdateStateRsp* proto);
	//创建UI
	void createUI();
	//显示抢地主UI
	void setGradUIEnabled(bool state);
	//显示出牌UI
	void setOutUIEnabled(bool state);
	//设置时钟倒计时(pos：0，自己，2.下家，3.下家）
	void setCountDown(int pos, int counts, function<void()> callback = NULL);
	//叫地主按钮，不叫按钮回调函数(state 是否叫地主）
	void gradButtonCallback(bool state);
	//出牌按钮，不出按钮回调函数(state 是否出牌）
	void outButtonCallback(bool state);
	//设置玩家牌的数量(上家和下家）
	void setPlayerPokerNumber(int up, int down);

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
	//接受游戏结束的时间
	UserEvent* recvResultListener;
	//放自己牌的Node
	Node* pokerNode;
	//选中的牌
	vector<UIPoker*> selPoker;
	//触摸开始前卡牌的状态列表
	bool lastPokerState[MAXPOKERNUM + 1];
	//游戏是否开始
	bool gameing;
	//是都在触摸中
	bool touching;

	//时钟Sprite
	Sprite* bellSprite;
	//叫地主Button
	ui::Button* gradButton;
	//不叫Button
	ui::Button* notGradButton;
	//出牌Button
	ui::Button* outButton;
	//不出Button
	ui::Button* notOutButton;
	//放地主牌的Node
	Node* landlordPokerNode;
	//牌桌上牌的Node
	Node* deskPokerNode;
	//不出Sprite
	Sprite* notOutSprite;
	//不抢Sprite
	Sprite* notGradSprite;
	//抢地主Sprite
	Sprite* gradSprite;
	
	//地主帽Sprite
	Sprite* landlordSprite;

};

