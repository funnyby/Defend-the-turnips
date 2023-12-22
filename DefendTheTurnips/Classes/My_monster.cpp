#include"My_monster.h"

USING_NS_CC;
using namespace cocos2d::ui;
int blood=10;


void Monster::initmonster() {
	//在地图起点处放置一个怪物
	initWithFile("monster/1.png");

	_walkSpeed = 0.01;

	this->setPosition(170, 485);
	auto moveTo = MoveTo::create(map[1].path* _walkSpeed,Vec2(map[1].x, map[1].y));
	auto moveTo1 = MoveTo::create(map[2].path * _walkSpeed, Vec2(map[2].x, map[2].y));
	auto moveTo2 = MoveTo::create(map[3].path * _walkSpeed, Vec2(map[3].x, map[3].y));
	auto moveTo3 = MoveTo::create(map[4].path * _walkSpeed, Vec2(map[4].x, map[4].y));
	auto moveTo4 = MoveTo::create(map[5].path * _walkSpeed, Vec2(map[5].x, map[5].y));
	CCSequence* actionSequence = CCSequence::create(moveTo, moveTo1,moveTo2, moveTo3,moveTo4,NULL);
	runAction(actionSequence);
}

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

void Monster::isFreezed() {
	if (_freeze == 1) {
		_walkSpeed *= 0.8;
	}
}