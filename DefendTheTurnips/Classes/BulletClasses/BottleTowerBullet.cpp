#include "..\Classes\BulletClasses\BottleTowerBullet.h"
#include "..\Classes\GameData\GameManager.h"
#include "..\Classes\Monster\My_monster.h"

bool GreenTowerBullet::initGreenBullet(int grade)
{
	if (!Bullet::init())
	{
		return false;
	}
	myGrade = grade;
	speed = (grade-1)*50+100;
	attackDamage = 10+(grade - 1)*2;
	bulletSprite->initWithFile("Bullets/GreenBottleBullets/PBottle" + StringUtils::toString(grade*10 +1) + ".png");//初始化
	
/*	Animation* blinkAnimation = Animation::create();    //twist animate action
	blinkAnimation->setDelayPerUnit(0.6f / 3);//动画共3帧，运行时间0.6秒
	blinkAnimation->setRestoreOriginalFrame(true);//动画执行完后返回第一帧

	Texture2D* texture1 = Director::getInstance()->getTextureCache()->addImage("Bullets/GreenBottleBullets/PBottle" + StringUtils::toString(myGrade * 10 + 1) + ".png");
	blinkAnimation->addSpriteFrameWithTexture(texture1, Rect(0, 0, 70, 70));
	Texture2D* texture2 = Director::getInstance()->getTextureCache()->addImage("Bullets/GreenBottleBullets/PBottle" + StringUtils::toString(myGrade * 10 + 2) + ".png");
	blinkAnimation->addSpriteFrameWithTexture(texture2, Rect(0, 0, 70, 70));
	Texture2D* texture3 = Director::getInstance()->getTextureCache()->addImage("Bullets/GreenBottleBullets/PBottle" + StringUtils::toString(myGrade * 10 + 3) + ".png");
	blinkAnimation->addSpriteFrameWithTexture(texture3, Rect(0, 0, 70, 70));
	
	this->runAction(RepeatForever::create(Animate::create(blinkAnimation)));*/
	//this->runAction(Animate::create(blinkAnimation));
	return true;
	
}
void GreenTowerBullet::rotateSpriteToDirection() {

	Vec2 direction = dst - src;
	float distance = src.distance(dst);
	float durTime = distance / speed;
	// 计算角度（弧度）
	float angle = atan2(direction.y, direction.x);

	// 将弧度转换为角度
	float rotation = CC_RADIANS_TO_DEGREES(angle);

	// 设置精灵的旋转角度
	bulletSprite->setRotation(-rotation);
	shootBy = MoveBy::create(durTime, direction);
//	this->runAction(Sequence::create(shootBy, FadeOut::create(0.2f)
	//	, CallFuncN::create(CC_CALLBACK_0(Bullet::removeFromParent, this)), NULL));
	

}
void GreenTowerBullet::inputBulletAction(Point towerLoc, Point MonsterLoc) {
	src = towerLoc, dst = MonsterLoc;
	bulletSprite->setPosition(src);
	this->rotateSpriteToDirection();
}
void GreenTowerBullet::shoot() {
	runAction(Sequence::create(shootBy,
		CallFuncN::create(CC_CALLBACK_0(GreenTowerBullet::removeBullet, this)), NULL));
}
void GreenTowerBullet::removeBullet() {
	bool isMissed = true;
	auto instance = Director::getInstance();

	auto bulletRect = Rect(this->getPositionX() + this->getParent()->getPositionX() - this->getContentSize().width / 2,
		this->getPositionY() + this->getParent()->getPositionY() - this->getContentSize().height / 2,
		this->bulletSprite->getContentSize().width,
		this->bulletSprite->getContentSize().height);
	//auto monsterVector = instance->monsterContainer;
/*for (int j = 0; j < monsterContainer.size(); j++) {
		auto monster = monsterContainer.at(j);
		auto monsterRect = monster->getBoundingBox();

		if (monsterRect.intersectsRect(bulletRect)){
			auto currHp = monster->getHP();

			currHp = currHp - this->getAttackDamage() ;

			if (currHp <= 0) {
				currHp = 0;
			}
			monster->setHP(currHp);
			monster->update(1);//?
			isMissed = false;
		}
	}*/

	if (isMissed) {
		//渐渐消失
		bulletSprite->runAction(Sequence::create(FadeOut::create(0.5f)
			, CallFuncN::create(CC_CALLBACK_0(Bullet::removeFromParent, this))
			, NULL));
	}
	else {
		this->removeFromParent();
	}
}
