#include"My_monster.h"

void Monster::initmonster() {
	//在地图起点处放置一个怪物
	cocos2d::Texture2D* texture = getTexture();
	texture->loadTexture("monster/1.png");
	setTexture(texture);
	setPosition(Vec2(170, 485));
	cocos2d::MoveTo* moveTo = MoveTo::create(map[1].path * 0.01, Vec2(map[1].x, map[1].y));
	cocos2d::MoveTo* moveTo1 = MoveTo::create(map[2].path * 0.01, Vec2(map[2].x, map[2].y));
	cocos2d::MoveTo* moveTo2 = MoveTo::create(map[3].path * 0.01, Vec2(map[3].x, map[3].y));
	cocos2d::MoveTo* moveTo3 = MoveTo::create(map[4].path * 0.01, Vec2(map[4].x, map[4].y));
	cocos2d::MoveTo* moveTo4 = MoveTo::create(map[5].path * 0.01, Vec2(map[5].x, map[5].y));
	CCSequence* actionSequence = CCSequence::create(moveTo, moveTo1, moveTo2, moveTo3, moveTo4, NULL);
	runAction(actionSequence);
}