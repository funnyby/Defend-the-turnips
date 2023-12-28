#include "..\Classes\BulletClasses\SunFlowerBullet.h"
#include "..\Classes\Monster\My_monster.h"

bool SunFlowerBullet::initSunBullet(int grade)
{
	if (!Bullet::init())
	{
		return false;
	}
	myGrade = grade;
	if (myGrade == 1)
		setAttackRange(40 * 1.2 + 20);
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
	const float distance = attackRange - 40;

	//动作持续时间
	const float durTime = (distance / speed);

	//设置精灵的扩散动画
	spreadTo = ScaleTo::create(durTime, attackRange /40.0f);
	//bulletSprite->runAction(spreadTo); test use
}

void SunFlowerBullet::inputBulletAction(Point towerLoc) {
	src = towerLoc;//设置点位置
	bulletSprite->setPosition(src);//初始定位
	this->spreadSpriteToScope();
}

void SunFlowerBullet::spread() {//run射击动画动作序列
	bulletSprite->runAction(spreadTo);
	Sleep(200);
	runAction(Sequence::create(
		CallFuncN::create(CC_CALLBACK_0(SunFlowerBullet::removeBullet, this)), NULL));
}

void SunFlowerBullet::removeBullet() {
	bool isMissed = true;
	auto instance = Director::getInstance();

	auto bulletRect = Rect(this->getPositionX() + this->getParent()->getPositionX() - this->getContentSize().width / 2,
		this->getPositionY() + this->getParent()->getPositionY() - this->getContentSize().height / 2,
		this->bulletSprite->getContentSize().width,
		this->bulletSprite->getContentSize().height);

	for (int j = 0; j < monsterContainer.size(); j++) {
		auto monster = monsterContainer.at(j);
		auto monsterRect = monster->getBoundingBox();

		if (monsterRect.intersectsRect(bulletRect)) {
			auto currHp = monster->getHP();

			currHp = currHp - this->getAttackDamage();

			if (currHp <= 0) {
				currHp = 0;
			}
			monster->setHP(currHp);
			monster->update(1);//?
			isMissed = false;
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