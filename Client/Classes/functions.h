#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#pragma once

#include "cocos2d.h"
#include <iostream>
#include <fstream>

#include "json/rapidjson.h"
#include "json/document.h"

//解析json文件
rapidjson::Document My_getJsonData(const char* fileName);

//四个字节char转int
int My_char4ToInt(const char *data);

#endif