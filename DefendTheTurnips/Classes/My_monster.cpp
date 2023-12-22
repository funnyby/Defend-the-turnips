#include"My_monster.h"

void Monster::initmonster() {
	//在地图起点处放置一个怪物
	initWithFile("monster/1.png");

	this->setPosition(170, 485);
	CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("monster/1.png");
	this->setTexture(texture);
	auto moveTo = MoveTo::create (map[1].path * 0.01, Vec2(map[1].x, map[1].y));
	auto moveTo1 = MoveTo::create(map[2].path * 0.01, Vec2(map[2].x, map[2].y));
	auto moveTo2 = MoveTo::create(map[3].path * 0.01, Vec2(map[3].x, map[3].y));
	auto moveTo3 = MoveTo::create(map[4].path * 0.01, Vec2(map[4].x, map[4].y));
	auto moveTo4 = MoveTo::create(map[5].path * 0.01, Vec2(map[5].x, map[5].y));
	CCSequence* actionSequence = CCSequence::create(moveTo, moveTo1, moveTo2, moveTo3, moveTo4, NULL);
	runAction(actionSequence);
}