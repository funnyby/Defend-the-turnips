#include"My_monster.h"

USING_NS_CC;
using namespace cocos2d::ui;

bool choose_a_object = 0;
int blood;
extern int game_money;//金钱
extern int monsternum;
extern int die_monsternum;

cocos2d::Vector<Monster*> monsterContainer;

void Monster::initmonster_type1() {
	//在地图起点处放置一个怪物
	monsterContainer.pushBack(this);
	initWithFile("monster/13.png");



	behit = Sprite::create();
	behit->setPosition(60, 24); //设置框的位置
	behit->setVisible(false); // 设置为可见  
	this->addChild(behit);            //加到默认图层里面去

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

	//2.创建动画，设置间隔
	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.3 / 3);//动画共16帧，运行时间1秒
	animation->setRestoreOriginalFrame(true);//动画执行完后返回第一帧

	//3.加载精灵帧
	Texture2D* texture1 = Director::getInstance()->getTextureCache()->addImage("monster/13.png");
	animation->addSpriteFrameWithTexture(texture1, Rect(0, 0, 88, 88));
	Texture2D* texture2 = Director::getInstance()->getTextureCache()->addImage("monster/14.png");
	animation->addSpriteFrameWithTexture(texture2, Rect(0, 0, 88, 88));
	Texture2D* texture3 = Director::getInstance()->getTextureCache()->addImage("monster/15.png");
	animation->addSpriteFrameWithTexture(texture3, Rect(0, 0, 88, 88));

	//4.运行动画
	this->runAction(RepeatForever::create(Animate::create(animation)));

	beginningWaypoint.x = Path[0].x;
	beginningWaypoint.y = Path[0].y;
	destinationWaypoint.x = Path[1].x;
	destinationWaypoint.y = Path[1].y;

}

void Monster::initmonster_type2() {
	//在地图起点处放置一个怪物
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

	//2.创建动画，设置间隔
	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.3 / 3);//动画共16帧，运行时间1秒
	animation->setRestoreOriginalFrame(true);//动画执行完后返回第一帧

	//3.加载精灵帧
	Texture2D* texture1 = Director::getInstance()->getTextureCache()->addImage("monster/F11.png");
	animation->addSpriteFrameWithTexture(texture1, Rect(-5, 0, 100, 100));
	Texture2D* texture2 = Director::getInstance()->getTextureCache()->addImage("monster/F12.png");
	animation->addSpriteFrameWithTexture(texture2, Rect(-5, 0, 100, 100));
	Texture2D* texture3 = Director::getInstance()->getTextureCache()->addImage("monster/F13.png");
	animation->addSpriteFrameWithTexture(texture3, Rect(-5, 0, 100, 100));

	//4.运行动画
	this->runAction(RepeatForever::create(Animate::create(animation)));

	beginningWaypoint.x = Path[0].x;
	beginningWaypoint.y = Path[0].y;
	destinationWaypoint.x = Path[1].x;
	destinationWaypoint.y = Path[1].y;

}

void Monster::initmonster_type3() {
	//在地图起点处放置一个怪物
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

	//2.创建动画，设置间隔
	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.3 / 3);//动画共16帧，运行时间1秒
	animation->setRestoreOriginalFrame(true);//动画执行完后返回第一帧

	//3.加载精灵帧
	Texture2D* texture1 = Director::getInstance()->getTextureCache()->addImage("monster/L11.png");
	animation->addSpriteFrameWithTexture(texture1, Rect(0, 0, 88, 88));
	Texture2D* texture2 = Director::getInstance()->getTextureCache()->addImage("monster/L12.png");
	animation->addSpriteFrameWithTexture(texture2, Rect(0, 0, 88, 88));
	Texture2D* texture3 = Director::getInstance()->getTextureCache()->addImage("monster/L13.png");
	animation->addSpriteFrameWithTexture(texture3, Rect(0, 0, 88, 88));

	//4.运行动画
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
		//调用萝卜被咬的函数
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
	bloodbox = Sprite::create("monster/3.png");   //创建进度框
	bloodbox->setScaleX(0.1f); // 将精灵在x轴上的大小缩小到原来的50%  
	bloodbox->setScaleY(0.1f); // 将精灵在y轴上的大小缩小到原来的50%
	bloodbox->setPosition(42, 90); //设置框的位置
	this->addChild(bloodbox);            //加到默认图层里面去
	sprBlood = Sprite::create("monster/4.png");  //创建血条
	ProgressTimer* progress = ProgressTimer::create(sprBlood); //创建progress对象
	progress->setType(ProgressTimer::Type::BAR);        //类型：条状
	progress->setScaleX(0.1f); // 将精灵在x轴上的大小缩小到原来的50%  
	progress->setScaleY(0.1f); // 将精灵在y轴上的大小缩小到原来的50%
	progress->setPosition(40, 90);
	//从右到左减少血量
	progress->setMidpoint(Point(0, 0.5));     //如果是从左到右的话，改成(1,0.5)即可
	progress->setBarChangeRate(Point(1, 0));
	progress->setTag(BLOOD_BAR);       //做一个标记
	this->addChild(progress);
}

void Monster::scheduleBlood() {
	auto progress = (ProgressTimer*)this->getChildByTag(BLOOD_BAR);
	progress->setPercentage(((_hp) / hp_total) * 100);  //这里是百分制显示
}

void Monster::betouched() {
	if (this->choosed == 1 || !this->isalive)
		return;
	choice = Sprite::create("monster/16.png");   //创建进度框
	this->addChild(choice, 10000);            //加到默认图层里面去
	choice->setPosition(50, 120); //设置框的位置
	//2.创建动画，设置间隔
	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.2 / 2);//动画共16帧，运行时间1秒
	animation->setRestoreOriginalFrame(true);//动画执行完后返回第一帧
	//3.加载精灵帧
	Texture2D* texture1 = Director::getInstance()->getTextureCache()->addImage("monster/16.png");
	animation->addSpriteFrameWithTexture(texture1, Rect(0, 0, 34, 43));
	Texture2D* texture2 = Director::getInstance()->getTextureCache()->addImage("monster/17.png");
	animation->addSpriteFrameWithTexture(texture2, Rect(0, 0, 34, 43));
	//4.运行动画
	choice->runAction(RepeatForever::create(Animate::create(animation)));
}

void Monster::touched() {
	// 添加鼠标点击事件监听器  
	auto listener = EventListenerMouse::create();
	this->setTag(_spriteIndex);
	listener->onMouseDown = [this](EventMouse* event) {
		// 获取鼠标点击的位置  
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
		auto sprite = Sprite::create("monster/5.png");   //创建进度框
		sprite->setScaleX(0.03f); // 将精灵在x轴上的大小缩小到原来的50%  
		sprite->setScaleY(0.03f); // 将精灵在y轴上的大小缩小到原来的50%
		sprite->setPosition(45, 9); //设置框的位置
		this->addChild(sprite);            //加到默认图层里面去
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
		//精灵爆炸
		auto texture = Director::getInstance()->getTextureCache()->addImage("monster/2.png");
		// 设置新的纹理  
		this->setTexture(texture);
		//2.创建动画，设置间隔
		Animation* animation = Animation::create();
		animation->setDelayPerUnit(0.4 / 6);//动画共16帧，运行时间1秒
		animation->setRestoreOriginalFrame(true);//动画执行完后返回第一帧
		//3.加载精灵帧
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
		//4.运行动画
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
	behit->setVisible(true); // 设置为可见  
	if (type == 1)
	{
		auto texture = Director::getInstance()->getTextureCache()->addImage("monster/behit1.png");
		// 设置新的纹理  
		behit->setTexture(texture);
		//2.创建动画，设置间隔
		Animation* animation = Animation::create();
		animation->setDelayPerUnit(0.2 / 2);//动画共16帧，运行时间1秒
		animation->setRestoreOriginalFrame(true);//动画执行完后返回第一帧
		//3.加载精灵帧
		Texture2D* texture1 = Director::getInstance()->getTextureCache()->addImage("monster/behit1.png");
		animation->addSpriteFrameWithTexture(texture1, Rect(0, 0, 100, 100));
		Texture2D* texture2 = Director::getInstance()->getTextureCache()->addImage("monster/7.png");
		animation->addSpriteFrameWithTexture(texture2, Rect(0, 0, 100, 100));
		//4.运行动画
		behit->runAction(RepeatForever::create(Animate::create(animation)));
	}
	schedule(schedule_selector(Monster::deletebehit), 0.4);
}

void Monster::deletebehit(float a) {
	behit->setVisible(false);
}

