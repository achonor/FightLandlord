#include "stdafx.h"
#include "MyGame.h"
#include "GameScene.h"

USING_NS_CC;
using namespace std;

game::game()
{
}


void game::init() {
	//�������·��
	CCFileUtils::getInstance()->addSearchPath("../../config");

	//��ʼ��GGData
	My_InitGGData();
	
	//��ʼ������
    std::string tmpAddr = My_config["loginAddr"].GetString();
    My_Client->initNet(tmpAddr, My_config["serverPort"].GetInt());
}
	
void game::start() {
	//��Ʒֱ���
	auto designResolutionSize = cocos2d::Size(My_config["resWidth"].GetInt(), My_config["resHeight"].GetInt());

	// ����
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		glview = GLViewImpl::createWithRect("FightLandlord", Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
		glview = GLViewImpl::create("FightLandlord");
#endif
		director->setOpenGLView(glview);
	}

	// ���½���ʾfps
	director->setDisplayStats(true);

	// ÿ��ˢ�´�����֡����
	director->setAnimationInterval(1.0 / 30);

	// ������Ʒֱ���
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::FIXED_WIDTH);

	// ������ʼ����
	auto scene = GameLayer::createScene();
	director->runWithScene(scene);
	scene->addChild(My_Client);
}

game::~game()
{
}
