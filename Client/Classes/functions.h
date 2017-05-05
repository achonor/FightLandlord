#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#pragma once

#include "cocos2d.h"
#include <iostream>
#include <fstream>

#include "json/rapidjson.h"
#include "json/document.h"

#include "google/protobuf/message.h"

//����json�ļ�
rapidjson::Document My_getJsonData(const char* fileName);

//�ĸ��ֽ�charתint
int My_char4ToInt(const char *data);

//intת���ĸ�char�ֽ�
void My_intToChar4(char* chr, int num);

//char*תstring
std::string My_charToString(const char* sChr, int sLen);

//ͨ��protobufЭ��������Э�����
google::protobuf::Message* My_CreateMessage(const std::string& messageName);

//���л�Э�飬��������ǰ��������ݵĳ���
std::string My_Serialization(google::protobuf::Message* proto);

#endif