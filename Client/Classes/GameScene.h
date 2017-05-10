#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "proto/cmd.pb.h"
#include "Event/UserEvent.h"
#include "game/ScreenLayer.h"

const int MAX_PANEL_NUM = 20;


class GameLayer : public cocos2d::Layer
{
public:
	GameLayer();
	~GameLayer();

    virtual bool init();
    
	void onEnter();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameLayer);

	//设置当前显示的界面
	void pushPanel(Node* panel, bool isTop = false);
	//弹出当前显示的界面
	void popPanel();

	//显示或隐藏菊花
	void setSrceenVisible(bool state);

protected:
	bool requestLogin();

protected:
	//菊花层
	ScreenLayer* screenLayer;
	//放界面的Node
	Node* panelNode;
	//最上层的Node
	Node* topNode;
	int curPanelNumber;
	Node* panelList[MAX_PANEL_NUM];
};

#endif // __HELLOWORLD_SCENE_H__
