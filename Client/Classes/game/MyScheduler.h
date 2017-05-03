#ifndef MYSCHEDULER_H
#define MYSCHEDULER_H
#pragma once
#include "stdafx.h"
#include "cocos2d.h"
#include <iostream>

USING_NS_CC;
using namespace std;

class MyScheduler :public Node{
public:
	static MyScheduler* getInstance();

private:
	MyScheduler();
	MyScheduler(const MyScheduler&);
	MyScheduler& operator=(const MyScheduler&);
	
	static MyScheduler* instance;
	//scheduleScriptFunc
	//scheduleGlobal
	//unscheduleGlobal
	//performWithDelayGlobal();


private:
	class GC
	{
	public:
		~GC(){
			if (NULL != instance){
				delete instance;
				instance = NULL;
			}
		}
	};
	static GC gc;
};

#endif