#ifndef GGDATA_H
#define GGDATA_H
#pragma once
#include "stdafx.h"
#include "functions.h"
#include "game/MyScheduler.h"

//��ʼ��GGData
void My_InitGGData();
//������Ϸ����
void My_ClearGGData();

//����Node����Ϸ�����Ż��ͷ�
extern CCNode *GGNode;

//��Ϸ�����ļ�
extern rapidjson::Document My_config;

//�ͻ�������
//extern Client My_Client;

//ȫ�ֶ�ʱ��������
extern MyScheduler *My_Scheduler;

#endif