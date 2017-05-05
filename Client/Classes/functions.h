#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#pragma once

#include "cocos2d.h"
#include <iostream>
#include <fstream>

#include "json/rapidjson.h"
#include "json/document.h"

#include "google/protobuf/message.h"

//解析json文件
rapidjson::Document My_getJsonData(const char* fileName);

//四个字节char转int
int My_char4ToInt(const char *data);

//int转成四个char字节
void My_intToChar4(char* chr, int num);

//char*转string
std::string My_charToString(const char* sChr, int sLen);

//通过protobuf协议名创建协议对象
google::protobuf::Message* My_CreateMessage(const std::string& messageName);

//序列化协议，并在数据前面加上数据的长度
std::string My_Serialization(google::protobuf::Message* proto);

#endif