#pragma once
#ifndef AUDIOMANAGE_H
#define AUDIOMANAGE_H
#include <iostream>
#include "SimpleAudioEngine.h"

using namespace std;
using namespace CocosDenshion;

class audioManage {
private:
	audioManage();
	audioManage(const audioManage &) {}
	audioManage & operator = (const audioManage &) {}
private:
	//cocos����Ƶ������
	SimpleAudioEngine* simpleAudioEngine;
	//����ƽ̨��ȡ�����ļ���
	std::string getFileName(const std::string &fileName);

public:
	virtual ~audioManage();
	static audioManage* getInstance();

public:
	//��������
	void playMusic(const char* fileName, bool isLoop = false);
	//ֹͣ��������
	void stopMusic();
	//��ȡ��������(0 - 100)
	int getMusicVolume();
	//������������(0 - 100)
	void setMusicVolume(int volume);
	//������Ч(����ֵΪ��ЧID)
	unsigned int playEffect(const char* fileName, bool isLoop = false);
	//��ͣ����(ʹ�ò���ʱ���ص�ID����)
	void stopEffect(unsigned int soundId);
	//ֹͣ������������Ч
	void stopAllEffects();
	//��ȡ��Ч����(0 - 100)
	int getEffectsVolume();
	//������Ч����(0 - 100)
	void setEffectsVolume(int volume);
};

#endif