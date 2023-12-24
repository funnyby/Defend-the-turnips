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
	
	
	//���һ���ܲ����յ㴦
	auto CarrotSprite = Carrot::create();
	CarrotSprite->setLocation(Vec2(1000, 485));
	this->addChild(CarrotSprite, 1000);
	//�ܲ�Ѫ��״̬�ĸ���
/*	
	// ����һ��BoundingBox��������ʾ��������*/
	Rect BoundingBox = CarrotSprite->getBoundingBox();
	/*if (CarrotSprite->GameOver())
		timerThread.join();*/
	// ����һ�������¼�������
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true); // �������ɴ����¼�����ֹ�¼����´���

	// �ڴ�����ʼʱ�жϴ������Ƿ��ھ���������
	listener->onTouchBegan = [&](Touch* touch, Event* event) {
		// ��ȡ�������λ��
		auto touchPosition = touch->getLocation();

		// �жϴ������Ƿ��ھ���������
		if (BoundingBox.containsPoint(touchPosition)) {
			// �������ڽ����˵������
			// �����ﴦ����Ӧ���߼�
			CarrotSprite->isCarrotClicked = true;
			schedule(schedule_selector(Carrot::updateCarrot), 1);
			return true; // ����true��ʾ���ɴ����¼�
		}
		return false; // ����false��ʾ�����ɴ����¼�
	};

	// ��Ӵ����¼����������¼��ַ���
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, CarrotSprite);


	//�ڵ�ͼ��㴦����һ������
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