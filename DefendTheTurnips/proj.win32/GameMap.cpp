#include "ChooseLevel.h"
#include "MainScene.h"
#include "EnterScene.h"
#include "GameMap.h"
#include "Way.h"
#include<vector>
#include <iostream>
#include <thread>
#include <chrono>

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

bool isSpriteInBounds(Sprite* sprite1, Sprite* sprite2) {
	// 获取精灵的包围盒
	Rect sprite1BoundingBox = sprite1->getBoundingBox();
	Rect sprite2BoundingBox = sprite2->getBoundingBox();

	// 判断两个包围盒是否相交
	if (sprite1BoundingBox.intersectsRect(sprite2BoundingBox)) {
		return true; // 精灵1进入了精灵2的范围内
	}
	return false; // 精灵1没有进入精灵2的范围内
}//此过程没有用到

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
	this->addChild(background,-1);
	
	
	//添加一个萝卜在终点处
	auto CarrotSprite = Carrot::create();
	CarrotSprite->setLocation(Vec2(1000, 485));
	this->addChild(CarrotSprite, 1000);
	//萝卜血量状态的更新
/*	
	// 创建一个BoundingBox对象来表示矩形区域*/
	Rect BoundingBox = CarrotSprite->getBoundingBox();
	/*if (CarrotSprite->GameOver())
		timerThread.join();*/
	// 创建一个触摸事件监听器
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true); // 设置吞噬触摸事件，防止事件向下传递

	// 在触摸开始时判断触摸点是否在矩形区域内
	listener->onTouchBegan = [&](Touch* touch, Event* event) {
		// 获取触摸点的位置
		auto touchPosition = touch->getLocation();

		// 判断触摸点是否在矩形区域内
		if (BoundingBox.containsPoint(touchPosition)) {
			// 在区域内进行了点击操作
			// 在这里处理相应的逻辑
			CarrotSprite->isCarrotClicked = true;
			schedule(schedule_selector(Carrot::updateCarrot), 1);
			return true; // 返回true表示吞噬触摸事件
		}
		return false; // 返回false表示不吞噬触摸事件
	};

	// 添加触摸事件监听器到事件分发器
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, CarrotSprite);


	//在地图起点处放置一个怪物
	auto monsterSprite = Monster::create();
	this->addChild(monsterSprite, 0);
	schedule(schedule_selector(GameMap::init_m), 1);
	monsterSprite->initmonster();
//	schedule(schedule_selector(Carrot::updateCarrot), 1);
	unschedule(schedule_selector(Carrot::updateCarrot));

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