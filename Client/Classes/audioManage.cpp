#include "audioManage.h"
#include "cocos2d.h"


audioManage::audioManage() {
	this->simpleAudioEngine = SimpleAudioEngine::getInstance();
}


audioManage::~audioManage() {

}

audioManage* audioManage::getInstance() {
	static audioManage instance;   //局部静态变量  
	return &instance;
}

std::string audioManage::getFileName(const std::string &fileName) {
	if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) {
		//win32平台
		return fileName + ".wav";
	} else if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) {
		//android平台
		return fileName + ".ogg";
	} else if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) {
		//ios平台
		return fileName + ".caf";
	}
	return fileName;
}
//播放音乐
void audioManage::playMusic(const char* fileName, bool isLoop) {
	std::string tmpFileName = this->getFileName(fileName);
	simpleAudioEngine->playBackgroundMusic(tmpFileName.c_str(), isLoop);
}
//停止播放音乐
void audioManage::stopMusic() {
	simpleAudioEngine->stopBackgroundMusic(true);
}

//获取音乐音量
int audioManage::getMusicVolume() {
	return 100 * simpleAudioEngine->getBackgroundMusicVolume();
}
//设置音乐音量
void audioManage::setMusicVolume(int volume) {
	simpleAudioEngine->setBackgroundMusicVolume(volume * 0.01);
}

//播放音效(返回值为音效ID)
unsigned int audioManage::playEffect(const char* fileName, bool isLoop) {
	std::string tmpFileName = this->getFileName(fileName);
	return simpleAudioEngine->playEffect(tmpFileName.c_str(), isLoop);
}

//停止播放音效(使用播放时返回的ID控制)
void audioManage::stopEffect(unsigned int soundId) {
	simpleAudioEngine->stopEffect(soundId);
}

//停止播放所所有音效
void audioManage::stopAllEffects() {
	simpleAudioEngine->stopAllEffects();
}

//获取音效音量(0 - 100)
int audioManage::getEffectsVolume() {
	return 100 * simpleAudioEngine->getEffectsVolume();
}

//设置音效音量(0 - 100)
void audioManage::setEffectsVolume(int volume) {
	simpleAudioEngine->setEffectsVolume(volume * 0.01);
}