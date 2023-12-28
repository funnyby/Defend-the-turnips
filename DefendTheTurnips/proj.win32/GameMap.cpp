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
	

	boshu = 1;
	monsternum = 0;
	die_monsternum = 0;

	auto CarrotSprite = Carrot::create();
	CarrotSprite->setLocation(Vec2(1000, 485));
	this->addChild(CarrotSprite, 100);
	CarrotSprite->initCarrot();
	CarrotSprite->schedule(schedule_selector(Carrot::update), 2.0f);
	
	this->scheduleOnce(schedule_selector(GameMap::bo), 1);
	
	/*auto BulletSprite1 = GreenTowerBullet::create();
	this->addChild(BulletSprite1, 3);
	BulletSprite1->initGreenBullet(1);

	BulletSprite->monsterContainer.pushBack(monsterSprite);
	BulletSprite1->inputBulletAction(Vec2(1000, 300), Vec2(335, 300));//src\dst
    BulletSprite1->shoot();
    */
	return true;
}

void GameMap::init_m1(float delta) {
	auto monsterSprite = Monster::create();
	this->addChild(monsterSprite, 100 - monsternum);
	monsterSprite->initmonster_type1();
	monsterSprite->schedule(schedule_selector(Monster::update), 0.05f);
	monsternum++;
}

void GameMap::init_m2(float delta) {
	auto monsterSprite = Monster::create();
	this->addChild(monsterSprite, 100 - monsternum);
	monsterSprite->initmonster_type2();
	monsterSprite->schedule(schedule_selector(Monster::update), 0.05f);
	monsternum++;
}

void GameMap::init_m3(float delta) {
	monsternum++;
	auto monsterSprite = Monster::create();
	this->addChild(monsterSprite, 100 - monsternum);
	monsterSprite->initmonster_type3();
	monsterSprite->schedule(schedule_selector(Monster::update), 0.05f);
}

bool InitUI()
{
	
	return true;
}

void GameMap::bo(float a) {

	switch (boshu)
	{
		case 1:
			//��һ�����������
			schedule(schedule_selector(GameMap::init_m3), 1, 4, 1);
			break;
		case 2:
			//�ڶ����������ú��
			schedule(schedule_selector(GameMap::init_m1), 1, 4, 1);
			break;
		case 3:
			//�����������С����
			schedule(schedule_selector(GameMap::init_m2), 1, 4, 1);
			break;
		case 4:
			//���Ĳ����������
			schedule(schedule_selector(GameMap::init_m3), 1, 4, 1);
			break;
		case 5:
			schedule(schedule_selector(GameMap::init_m3), 1, 4, 1);
			break;
		case 6:
			//���岨�������
			schedule(schedule_selector(GameMap::init_m2), 1, 4, 1);
			break;
		case 7:
			schedule(schedule_selector(GameMap::init_m1), 1, 4, 1);
			break;
	}
	boshu++;
	if (boshu < 6)
		this->schedule(schedule_selector(GameMap::next_bo), 3);
	else
	{
		this->scheduleOnce(schedule_selector(GameMap::bo), 5);
	}
}

void GameMap::next_bo(float a) {
	if (die_monsternum == monsternum)
	{
		this->unschedule(schedule_selector(GameMap::next_bo));
		this->GameMap::bo(0.1f);
	}
}