#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#pragma once

#include "cocos2d.h"
#include <iostream>
#include <fstream>

#include "json/rapidjson.h"
#include "json/document.h"

//����json�ļ�
rapidjson::Document My_getJsonData(const char* fileName);

//�ĸ��ֽ�charתint
int My_char4ToInt(const char *data);

#endif