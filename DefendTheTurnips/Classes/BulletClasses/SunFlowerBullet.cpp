#include "..\Classes\BulletClasses\SunFlowerBullet.h"
#include "..\Classes\Monster\My_monster.h"

bool SunFlowerBullet::initSunBullet(int grade)
{
	if (!Bullet::init())
	{
		return false;
	}
	myGrade = grade;
	speed = (grade - 1) * 200 + 1000;
	attackDamage = 10 + (grade - 1) * 2;
	bulletSprite->initWithFile("Bullets/SunFlowerBullets/TSun-hd(" + StringUtils::toString((grade-1) * 3 + 1) + ").png");//��ʼ��
	
	return true;
}
void SunFlowerBullet::inputBulletAction(Point towerLoc) {
	src = towerLoc;//���õ�λ��
	bulletSprite->setPosition(src);//��ʼ��λ
}