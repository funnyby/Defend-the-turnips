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

	bulletSprite->initWithFile("Bullets/ShitBullets/Shit" + StringUtils::toString(grade * 10 + 1) + ".png");//��ʼ��
	//�ɵĹ��̵�����ı仯����
	Animation* blinkAnimation = Animation::create();    //twist animate action
	blinkAnimation->setDelayPerUnit(1.0f / 2);//������3֡������ʱ��0.6��
	blinkAnimation->setRestoreOriginalFrame(true);//����ִ����󷵻ص�һ֡

	Texture2D* texture1 = Director::getInstance()->getTextureCache()->addImage("Bullets/ShitBullets/Shit" + StringUtils::toString(myGrade * 10 + 1) + ".png");
	blinkAnimation->addSpriteFrameWithTexture(texture1, Rect(0, 0, 70, 70));
	Texture2D* texture2 = Director::getInstance()->getTextureCache()->addImage("Bullets/ShitBullets/Shit" + StringUtils::toString(myGrade * 10 + 2) + ".png");
	blinkAnimation->addSpriteFrameWithTexture(texture2, Rect(0, 0, 70, 70));
	bulletSprite->runAction(RepeatForever::create(Animate::create(blinkAnimation)));
	return true;
}
void shitBullet::rotateSpriteToDirection() {
	//��������
	const Vec2 direction = dst - src;

	//��������
	const float distance = src.distance(dst);

	//��������ʱ��
	const float durTime = distance / speed;

	// ����Ƕȣ����ȣ�
	const float angle = atan2(direction.y, direction.x);

	// ������ת��Ϊ�Ƕ�
	const float rotation = CC_RADIANS_TO_DEGREES(angle);

	// ���þ������ת�Ƕ�
	bulletSprite->setRotation(-rotation);

	//�������
	shootBy = MoveBy::create(durTime, direction);
}
void shitBullet::inputBulletAction(Point towerLoc, Point MonsterLoc) {
	src = towerLoc, dst = MonsterLoc;//����������
	bulletSprite->setPosition(src);//��ʼ��λ
	this->rotateSpriteToDirection();//����Ƕ���������
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
			monster->setFreeze(3);//���Ķ�
			monster->update(1);//?
			isMissed = false;
		}
	}
	*/
	if (isMissed) {
		//������ʧ
		bulletSprite->runAction(Sequence::create(FadeOut::create(0.3f)
			, CallFuncN::create(CC_CALLBACK_0(Bullet::removeFromParent, this))
			, NULL));
	}
	else {
		this->removeFromParent();
	}
}