#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "proto/cmd.pb.h"
#include "Event/UserEvent.h"

const int MAX_PANEL_NUM = 20;


class GameLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    
	void onEnter();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameLayer);


	//设置当前显示的界面
	void pushPanel(Node* panel);
	//弹出当前显示的界面
	void popPanel();
protected:
	bool requestLogin();

private:
	int curPanelNumber;
	Node* panelList[MAX_PANEL_NUM];
};

#endif // __HELLOWORLD_SCENE_H__
