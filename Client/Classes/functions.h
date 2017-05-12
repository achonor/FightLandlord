#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#pragma once

#include "cocos2d.h"
#include <iostream>
#include <fstream>
#include <vector>

#include "json/rapidjson.h"
#include "json/document.h"

#include "proto/cmd.pb.h"
#include "google/protobuf/message.h"

const char PokerToChar[18] = "0003456789abcdefg";

//解析json文件
rapidjson::Document My_getJsonData(const char* fileName);

//四个字节char转int
unsigned int My_char4ToInt(const char *data);

//int转成四个char字节
void My_intToChar4(char* chr, unsigned int num);

//char*转string
std::string My_charToString(const char* sChr, int sLen);

//通过protobuf协议名创建协议对象
google::protobuf::Message* My_CreateMessage(const std::string& messageName);

//序列化协议，并在数据前面加上数据的长度
std::string My_Serialization(google::protobuf::Message* proto);

//返回一个图片数字
cocos2d::Node* My_getSpriteNumber(std::string path, int number);

//计算两点间距离
double My_calcPostionDis(cocos2d::Vec2 &pos1, cocos2d::Vec2 &pos2);

//poker排序
bool My_pokerCmd(MessageDataPoker &a, MessageDataPoker &b);

//vector<MessageDataPoker >转成字符串
//3:3， 4:4，5:5，6:6，7:7，8:8，9:9，a:10，b:J， c:Q， d:K， e:A, f:2, g:王
std::string My_pokerListToString(vector<MessageDataPoker > &pokerList);

//判断牌的大小
bool My_pokerCmp(vector<MessageDataPoker > &a, vector<MessageDataPoker > &b);

#endif