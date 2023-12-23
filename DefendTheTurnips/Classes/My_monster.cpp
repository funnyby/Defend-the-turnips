#include"My_monster.h"

USING_NS_CC;
using namespace cocos2d::ui;

int blood;

void Monster::initmonster() {
	//�ڵ�ͼ��㴦����һ������
	initWithFile("monster/1.png");

	//_walkSpeed =200;
	_walkSpeed =0.01;
	_hp = 100;
	_freeze = -1;

	this->create_Health_bar();
	this->scheduleBlood();
	this->setPosition(170, 485);

	//beginningWaypoint.x = map[0].x;
	//beginningWaypoint.y = map[0].y;
	//destinationWaypoint.x = map[1].x;
	//destinationWaypoint.y = map[1].y;

	auto moveTo = MoveTo::create(map[1].path* _walkSpeed,Vec2(map[1].x, map[1].y));
	auto moveTo1 = MoveTo::create(map[2].path * _walkSpeed, Vec2(map[2].x, map[2].y));
	auto moveTo2 = MoveTo::create(map[3].path * _walkSpeed, Vec2(map[3].x, map[3].y));
	auto moveTo3 = MoveTo::create(map[4].path * _walkSpeed, Vec2(map[4].x, map[4].y));
	auto moveTo4 = MoveTo::create(map[5].path * _walkSpeed, Vec2(map[5].x, map[5].y));
	CCSequence* actionSequence = CCSequence::create(moveTo, moveTo1,moveTo2, moveTo3,moveTo4,NULL);
	runAction(actionSequence);
}

void Monster::update(float dt) {
	int waypoint = 1;
	_freeze += 1;
	this->isDie();
	this->isFreezed();
	this->scheduleBlood();
	//this->walk();
	//this->judge_dest(waypoint);
}

void Monster::create_Health_bar() {
	auto sprite = Sprite::create("monster/3.png");   //�������ȿ�
	sprite->setScaleX(0.12f); // ��������x���ϵĴ�С��С��ԭ����50%  
	sprite->setScaleY(0.12f); // ��������y���ϵĴ�С��С��ԭ����50%
	sprite->setPosition(40, 90); //���ÿ��λ��
	this->addChild(sprite);            //�ӵ�Ĭ��ͼ������ȥ
	auto sprBlood = Sprite::create("monster/4.png");  //����Ѫ��
	ProgressTimer* progress = ProgressTimer::create(sprBlood); //����progress����
	progress->setType(ProgressTimer::Type::BAR);        //���ͣ���״
	progress->setScaleX(0.12f); // ��������x���ϵĴ�С��С��ԭ����50%  
	progress->setScaleY(0.12f); // ��������y���ϵĴ�С��С��ԭ����50%
	progress->setPosition(40, 90);
	//���ҵ������Ѫ��
	progress->setMidpoint(Point(0, 0.5));     //����Ǵ����ҵĻ����ĳ�(1,0.5)����
	progress->setBarChangeRate(Point(1, 0));
	progress->setTag(BLOOD_BAR);       //��һ�����
	this->addChild(progress);
}

void Monster::scheduleBlood() {
	auto progress = (ProgressTimer*)this->getChildByTag(BLOOD_BAR);
	progress->setPercentage(((_hp) / 100) * 100);  //�����ǰٷ�����ʾ
}

//�ܲ���Ѫ
void loseblood() {
	blood--;
}

void Monster::BiteTurnips() {
	double time = 0;
	for (int i = 1; i <= 5; i++) {
		time += map[1].path * 0.01;
	}
	auto position = this->getPosition();
	if (position.x == map[5].x && position.y == map[5].y)
		loseblood();
}

bool Monster::judge_dest(int& n) {
	//Vec2 pos = this->getPosition();
	//if ((destinationWaypoint.x - pos.x) * (destinationWaypoint.x - pos.x) + (destinationWaypoint.y - pos.y) * (destinationWaypoint.y - pos.y) <= 37)
	//{
	//	beginningWaypoint.x = map[n].x;
	//	beginningWaypoint.y = map[n].y;
	//	destinationWaypoint.x = map[n+1].x;
	//	destinationWaypoint.y = map[n+1].y;
	//	//auto b = Sprite::create("monster/2.png");
	//	//this->addChild(b);
	//	//this->setPosition(70, 485);
	//	//for (int i = 0; i <= 4; i++) {
	//	//	if (map[i].x == destinationWaypoint.x && map[i].y == destinationWaypoint.y) {
	//	//		//auto b = Sprite::create("monster/2.png");
	//	//		//this->addChild(b);
	//	//		//this->setPosition(70, 485);
	//	//		beginningWaypoint.x = map[i].x;
	//	//		beginningWaypoint.y = map[i].y;
	//	//		destinationWaypoint.x = map[i+1].x;
	//	//		destinationWaypoint.y = map[i+1].y;
	//	//		return true;
	//	//	}
	//	//}
	//	return true;
	//}
	//else
		return false;
}

void Monster::walk() {
	//Vec2 pos = this->getPosition();
	//float path = abs(destinationWaypoint.x - beginningWaypoint.x) + abs(destinationWaypoint.y - beginningWaypoint.y);
	//float x = (destinationWaypoint.x - beginningWaypoint.x) / path * _walkSpeed * 0.1f+pos.x;
	//float y = (destinationWaypoint.y - beginningWaypoint.y) / path * _walkSpeed * 0.1f + pos.y;
	//MoveTo* moveto = MoveTo::create(0.1f, Point(x, y));
	//this->runAction(moveto);
}


bool Monster::isFreezed() {
	if (_freeze == 1) {
		_walkSpeed *= 0.5;
		this->schedule(schedule_selector(Monster::unFreezed), 3);
		return true;
	}
	return false;
}

void Monster::unFreezed(float a) {
	_freeze = 0;
}


bool Monster::isDie() {
	if (_hp <= 0)
	{
		//���鱬ը
		auto texture = Director::getInstance()->getTextureCache()->addImage("monster/2.png");
		// �����µ�����  
		this->setTexture(texture);
		this->stopAllActions();
		this->schedule(schedule_selector(Monster::deletemonster), 0.05f);
		return true;
	}
	else
		return false;
}

void Monster::behurt(float a) {
	_hp = 0;
	if (this->isDie()) {
		//ɾ���þ����㣬��ôд����
	}
}

void Monster::deletemonster(float a) {
	this->removeFromParent();
}

//void Monster::behurt(int monster_blood) {
//	_hp -= monster_blood;
//}