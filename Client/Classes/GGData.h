#ifndef GGDATA_H
#define GGDATA_H
#pragma once
#include "stdafx.h"
#include "functions.h"
#include "net/Client.h"

//��ʼ��GGData
void My_InitGGData();
//������Ϸ����
void My_ClearGGData();

//����Node����Ϸ�����Ż��ͷ�
extern Node *GGNode;

//��Ϸ�����ļ�
extern rapidjson::Document My_config;

//�ͻ�������
extern Client* My_Client;


//���յ������¼�
extern string EVENT_RECEIVE_DATA;

#endif