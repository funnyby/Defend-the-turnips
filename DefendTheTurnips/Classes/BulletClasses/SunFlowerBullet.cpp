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
	bulletSprite->initWithFile("Bullets/SunFlowerBullets/TSun-hd11.png");//��ʼ��

	return true;
}

void SunFlowerBullet::spreadSpriteToScope() {

	//��ɢ�ľ���
	const float distance = attackRange;

	//��������ʱ��
	const float durTime = (distance / speed) * 100;

	//���þ������ɢ����
	spreadTo = ScaleTo::create(durTime, 100 * distance / 20.0f);
	//bulletSprite->runAction(spreadTo); test use
}

void SunFlowerBullet::inputBulletAction(Point towerLoc) {
	src = towerLoc;//���õ�λ��
	this->setScale(0.3);
	this->setPosition(src);//��ʼ��λ

	this->spreadSpriteToScope();
}

void SunFlowerBullet::spread() {//run���������������
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
		//������ʧ
		bulletSprite->runAction(Sequence::create(FadeOut::create(1.3f)
			, CallFuncN::create(CC_CALLBACK_0(Bullet::removeFromParent, this))
			, NULL));
	}
	else {
		this->removeFromParent();
	}
}