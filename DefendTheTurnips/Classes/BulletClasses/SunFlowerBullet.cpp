#include "..\Classes\BulletClasses\SunFlowerBullet.h"
#include "..\Classes\Monster\My_monster.h"

bool SunFlowerBullet::initSunBullet(int grade)
{
	if (!Bullet::init())
	{
		return false;
	}
	setAnchorPoint(Vec2(0.5, 0.5));
	myGrade = grade;
	if (myGrade == 1)
		setAttackRange(40 * 1.5 + 20);
	else if (myGrade == 2)
		setAttackRange(40 * 1.8 + 20);
	else
		setAttackRange(40 * 2.5 + 20);
	speed = (grade - 1) * 40 + 100;
	attackDamage = 10 + (grade - 1) * 2;
	bulletSprite->initWithFile("Bullets/SunFlowerBullets/TSun-hd11.png");//初始化

	return true;
}

void SunFlowerBullet::spreadSpriteToScope() {

	//扩散的距离
	const float distance = attackRange;

	//动作持续时间
	const float durTime = (distance / speed) * 100;

	//设置精灵的扩散动画
	spreadTo = ScaleTo::create(durTime, 100 * distance / 20.0f);
	//bulletSprite->runAction(spreadTo); test use
}

void SunFlowerBullet::inputBulletAction(Point towerLoc) {
	src = towerLoc;//设置点位置
	this->setScale(0.3);
	this->setPosition(src);//初始定位

	this->spreadSpriteToScope();
}

void SunFlowerBullet::spread() {//run射击动画动作序列
	bulletSprite->runAction(spreadTo);
	runAction(Sequence::create(
		CallFuncN::create(CC_CALLBACK_0(SunFlowerBullet::removeBullet, this)), NULL));
}

void SunFlowerBullet::removeBullet() {
	bool isMissed = true;

	auto bulletRect = Rect(this->getPositionX() + this->getParent()->getPositionX() - attackRange-20,
		this->getPositionY() + this->getParent()->getPositionY() - attackRange -20,
		this->bulletSprite->getContentSize().width+20,
		this->bulletSprite->getContentSize().height+20);
	
	for (int j = 0; j < monsterContainer.size(); j++) {
		auto monster = monsterContainer.at(j);
		auto monsterRect = monster->getBoundingBox();

		if (monsterRect.intersectsRect(bulletRect)) {
			monster->behurt(this->getAttackRange(), 3);
		}
	}
	for (int j = 0; j < BarrierContainer.size(); j++) {
		auto barrier1 = BarrierContainer.at(j);
		auto barrierRect = barrier1->getBoundingBox();
		if (barrierRect.intersectsRect(bulletRect)) {
			barrier1->behurt(this->getAttackDamage(), 1);
		}
	}

	if (isMissed) {
		//渐渐消失
		bulletSprite->runAction(Sequence::create(FadeOut::create(1.3f)
			, CallFuncN::create(CC_CALLBACK_0(Bullet::removeFromParent, this))
			, NULL));
	}
	else {
		this->removeFromParent();
	}
}