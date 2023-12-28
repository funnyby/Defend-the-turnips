#include "..\Classes\BulletClasses\shit.h"
#include "..\Classes\Monster\My_monster.h"

bool shitBullet::initshitBullet(int grade)
{
	if (!Bullet::init())
	{
		return false;
	}
	myGrade = grade;
	speed = (grade - 1) * 200 + 1000;
	attackDamage = 10 + (grade - 1) * 2;
	_freeze = -10*grade;

	bulletSprite->initWithFile("Bullets/ShitBullets/Shit" + StringUtils::toString(grade * 10 + 1) + ".png");//初始化
	//飞的过程的纹理的变化设置
	Animation* blinkAnimation = Animation::create();    //twist animate action
	blinkAnimation->setDelayPerUnit(1.0f / 2);//动画共3帧，运行时间0.6秒
	blinkAnimation->setRestoreOriginalFrame(true);//动画执行完后返回第一帧

	Texture2D* texture1 = Director::getInstance()->getTextureCache()->addImage("Bullets/ShitBullets/Shit" + StringUtils::toString(myGrade * 10 + 1) + ".png");
	blinkAnimation->addSpriteFrameWithTexture(texture1, Rect(0, 0, 70, 70));
	Texture2D* texture2 = Director::getInstance()->getTextureCache()->addImage("Bullets/ShitBullets/Shit" + StringUtils::toString(myGrade * 10 + 2) + ".png");
	blinkAnimation->addSpriteFrameWithTexture(texture2, Rect(0, 0, 70, 70));
	bulletSprite->runAction(RepeatForever::create(Animate::create(blinkAnimation)));
	return true;
}
void shitBullet::rotateSpriteToDirection() {
	//方向向量
	const Vec2 direction = dst - src;

	//两点间距离
	const float distance = src.distance(dst);

	//动作持续时间
	const float durTime = distance / speed;

	// 计算角度（弧度）
	const float angle = atan2(direction.y, direction.x);

	// 将弧度转换为角度
	const float rotation = CC_RADIANS_TO_DEGREES(angle);

	// 设置精灵的旋转角度
	bulletSprite->setRotation(-rotation);

	//射击动画
	shootBy = MoveBy::create(durTime, direction);
}
void shitBullet::inputBulletAction(Point towerLoc, Point MonsterLoc) {
	src = towerLoc, dst = MonsterLoc;//设置两个点
	bulletSprite->setPosition(src);//初始定位
	this->rotateSpriteToDirection();//计算角度制作动画
}
void shitBullet::shoot() {
	runAction(Sequence::create(shootBy,
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
/*	for (int j = 0; j < monsterContainer.size(); j++) {
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
	*/
	if (isMissed) {
		//渐渐消失
		bulletSprite->runAction(Sequence::create(FadeOut::create(0.3f)
			, CallFuncN::create(CC_CALLBACK_0(Bullet::removeFromParent, this))
			, NULL));
	}
	else {
		this->removeFromParent();
	}
}