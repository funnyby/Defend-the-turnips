#include "..\Classes\BulletClasses\BottleTowerBullet.h"
#include "..\Classes\GameData\GameManager.h"

bool GreenTowerBullet::init()
{
	if (!Bullet::init())
	{
		return false;
	}
	bulletSprite = Sprite::createWithSpriteFrameName("arrow.png");
	addChild(bulletSprite);
	return true;
}
void GreenTowerBullet::shoot() {
	runAction(Sequence::create(bulletAction,
		CallFuncN::create(CC_CALLBACK_0(GreenTowerBullet::removeBullet, this)), NULL));
}
void GreenTowerBullet::removeBullet() {
	bool isMissed = true;
	auto instance = GameManager::getInstance();

	auto bulletRect = Rect(this->getPositionX() + this->getParent()->getPositionX() - this->getContentSize().width / 2,
		this->getPositionY() + this->getParent()->getPositionY() - this->getContentSize().height / 2,
		this->bulletSprite->getContentSize().width,
		this->bulletSprite->getContentSize().height);

	auto monsterVector = instance->monsterVector;

/*	for (int j = 0; j < monsterVector.size(); j++)
	{
		auto monster = monsterVector.at(j);
		auto monsterRect = monster->baseSprite->getBoundingBox();

		if (monsterRect.intersectsRect(bulletRect) && monster->getAttackBySoldier())
		{
			auto currHp = monster->getCurrHp();

			currHp = currHp - this->getAttackDamage() + monster->getArmor();

			if (currHp <= 0) {
				currHp = 0;
			}
			monster->setCurrHp(currHp);

			monster->getHpBar()->setPercentage((currHp / monster->getMaxHp()) * 100);
			monster->getHurt();
			isMissed = false;
			if (currHp == 0) {
				monster->death();
			}
			break;
		}
	}*/
	if (isMissed) {

		bulletSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("decal_arrow.png"));

		bulletSprite->runAction(Sequence::create(FadeOut::create(1.0f)
			, CallFuncN::create(CC_CALLBACK_0(Bullet::removeFromParent, this))
			, NULL));
	}
	else {
		this->removeFromParent();
	}
}