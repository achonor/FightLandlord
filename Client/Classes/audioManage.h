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
	//cocos的音频管理单例
	SimpleAudioEngine* simpleAudioEngine;
	//根据平台获取完整文件名
	std::string getFileName(const std::string &fileName);

public:
	virtual ~audioManage();
	static audioManage* getInstance();

public:
	//播放音乐
	void playMusic(const char* fileName, bool isLoop = false);
	//停止播放音乐
	void stopMusic();
	//获取音乐音量(0 - 100)
	int getMusicVolume();
	//设置音乐音量(0 - 100)
	void setMusicVolume(int volume);
	//播放音效(返回值为音效ID)
	unsigned int playEffect(const char* fileName, bool isLoop = false);
	//暂停播放(使用播放时返回的ID控制)
	void stopEffect(unsigned int soundId);
	//停止播放所所有音效
	void stopAllEffects();
	//获取音效音量(0 - 100)
	int getEffectsVolume();
	//设置音效音量(0 - 100)
	void setEffectsVolume(int volume);
};

#endif