#include "..\Classes\BulletClasses\shit.h"
#include "..\Classes\GameData\GameManager.h"
#include "..\Classes\Monster\My_monster.h"

bool shitBullet::initshitBullet()
{
	if (!Bullet::init())
	{
		return false;
	}
	speed = 10;
	attackDamage = 4;
	bulletSprite->initWithFile("Bullets/GreenBottleBullets/PBottle11.png");//初始化
	bulletSprite->setPosition(Vec2(650, 300));
	//this->rotateSpriteToDirection(Vec2(650, 300), Vec2(1000, 485));
	this->inputBulletAction(Vec2(650, 300), Vec2(650, 500));
	this->runAction(Sequence::create(shootTo, FadeOut::create(0.2f)
		, CallFuncN::create(CC_CALLBACK_0(Bullet::removeFromParent, this)), NULL));
	return true;
}
void shitBullet::rotateSpriteToDirection(Point src, Point dst) {
	Vec2 direction = dst - src;

	// 计算角度（弧度）
	float angle = atan2(direction.y, direction.x);

	// 将弧度转换为角度
	float rotation = CC_RADIANS_TO_DEGREES(angle);

	// 设置精灵的旋转角度
	this->setRotation(360 - rotation);
}
void shitBullet::inputBulletAction(Point towerLoc, Point MonsterLoc) {
	bulletSprite->setPosition(towerLoc);
	this->rotateSpriteToDirection(towerLoc, MonsterLoc);
	float durTime = towerLoc.distance(MonsterLoc) / speed;
	shootTo = MoveTo::create(durTime, MonsterLoc);
}
void shitBullet::shoot() {
	runAction(Sequence::create(shootTo,
		CallFuncN::create(CC_CALLBACK_0(shitBullet::removeBullet, this)), NULL));
}
void shitBullet::removeBullet() {
	bool isMissed = true;
	auto instance = Director::getInstance();

	auto bulletRect = Rect(this->getPositionX() + this->getParent()->getPositionX() - this->getContentSize().width / 2,
		this->getPositionY() + this->getParent()->getPositionY() - this->getContentSize().height / 2,
		this->bulletSprite->getContentSize().width,
		this->bulletSprite->getContentSize().height);
	//auto monsterVector = instance->monsterContainer;
	for (int j = 0; j < monsterContainer.size(); j++) {
		auto monster = monsterContainer.at(j);
		auto monsterRect = monster->getBoundingBox();

		if (monsterRect.intersectsRect(bulletRect)){
			auto currHp = monster->getHP();

			currHp = currHp - this->getAttackDamage() ;

			if (currHp <= 0) {
				currHp = 0;
			}
			monster->setHP(currHp);
			monster->setFreeze(3);//待改动
			monster->update(1);//?
			isMissed = false;
		}
	}

	if (isMissed) {
		//渐渐消失
		bulletSprite->runAction(Sequence::create(FadeOut::create(1.0f)
			, CallFuncN::create(CC_CALLBACK_0(Bullet::removeFromParent, this))
			, NULL));
	}
	else {
		this->removeFromParent();
	}
}