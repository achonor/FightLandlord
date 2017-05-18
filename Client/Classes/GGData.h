#ifndef GGDATA_H
#define GGDATA_H
#pragma once
#include "stdafx.h"
#include "functions.h"
#include "net/Client.h"
#include "audioManage.h"

//初始化GGData
void My_InitGGData();

//清理游戏数据
void My_ClearGGData();

//屏幕尺寸
extern Size My_visibleSize;

//玩家ID
extern int My_playerID;

//公共Node，游戏结束才会释放
extern Node *GGNode;

//游戏配置文件
extern rapidjson::Document My_config;

//客户端网络
extern Client* My_client;

//游戏场景(实际是Layer)
extern GameLayer* My_gameScene;

//接收到数据事件
extern string EVENT_RECEIVE_DATA;

//音频控制器
extern audioManage* My_audioManage;

#endif