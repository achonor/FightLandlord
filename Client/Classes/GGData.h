#ifndef GGDATA_H
#define GGDATA_H
#pragma once
#include "stdafx.h"
#include "functions.h"
#include "net/Client.h"

//初始化GGData
void My_InitGGData();
//清理游戏数据
void My_ClearGGData();

//公共Node，游戏结束才会释放
extern Node *GGNode;

//游戏配置文件
extern rapidjson::Document My_config;

//客户端网络
extern Client* My_Client;


//接收到数据事件
extern string EVENT_RECEIVE_DATA;

#endif