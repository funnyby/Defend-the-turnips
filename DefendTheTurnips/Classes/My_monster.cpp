#include"My_monster.h"

USING_NS_CC;
using namespace cocos2d::ui;

int blood;

void Monster::initmonster() {
	//�ڵ�ͼ��㴦����һ������
	initWithFile("monster/1.png");

	_walkSpeed =100;
	//_walkSpeed =0.01;
	_hp = 100;
	_freeze = -1;
	waypoint = 1;
	isalive = 1;

	this->create_Health_bar();
	this->scheduleBlood();
	this->setPosition(170, 485);

	beginningWaypoint.x = map[0].x;
	beginningWaypoint.y = map[0].y;
	destinationWaypoint.x = map[1].x;
	destinationWaypoint.y = map[1].y;

}

void Monster::update(float dt) {
	_hp-=5;
	this->isDie();
	this->isFreezed();
	this->scheduleBlood();
	this->walk();
	this->judge_dest();
	if (!this->isalive)
		this->unschedule(schedule_selector(Monster::update));
}

void Monster::create_Health_bar() {
	auto sprite = Sprite::create("monster/3.png");   //�������ȿ�
	sprite->setScaleX(0.12f); // ��������x���ϵĴ�С��С��ԭ����50%  
	sprite->setScaleY(0.12f); // ��������y���ϵĴ�С��С��ԭ����50%
	sprite->setPosition(40, 90); //���ÿ��λ��
	this->addChild(sprite);            //�ӵ�Ĭ��ͼ������ȥ
	auto sprBlood = Sprite::create("monster/4.png");  //����Ѫ��
	ProgressTimer* progress = ProgressTimer::create(sprBlood); //����progress����
	progress->setType(ProgressTimer::Type::BAR);        //���ͣ���״
	progress->setScaleX(0.12f); // ��������x���ϵĴ�С��С��ԭ����50%  
	progress->setScaleY(0.12f); // ��������y���ϵĴ�С��С��ԭ����50%
	progress->setPosition(40, 90);
	//���ҵ������Ѫ��
	progress->setMidpoint(Point(0, 0.5));     //����Ǵ����ҵĻ����ĳ�(1,0.5)����
	progress->setBarChangeRate(Point(1, 0));
	progress->setTag(BLOOD_BAR);       //��һ�����
	this->addChild(progress);
}

void Monster::scheduleBlood() {
	auto progress = (ProgressTimer*)this->getChildByTag(BLOOD_BAR);
	progress->setPercentage(((_hp) / 100) * 100);  //�����ǰٷ�����ʾ
}

//�ܲ���Ѫ
void loseblood() {
	blood--;
}

void Monster::BiteTurnips() {
	//double time = 0;
	//for (int i = 1; i <= 5; i++) {
	//	time += map[1].path * 0.01;
	//}
	//auto position = this->getPosition();
	//if (position.x == map[5].x && position.y == map[5].y)
	//	loseblood();
}

bool Monster::judge_dest() {
	Vec2 pos = this->getPosition();
	if ((destinationWaypoint.x - pos.x) * (destinationWaypoint.x - pos.x) + (destinationWaypoint.y - pos.y) * (destinationWaypoint.y - pos.y) <= 666)
	{
		waypoint++;
		beginningWaypoint.x = destinationWaypoint.x;
		beginningWaypoint.y = destinationWaypoint.y;
		destinationWaypoint.x = map[waypoint].x;
		destinationWaypoint.y = map[waypoint].y;
		//if(waypoint >3)
		//{
		//	auto b = Sprite::create("monster/2.png");
		//	this->addChild(b);
		//	this->setPosition(70, 485);
		//}
		return true;
	}
	else
		return false;
}

void Monster::walk() {
	Vec2 pos = this->getPosition();
	float path = map[waypoint].path;
	float x = _walkSpeed * 0.1f*(destinationWaypoint.x - beginningWaypoint.x) / path +pos.x;
	float y = _walkSpeed * 0.1f * (destinationWaypoint.y - beginningWaypoint.y) /path + pos.y;
	MoveTo* moveto = MoveTo::create(0.1f, Point(x, y));
	this->runAction(moveto);
}


bool Monster::isFreezed() {
	if (_freeze == 1) {
		_walkSpeed *= 0.5;
		this->schedule(schedule_selector(Monster::unFreezed), 3);
		auto sprite = Sprite::create("monster/5.png");   //�������ȿ�
		sprite->setScaleX(0.03f); // ��������x���ϵĴ�С��С��ԭ����50%  
		sprite->setScaleY(0.03f); // ��������y���ϵĴ�С��С��ԭ����50%
		sprite->setPosition(35, 9); //���ÿ��λ��
		this->addChild(sprite);            //�ӵ�Ĭ��ͼ������ȥ
		return true;
	}
	return false;
}

void Monster::unFreezed(float a) {
	_freeze = 0;
}


bool Monster::isDie() {
	if (_hp <= 0)
	{
		isalive = 0;
		//���鱬ը
		auto texture = Director::getInstance()->getTextureCache()->addImage("monster/2.png");
		// �����µ�����  
		this->setTexture(texture);
		//2.�������������ü��
		Animation* animation = Animation::create();
		animation->setDelayPerUnit(0.125 / 2);//������16֡������ʱ��1��
		animation->setRestoreOriginalFrame(true);//����ִ����󷵻ص�һ֡
		//3.���ؾ���֡
		Texture2D* texture1 = Director::getInstance()->getTextureCache()->addImage("monster/8.png");
		for (int i = 0; i <= 1; i++)
		{
			for (int j = 0; j <= 1; j++)
			{
				animation->addSpriteFrameWithTexture(texture1, Rect(125 * j, 125 * i, 150, 125));
			}
		}
		//4.���ж���
		this->runAction(RepeatForever::create(Animate::create(animation)));
		this->schedule(schedule_selector(Monster::deletemonster), 0.125);
		return true;
	}
	else
		return false;
}

void Monster::behurt(float a) {
	_hp = 0;
	if (this->isDie()) {
		//ɾ���þ����㣬��ôд����
	}
}

void Monster::deletemonster(float a) {
	this->removeFromParent();
}

//void Monster::behurt(int monster_blood) {
//	_hp -= monster_blood;
//}