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
	// ��ȡ����İ�Χ��
	Rect sprite1BoundingBox = sprite1->getBoundingBox();
	Rect sprite2BoundingBox = sprite2->getBoundingBox();

	// �ж�������Χ���Ƿ��ཻ
	if (sprite1BoundingBox.intersectsRect(sprite2BoundingBox)) {
		return true; // ����1�����˾���2�ķ�Χ��
	}
	return false; // ����1û�н��뾫��2�ķ�Χ��
}//�˹���û���õ�

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
	this->addChild(background,-1);
	

	auto CarrotSprite = Carrot::create();
	CarrotSprite->setLocation(Vec2(1000, 485));
	this->addChild(CarrotSprite, 100);
	CarrotSprite->initCarrot();
	CarrotSprite->schedule(schedule_selector(Carrot::update), 2.0f);
	
	/*auto monsterSprite = Monster::create();
	this->addChild(monsterSprite, 0);
	monsterSprite->initmonster_type3();*/
	
	auto BulletSprite = GreenTowerBullet::create();
	this->addChild(BulletSprite, 3);
	BulletSprite->initGreenBullet(3);

	//BulletSprite->monsterContainer.pushBack(monsterSprite);
	
	BulletSprite->inputBulletAction(Vec2(1000, 300), Vec2(335, 300));//src\dst
    BulletSprite->shoot();
	//BulletSprite->upgradeAttackDamage(10);
	
//	BulletSprite->inputBulletAction(Vec2(1000, 300), Vec2(335, 300));//src\dst
	//BulletSprite->shoot();
	//schedule(schedule_selector(GameMap::init_m), 1);
	return true;
}

void GameMap::init_m(float delta) {
	auto monsterSprite = Monster::create();
	this->addChild(monsterSprite, 0);
	monsterSprite->initmonster_type3();
	monsterSprite->schedule(schedule_selector(Monster::update), 0.05f);
}
bool InitUI()
{
	
	return true;
}