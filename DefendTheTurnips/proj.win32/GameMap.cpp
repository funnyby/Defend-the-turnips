#include "ChooseLevel.h"
#include "MainScene.h"
#include "EnterScene.h"
#include "GameMap.h"
#include "Way.h"
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
	
	
	//添加一个萝卜在终点处
	auto CarrotSprite = Carrot::create();
	this->addChild(CarrotSprite, 1000);
	CarrotSprite->setLocation(Vec2(1000, 485));
	CarrotSprite->init();

	//对萝卜的眨眼动画展示

	//在地图起点处放置一个怪物
	auto monsterSprite = Monster::create();
	this->addChild(monsterSprite, 0);
	schedule(schedule_selector(GameMap::init_m), 1);
	monsterSprite->initmonster();
	return true;
}
void GameMap::init_m(float delta) {
	auto monsterSprite = Monster::create();
	this->addChild(monsterSprite, 0);
	monsterSprite->initmonster();
}
bool InitUI()
{
	
	return true;
}