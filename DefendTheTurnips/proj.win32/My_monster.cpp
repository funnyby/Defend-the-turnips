#include"My_monster.h"

//Monster* Monster::create(const std::string& filename)
//{
//	Monster* sprite = new Monster();
//
//	if (sprite && sprite->initWithFile(filename))
//	{
//		sprite->autorelease(); return sprite;
//	}
//	CC_SAFE_DELETE(sprite);
//	return nullptr;
//}

void Monster::initmonster() {
	monsterSprite->setPosition(Vec2(170, 485));
	this->addChild(monsterSprite, 0);
	auto moveTo = MoveTo::create(map[1].path*0.01, Vec2(map[1].x, map[1].y));
	auto moveTo1 = MoveTo::create(map[2].path * 0.01, Vec2(map[2].x, map[2].y));
	auto moveTo2 = MoveTo::create(map[3].path * 0.01, Vec2(map[3].x, map[3].y));
	auto moveTo3 = MoveTo::create(map[4].path * 0.01, Vec2(map[4].x, map[4].y));
	auto moveTo4 = MoveTo::create(map[5].path * 0.01, Vec2(map[5].x, map[5].y));
	CCSequence* actionSequence = CCSequence::create(moveTo, moveTo1,moveTo2, moveTo3,moveTo4,NULL);
	monsterSprite->runAction(actionSequence);
}