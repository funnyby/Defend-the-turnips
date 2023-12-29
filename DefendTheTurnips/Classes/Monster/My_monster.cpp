#include"My_monster.h"

USING_NS_CC;
using namespace cocos2d::ui;

bool choose_a_object = 0;
int blood;
extern int game_money;//��Ǯ
extern int monsternum;
extern int die_monsternum;

cocos2d::Vector<Monster*> monsterContainer;

void Monster::initmonster_type1() {
	//�ڵ�ͼ��㴦����һ������
	monsterContainer.pushBack(this);
	initWithFile("monster/13.png");



	behit = Sprite::create();
	behit->setPosition(60, 24); //���ÿ��λ��
	behit->setVisible(false); // ����Ϊ�ɼ�  
	this->addChild(behit);            //�ӵ�Ĭ��ͼ������ȥ

	freeze_total = 88;
	_walkSpeed = 88;
	//_walkSpeed =0.01;
	hp_total = 100;
	_hp = 100;
	_freeze = -10;
	waypoint = 1;
	isalive = 1;

	this->setMoney(15.0f);
	this->create_Health_bar();
	this->scheduleBlood();
	this->setPosition(170, 485);

	//2.�������������ü��
	Animation* animation = Animation::create();
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

	beginningWaypoint.x = Path[0].x;
	beginningWaypoint.y = Path[0].y;
	destinationWaypoint.x = Path[1].x;
	destinationWaypoint.y = Path[1].y;

}

void Monster::initmonster_type2() {
	//�ڵ�ͼ��㴦����һ������
	monsterContainer.pushBack(this);
	initWithFile("monster/F11.png");

	freeze_total = 137;
	_walkSpeed = 137;
	//_walkSpeed =0.01;
	hp_total = 50;
	_hp = 50;
	_freeze = -1;
	waypoint = 1;
	isalive = 1;

	this->setMoney(16.5f);
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

	beginningWaypoint.x = Path[0].x;
	beginningWaypoint.y = Path[0].y;
	destinationWaypoint.x = Path[1].x;
	destinationWaypoint.y = Path[1].y;

}

void Monster::initmonster_type3() {
	//�ڵ�ͼ��㴦����һ������
	monsterContainer.pushBack(this);
	initWithFile("monster/L11.png");

	freeze_total = 48;
	_walkSpeed = 48;
	//_walkSpeed =0.01;
	_hp = 200;
	hp_total = 200;
	_freeze = -1;
	waypoint = 1;
	isalive = 1;

	this->setMoney(14.5f);
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

	beginningWaypoint.x = Path[0].x;
	beginningWaypoint.y = Path[0].y;
	destinationWaypoint.x = Path[1].x;
	destinationWaypoint.y = Path[1].y;

}

void Monster::update(float dt) {
	this->isDie();
	this->isFreezed();
	this->scheduleBlood();
	this->walk();
	this->judge_dest();
	this->touched();
	this->BiteTurnips();
	if (!this->isalive)
		this->unschedule(schedule_selector(Monster::update));
}

void Monster::BiteTurnips() {
	Vec2 location;
	location.x = Path[6].x - 10;
	location.y = Path[6].y;
	if (this->getBoundingBox().containsPoint(location)) {
		_hp = -6;
		this->isDie();
		//�����ܲ���ҧ�ĺ���
	}
}


bool Monster::judge_dest() {
	Vec2 pos = this->getPosition();
	if ((destinationWaypoint.x - pos.x) * (destinationWaypoint.x - pos.x) + (destinationWaypoint.y - pos.y) * (destinationWaypoint.y - pos.y) <= 666)
	{
		waypoint++;
		if (waypoint == 6)
		{
			for (auto Carrot : myCarrot) {
				Carrot->set_beBiten(true);
			}
			//myCarrot[0]->set_beBiten(true);
			this->_hp = 0;
			this->isDie();
			return true;
		}
		beginningWaypoint.x = destinationWaypoint.x;
		beginningWaypoint.y = destinationWaypoint.y;
		destinationWaypoint.x = Path[waypoint].x;
		destinationWaypoint.y = Path[waypoint].y;
		return true;
	}
	else
		return false;
}

void Monster::walk() {
	Vec2 pos = this->getPosition();
	float path = Path[waypoint].path;
	float x = _walkSpeed * 0.1f * (destinationWaypoint.x - beginningWaypoint.x) / path + pos.x;
	float y = _walkSpeed * 0.1f * (destinationWaypoint.y - beginningWaypoint.y) / path + pos.y;
	MoveTo* moveto = MoveTo::create(0.1f, Point(x, y));
	this->runAction(moveto);
}

void Monster::create_Health_bar() {
	bloodbox = Sprite::create("monster/3.png");   //�������ȿ�
	bloodbox->setScaleX(0.1f); // ��������x���ϵĴ�С��С��ԭ����50%  
	bloodbox->setScaleY(0.1f); // ��������y���ϵĴ�С��С��ԭ����50%
	bloodbox->setPosition(42, 90); //���ÿ��λ��
	this->addChild(bloodbox);            //�ӵ�Ĭ��ͼ������ȥ
	sprBlood = Sprite::create("monster/4.png");  //����Ѫ��
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
	if (this->choosed == 1 || !this->isalive)
		return;
	choice = Sprite::create("monster/16.png");   //�������ȿ�
	this->addChild(choice, 10000);            //�ӵ�Ĭ��ͼ������ȥ
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
	// ���������¼�������  
	auto listener = EventListenerMouse::create();
	this->setTag(_spriteIndex);
	listener->onMouseDown = [this](EventMouse* event) {
		// ��ȡ�������λ��  
		Vec2 location = event->getLocationInView();

		if (this->getBoundingBox().containsPoint(location)) {
			if (choose_a_object == 0)
			{
				if (this->choosed == 0)
					this->betouched();
				choose_a_object = 1;
				this->choosed = 1;
			}
			else {
				for (auto monster : BarrierContainer) {
					if (monster->choosed == 1) {
						monster->choosed = 0;
						if (monster->choice != nullptr)
						{
							monster->choice->removeFromParent();
						}
					}
				}
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
	if (!this->isalive)
	{
		_eventDispatcher->removeEventListener(listener);
		return;
	}
}


bool Monster::isFreezed() {
	if (_freeze == 1) {
		_walkSpeed = 0.5 * freeze_total;;
		this->schedule(schedule_selector(Monster::unFreezed), 3);
		auto sprite = Sprite::create("monster/5.png");   //�������ȿ�
		sprite->setScaleX(0.03f); // ��������x���ϵĴ�С��С��ԭ����50%  
		sprite->setScaleY(0.03f); // ��������y���ϵĴ�С��С��ԭ����50%
		sprite->setPosition(45, 9); //���ÿ��λ��
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
		if (this->choosed == 1 && this->choice != nullptr)
		{
			getActionManager()->removeAllActionsFromTarget(choice);
			choice->removeFromParent();
			choose_a_object = 0;
		}
		bloodbox->removeFromParent();
		getActionManager()->removeAllActionsFromTarget(this);
		sprBlood->removeFromParent();
		auto progress = (ProgressTimer*)this->getChildByTag(BLOOD_BAR);
		progress->removeFromParent();
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
		animation->addSpriteFrameWithTexture(texture1, Rect(0, 0, 100, 100));
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
		die_monsternum++;
		game_money += this->getMoney();
		return true;
	}
	else
		return false;
}


void Monster::deletemonster(float a) {
	this->removeFromParent();
}

void Monster::behurt(int monster_blood, int type) {
	_hp -= monster_blood;
	behit->setVisible(true); // ����Ϊ�ɼ�  
	if (type == 1)
	{
		auto texture = Director::getInstance()->getTextureCache()->addImage("monster/behit1.png");
		// �����µ�����  
		behit->setTexture(texture);
		//2.�������������ü��
		Animation* animation = Animation::create();
		animation->setDelayPerUnit(0.2 / 2);//������16֡������ʱ��1��
		animation->setRestoreOriginalFrame(true);//����ִ����󷵻ص�һ֡
		//3.���ؾ���֡
		Texture2D* texture1 = Director::getInstance()->getTextureCache()->addImage("monster/behit1.png");
		animation->addSpriteFrameWithTexture(texture1, Rect(0, 0, 100, 100));
		Texture2D* texture2 = Director::getInstance()->getTextureCache()->addImage("monster/7.png");
		animation->addSpriteFrameWithTexture(texture2, Rect(0, 0, 100, 100));
		//4.���ж���
		behit->runAction(RepeatForever::create(Animate::create(animation)));
	}
	schedule(schedule_selector(Monster::deletebehit), 0.4);
}

void Monster::deletebehit(float a) {
	behit->setVisible(false);
}

