#include"My_monster.h"

USING_NS_CC;
using namespace cocos2d::ui;

bool choose_a_object = 0;
int blood;
cocos2d::Vector<Monster*> monsterContainer;

void Monster::initmonster_type1() {
	//在地图起点处放置一个怪物
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

	//2.创建动画，设置间隔
	Animation*animation = Animation::create();
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

	beginningWaypoint.x = map[0].x;
	beginningWaypoint.y = map[0].y;
	destinationWaypoint.x = map[1].x;
	destinationWaypoint.y = map[1].y;

}

void Monster::initmonster_type2() {
	//在地图起点处放置一个怪物
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

	beginningWaypoint.x = map[0].x;
	beginningWaypoint.y = map[0].y;
	destinationWaypoint.x = map[1].x;
	destinationWaypoint.y = map[1].y;

}

void Monster::initmonster_type3() {
	//在地图起点处放置一个怪物
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

//萝卜掉血
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
	bloodbox = Sprite::create("monster/3.png");   //创建进度框
	bloodbox->setScaleX(0.1f); // 将精灵在x轴上的大小缩小到原来的50%  
	bloodbox->setScaleY(0.1f); // 将精灵在y轴上的大小缩小到原来的50%
	bloodbox->setPosition(42, 90); //设置框的位置
	this->addChild(bloodbox);            //加到默认图层里面去
	auto sprBlood = Sprite::create("monster/4.png");  //创建血条
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
	if (this->choosed == 1|| !this->isalive)
		return;
	choice = Sprite::create("monster/16.png");   //创建进度框
	this->addChild(choice);            //加到默认图层里面去
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
	if (!this->isalive)
		return;
	// 添加鼠标点击事件监听器  
	auto listener = EventListenerMouse::create();
	this->setTag(_spriteIndex);
	listener->onMouseDown = [this](EventMouse* event) {
		// 获取鼠标点击的位置  
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
		auto sprite = Sprite::create("monster/5.png");   //创建进度框
		sprite->setScaleX(0.03f); // 将精灵在x轴上的大小缩小到原来的50%  
		sprite->setScaleY(0.03f); // 将精灵在y轴上的大小缩小到原来的50%
		sprite->setPosition(35, 9); //设置框的位置
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
		if(this->choosed==1&& this->choice != nullptr)
		{
			//getActionManager()->removeAllActionsFromTarget(choice);
			//choice->removeFromParent();
		}
		bloodbox->removeFromParent();
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
		//4.运行动画
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
		//删除该精灵结点，怎么写待定
	}
}

void Monster::deletemonster(float a) {
	this->removeFromParent();
}

//void Monster::behurt(int monster_blood) {
//	_hp -= monster_blood;
//}