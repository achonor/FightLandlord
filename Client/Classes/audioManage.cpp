#include "audioManage.h"
#include "cocos2d.h"


audioManage::audioManage() {
	this->simpleAudioEngine = SimpleAudioEngine::getInstance();
}


audioManage::~audioManage() {

}

audioManage* audioManage::getInstance() {
	static audioManage instance;   //�ֲ���̬����  
	return &instance;
}

std::string audioManage::getFileName(const std::string &fileName) {
	if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) {
		//win32ƽ̨
		return fileName + ".wav";
	} else if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) {
		//androidƽ̨
		return fileName + ".ogg";
	} else if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) {
		//iosƽ̨
		return fileName + ".caf";
	}
	return fileName;
}
//��������
void audioManage::playMusic(const char* fileName, bool isLoop) {
	std::string tmpFileName = this->getFileName(fileName);
	simpleAudioEngine->playBackgroundMusic(tmpFileName.c_str(), isLoop);
}
//ֹͣ��������
void audioManage::stopMusic() {
	simpleAudioEngine->stopBackgroundMusic(true);
}

//��ȡ��������
int audioManage::getMusicVolume() {
	return 100 * simpleAudioEngine->getBackgroundMusicVolume();
}
//������������
void audioManage::setMusicVolume(int volume) {
	simpleAudioEngine->setBackgroundMusicVolume(volume * 0.01);
}

//������Ч(����ֵΪ��ЧID)
unsigned int audioManage::playEffect(const char* fileName, bool isLoop) {
	std::string tmpFileName = this->getFileName(fileName);
	return simpleAudioEngine->playEffect(tmpFileName.c_str(), isLoop);
}

//ֹͣ������Ч(ʹ�ò���ʱ���ص�ID����)
void audioManage::stopEffect(unsigned int soundId) {
	simpleAudioEngine->stopEffect(soundId);
}

//ֹͣ������������Ч
void audioManage::stopAllEffects() {
	simpleAudioEngine->stopAllEffects();
}

//��ȡ��Ч����(0 - 100)
int audioManage::getEffectsVolume() {
	return 100 * simpleAudioEngine->getEffectsVolume();
}

//������Ч����(0 - 100)
void audioManage::setEffectsVolume(int volume) {
	simpleAudioEngine->setEffectsVolume(volume * 0.01);
}