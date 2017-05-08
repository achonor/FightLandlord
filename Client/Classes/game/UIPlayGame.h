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

	//显示发牌动画
	void showDealAction();

public:
	//请求开始游戏
	void requestStartGame();
	//请求获取牌
	void requestGetPoker();

protected:
	//上家牌的数量
	int upNum;
	//下家牌的数量
	int downNum;
	//自己的牌
	vector<MessageDataPoker>poker;
	//接受发牌协议事件
	UserEvent* recvPokerlistener;
	//放自己牌的Node
	Node* pokerNode;
};

