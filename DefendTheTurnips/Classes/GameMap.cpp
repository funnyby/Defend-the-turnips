#include "ChooseLevel.h"
#include "MainScene.h"
#include"EnterScene.h"
#include"GameMap.h"
#include"Way.h"
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
	// 添加背景
	auto background = Sprite::create("GameMap/map.png");  // 使用你的背景图片文件名
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	// 计算缩放比例，以适应屏幕
	float scaleX = visibleSize.width / background->getContentSize().width;
	float scaleY = visibleSize.height / background->getContentSize().height;

	// 设置精灵的缩放
	background->setScale(scaleX, scaleY);
	this->addChild(background);

	//在地图起点处放置一个怪物
	auto monsterSprite = Monster::create("monster/1.png");
	monsterSprite->setPosition(Vec2(170, 485));
	this->addChild(monsterSprite, 0);
	auto moveTo = MoveTo::create(map[1].path*0.01, Vec2(map[1].x, map[1].y));
	auto moveTo1 = MoveTo::create(map[2].path * 0.01, Vec2(map[2].x, map[2].y));
	auto moveTo2 = MoveTo::create(map[3].path * 0.01, Vec2(map[3].x, map[3].y));
	auto moveTo3 = MoveTo::create(map[4].path * 0.01, Vec2(map[4].x, map[4].y));
	auto moveTo4 = MoveTo::create(map[5].path * 0.01, Vec2(map[5].x, map[5].y));
	CCSequence* actionSequence = CCSequence::create(moveTo, moveTo1,moveTo2, moveTo3,moveTo4,NULL);
	monsterSprite->runAction(actionSequence);

	//auto monsterSprite = Monster::create();
	//this->addChild(monsterSprite, 0);
	//monsterSprite->initmonster();
	return true;
}

bool InitUI()
{
	
	return true;
}