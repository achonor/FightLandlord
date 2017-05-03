#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#pragma once

#include "cocos2d.h"
#include <iostream>
#include <fstream>

#include "json/rapidjson.h"
#include "json/document.h"

//½âÎöjsonÎÄ¼þ
rapidjson::Document My_getJsonData(const char* fileName);

#endif