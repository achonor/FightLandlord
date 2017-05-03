#include "stdafx.h"
#include "MyScheduler.h"

MyScheduler* MyScheduler::instance = new MyScheduler();

MyScheduler::MyScheduler() {}
MyScheduler::MyScheduler(const MyScheduler&) {}
MyScheduler& MyScheduler::operator=(const MyScheduler&) { return *instance; }

MyScheduler* MyScheduler::getInstance() {
	return instance;
}

