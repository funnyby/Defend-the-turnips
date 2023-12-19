#include "ChooseLevel.h"
#include "MainScene.h"
#include"EnterScene.h"
#include"GameMap.h"
#include<vector>

USING_NS_CC;
using namespace cocos2d::ui;

cocos2d::Scene* GameMap::createScene()
{
	return GameMap::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading:%s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameMap.cpp\n");
}

bool GameMap::init()
{
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// ��ӱ���
	auto background = Sprite::create("GameMap/map.png");  // ʹ����ı���ͼƬ�ļ���
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	// �������ű���������Ӧ��Ļ
	float scaleX = visibleSize.width / background->getContentSize().width;
	float scaleY = visibleSize.height / background->getContentSize().height;

	// ���þ��������
	background->setScale(scaleX, scaleY);
	this->addChild(background);
	return true;
}

bool InitUI()
{
	
	return true;
}