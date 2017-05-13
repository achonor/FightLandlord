#ifndef CHECKPOKER_H
#define CHECKPOKER_H
#pragma once
#include <string>
#include <string.h>
#include <iostream>
#include <algorithm>

using namespace std;

//需要连续多少才合法
const int needNum[5] = { 16, 1, 1, 1, 1 };
//最多能带多少牌
const int mostTake[5] = { 0, 0, 0, 2, 2 };

//牌和代码中字符的对应
//3:3， 4:4，5:5，6:6，7:7，8:8，9:9，a:10，b:J， c:Q， d:K， e:A, f:2, g:王

enum pokerType {
	illegal = 0,//非法
	single = 1,      //单牌, 顺子
	couple = 2,     //对子, 连对
	three = 3,      //三带一，三带一对, 飞机
	four = 4,       //四带一，四带二
	bomb = 5,       //炸弹
	rocket = 6,     //火箭
};

//检测牌类型函数返回的结果
class checkResult {
public:
	char maxChar;   //用于比较大小的字符
	pokerType pType;//牌的类型
	checkResult(pokerType _pType = illegal, char _maxChar = '3') {
		this->maxChar = _maxChar;
		this->pType = _pType;
	}
};
class checkPoker {

public:
	checkPoker();
	virtual ~checkPoker();

	//从有序的字符串中查找数量为num的字符
	static void findCharByNumber(char *retStr, std::string &srcStr, int num);
	//检测字符串中的字符是否连续
	static bool checkCharIsConnect(const char *str);
	//检测牌的类型
	static checkResult checkType(std::string &pokerList);
	//判断牌的大小
	static bool pokerCmp(std::string &a, std::string &b);
};


#endif