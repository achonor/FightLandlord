#ifndef CHECKPOKER_H
#define CHECKPOKER_H
#pragma once
#include <string>
#include <string.h>
#include <iostream>
#include <algorithm>

using namespace std;

//��Ҫ�������ٲźϷ�
const int needNum[5] = { 16, 1, 1, 1, 1 };
//����ܴ�������
const int mostTake[5] = { 0, 0, 0, 2, 2 };

//�ƺʹ������ַ��Ķ�Ӧ
//3:3�� 4:4��5:5��6:6��7:7��8:8��9:9��a:10��b:J�� c:Q�� d:K�� e:A, f:2, g:��

enum pokerType {
	illegal = 0,//�Ƿ�
	single = 1,      //����, ˳��
	couple = 2,     //����, ����
	three = 3,      //����һ������һ��, �ɻ�
	four = 4,       //�Ĵ�һ���Ĵ���
	bomb = 5,       //ը��
	rocket = 6,     //���
};

//��������ͺ������صĽ��
class checkResult {
public:
	char maxChar;   //���ڱȽϴ�С���ַ�
	pokerType pType;//�Ƶ�����
	checkResult(pokerType _pType = illegal, char _maxChar = '3') {
		this->maxChar = _maxChar;
		this->pType = _pType;
	}
};
class checkPoker {

public:
	checkPoker();
	virtual ~checkPoker();

	//��������ַ����в�������Ϊnum���ַ�
	static void findCharByNumber(char *retStr, std::string &srcStr, int num);
	//����ַ����е��ַ��Ƿ�����
	static bool checkCharIsConnect(const char *str);
	//����Ƶ�����
	static checkResult checkType(std::string &pokerList);
	//�ж��ƵĴ�С
	static bool checkPoker::pokerCmp(std::string &a, std::string &b);
};


#endif