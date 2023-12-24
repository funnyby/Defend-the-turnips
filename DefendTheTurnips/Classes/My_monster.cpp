#include"My_monster.h"

USING_NS_CC;
using namespace cocos2d::ui;

bool choose_a_object = 0;
int blood;
cocos2d::Vector<Monster*> monsterContainer;

void Monster::initmonster_type1() {
	//�ڵ�ͼ��㴦����һ������
	monsterContainer.pushBack(this);
	initWithFile("monster/13.png");

	_walkSpeed =111;
	//_walkSpeed =0.01;
	hp_total = 100;
	_hp = 100;
	_freeze = -1;
	waypoint = 1;
	isalive = 1;

	this->create_Health_bar();
	this->scheduleBlood();
	this->setPosition(170, 485);

	//2.�������������ü��
	Animation*animation = Animation::create();
	animation->setDelayPerUnit(0.3 / 3);//������16֡������ʱ��1��
	animation->setRestoreOriginalFrame(true);//����ִ����󷵻ص�һ֡

	//3.���ؾ���֡
	Texture2D* texture1 = Director::getInstance()->getTextureCache()->addImage("monster/13.png");
	animation->addSpriteFrameWithTexture(texture1, Rect(0, 0, 88, 88));
	Texture2D* texture2 = Director::getInstance()->getTextureCache()->addImage("monster/14.png");
	animation->addSpriteFrameWithTexture(texture2, Rect(0, 0, 88, 88));
	Texture2D* texture3 = Director::getInstance()->getTextureCache()->addImage("monster/15.png");
	animation->addSpriteFrameWithTexture(texture3, Rect(0, 0, 88, 88));

	//4.���ж���
	this->runAction(RepeatForever::create(Animate::create(animation)));

	beginningWaypoint.x = map[0].x;
	beginningWaypoint.y = map[0].y;
	destinationWaypoint.x = map[1].x;
	destinationWaypoint.y = map[1].y;

}

void Monster::initmonster_type2() {
	//�ڵ�ͼ��㴦����һ������
	monsterContainer.pushBack(this);
	initWithFile("monster/F11.png");

	_walkSpeed = 150;
	//_walkSpeed =0.01;
	hp_total = 50;
	_hp = 50;
	_freeze = -1;
	waypoint = 1;
	isalive = 1;

	this->create_Health_bar();
	this->scheduleBlood();
	this->setPosition(170, 485);

	//2.�������������ü��
	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.3 / 3);//������16֡������ʱ��1��
	animation->setRestoreOriginalFrame(true);//����ִ����󷵻ص�һ֡

	//3.���ؾ���֡
	Texture2D* texture1 = Director::getInstance()->getTextureCache()->addImage("monster/F11.png");
	animation->addSpriteFrameWithTexture(texture1, Rect(-5, 0, 100, 100));
	Texture2D* texture2 = Director::getInstance()->getTextureCache()->addImage("monster/F12.png");
	animation->addSpriteFrameWithTexture(texture2, Rect(-5, 0, 100, 100));
	Texture2D* texture3 = Director::getInstance()->getTextureCache()->addImage("monster/F13.png");
	animation->addSpriteFrameWithTexture(texture3, Rect(-5, 0, 100, 100));

	//4.���ж���
	this->runAction(RepeatForever::create(Animate::create(animation)));

	beginningWaypoint.x = map[0].x;
	beginningWaypoint.y = map[0].y;
	destinationWaypoint.x = map[1].x;
	destinationWaypoint.y = map[1].y;

}

void Monster::initmonster_type3() {
	//�ڵ�ͼ��㴦����һ������
	monsterContainer.pushBack(this);
	initWithFile("monster/L11.png");

	_walkSpeed = 80;
	//_walkSpeed =0.01;
	_hp = 200;
	hp_total = 200;
	_freeze = -1;
	waypoint = 1;
	isalive = 1;

	this->create_Health_bar();
	this->scheduleBlood();
	this->setPosition(170, 485);

	//2.�������������ü��
	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.3 / 3);//������16֡������ʱ��1��
	animation->setRestoreOriginalFrame(true);//����ִ����󷵻ص�һ֡

	//3.���ؾ���֡
	Texture2D* texture1 = Director::getInstance()->getTextureCache()->addImage("monster/L11.png");
	animation->addSpriteFrameWithTexture(texture1, Rect(0, 0, 88, 88));
	Texture2D* texture2 = Director::getInstance()->getTextureCache()->addImage("monster/L12.png");
	animation->addSpriteFrameWithTexture(texture2, Rect(0, 0, 88, 88));
	Texture2D* texture3 = Director::getInstance()->getTextureCache()->addImage("monster/L13.png");
	animation->addSpriteFrameWithTexture(texture3, Rect(0, 0, 88, 88));

	//4.���ж���
	this->runAction(RepeatForever::create(Animate::create(animation)));

	beginningWaypoint.x = map[0].x;
	beginningWaypoint.y = map[0].y;
	destinationWaypoint.x = map[1].x;
	destinationWaypoint.y = map[1].y;

}

void Monster::update(float dt) {
	_hp-=1;
	this->isDie();
	this->isFreezed();
	this->scheduleBlood();
	this->walk();
	this->judge_dest();
	this->touched();
	if (!this->isalive)
		this->unschedule(schedule_selector(Monster::update));
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

void Monster::create_Health_bar() {
	bloodbox = Sprite::create("monster/3.png");   //�������ȿ�
	bloodbox->setScaleX(0.1f); // ��������x���ϵĴ�С��С��ԭ����50%  
	bloodbox->setScaleY(0.1f); // ��������y���ϵĴ�С��С��ԭ����50%
	bloodbox->setPosition(42, 90); //���ÿ��λ��
	this->addChild(bloodbox);            //�ӵ�Ĭ��ͼ������ȥ
	auto sprBlood = Sprite::create("monster/4.png");  //����Ѫ��
	ProgressTimer* progress = ProgressTimer::create(sprBlood); //����progress����
	progress->setType(ProgressTimer::Type::BAR);        //���ͣ���״
	progress->setScaleX(0.1f); // ��������x���ϵĴ�С��С��ԭ����50%  
	progress->setScaleY(0.1f); // ��������y���ϵĴ�С��С��ԭ����50%
	progress->setPosition(40, 90);
	//���ҵ������Ѫ��
	progress->setMidpoint(Point(0, 0.5));     //����Ǵ����ҵĻ����ĳ�(1,0.5)����
	progress->setBarChangeRate(Point(1, 0));
	progress->setTag(BLOOD_BAR);       //��һ�����
	this->addChild(progress);
}

void Monster::scheduleBlood() {
	auto progress = (ProgressTimer*)this->getChildByTag(BLOOD_BAR);
	progress->setPercentage(((_hp) / hp_total) * 100);  //�����ǰٷ�����ʾ
}

void Monster::betouched() {
	if (this->choosed == 1|| !this->isalive)
		return;
	choice = Sprite::create("monster/16.png");   //�������ȿ�
	this->addChild(choice);            //�ӵ�Ĭ��ͼ������ȥ
	choice->setPosition(50, 120); //���ÿ��λ��
	//2.�������������ü��
	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.2 / 2);//������16֡������ʱ��1��
	animation->setRestoreOriginalFrame(true);//����ִ����󷵻ص�һ֡
	//3.���ؾ���֡
	Texture2D* texture1 = Director::getInstance()->getTextureCache()->addImage("monster/16.png");
	animation->addSpriteFrameWithTexture(texture1, Rect(0, 0, 34, 43));
	Texture2D* texture2 = Director::getInstance()->getTextureCache()->addImage("monster/17.png");
	animation->addSpriteFrameWithTexture(texture2, Rect(0, 0, 34, 43));
	//4.���ж���
	choice->runAction(RepeatForever::create(Animate::create(animation)));
}

void Monster::touched() {
	if (!this->isalive)
		return;
	// ���������¼�������  
	auto listener = EventListenerMouse::create();
	this->setTag(_spriteIndex);
	listener->onMouseDown = [this](EventMouse* event) {
		// ��ȡ�������λ��  
		Vec2 location= event->getLocationInView();

		if (this->getBoundingBox().containsPoint(location)) {
			if(choose_a_object == 0)
			{
				if(this->choosed == 0)
				this->betouched();
				choose_a_object = 1;
				this->choosed = 1;
			}
			else {
				for (auto monster : monsterContainer) {
					if (monster->choosed == 1) {
						monster->choosed = 0;
						if (monster->choice != nullptr)
						{
							monster->choice->removeFromParent();
						}
					}
				}
				this->betouched();
				this->choosed = 1;
				choose_a_object = 1;
			}
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

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
		if(this->choosed==1&& this->choice != nullptr)
		{
			//getActionManager()->removeAllActionsFromTarget(choice);
			//choice->removeFromParent();
		}
		bloodbox->removeFromParent();
		getActionManager()->removeAllActionsFromTarget(this);
		isalive = 0;
		//���鱬ը
		auto texture = Director::getInstance()->getTextureCache()->addImage("monster/2.png");
		// �����µ�����  
		this->setTexture(texture);
		//2.�������������ü��
		Animation* animation = Animation::create();
		animation->setDelayPerUnit(0.4 / 6);//������16֡������ʱ��1��
		animation->setRestoreOriginalFrame(true);//����ִ����󷵻ص�һ֡
		//3.���ؾ���֡
		Texture2D* texture1 = Director::getInstance()->getTextureCache()->addImage("monster/6.png");
		animation->addSpriteFrameWithTexture(texture1, Rect(0,0,100,100));
		Texture2D* texture2 = Director::getInstance()->getTextureCache()->addImage("monster/8.png");
		animation->addSpriteFrameWithTexture(texture2, Rect(0, 0, 100, 100));
		Texture2D* texture3 = Director::getInstance()->getTextureCache()->addImage("monster/9.png");
		animation->addSpriteFrameWithTexture(texture3, Rect(0, 0, 100, 100));
		Texture2D* texture4 = Director::getInstance()->getTextureCache()->addImage("monster/10.png");
		animation->addSpriteFrameWithTexture(texture4, Rect(0, 0, 100, 100));
		Texture2D* texture5 = Director::getInstance()->getTextureCache()->addImage("monster/11.png");
		animation->addSpriteFrameWithTexture(texture5, Rect(0, 0, 100, 100));
		Texture2D* texture6 = Director::getInstance()->getTextureCache()->addImage("monster/12.png");
		animation->addSpriteFrameWithTexture(texture6, Rect(0, 0, 100, 100));
		//4.���ж���
		this->runAction(RepeatForever::create(Animate::create(animation)));
		this->schedule(schedule_selector(Monster::deletemonster), 0.4);
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