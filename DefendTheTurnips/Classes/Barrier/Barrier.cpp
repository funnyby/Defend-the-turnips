#include"Barrier.h"

USING_NS_CC;
using namespace cocos2d::ui;

extern int game_money1;
cocos2d::Vector<Barrier*> BarrierContainer;

void Barrier::initBarrier(int hp, int money, Texture2D* texture, Vec2 pos) {
	//在地图起点处放置一个怪物
	BarrierContainer.pushBack(this);
	initWithTexture(texture);

	hp_total = hp;
	_money = money;
	this->setPosition(pos);

	behit = Sprite::create();
	behit->setPosition(60, 10); //设置框的位置
	behit->setVisible(false); // 设置为可见  
	this->addChild(behit);            //加到默认图层里面去

	//hp_total = 100;
	_hp = hp_total;
	isalive = 1;

	this->create_Health_bar();
	this->scheduleBlood();
	this->schedule(schedule_selector(Barrier::update), 0.4f);
	//this->setPosition(470, 485);

}

void Barrier::update(float dt) {
	this->isDie();
	this->scheduleBlood();
	this->touched();
	if (!this->isalive)
		this->unschedule(schedule_selector(Barrier::update));
}

void Barrier::create_Health_bar() {
	bloodbox = Sprite::create("monster/3.png");   //创建进度框
	bloodbox->setScaleX(0.1f); // 将精灵在x轴上的大小缩小到原来的50%  
	bloodbox->setScaleY(0.1f); // 将精灵在y轴上的大小缩小到原来的50%
	bloodbox->setPosition(42, 90); //设置框的位置
	this->addChild(bloodbox);            //加到默认图层里面去
	bloodbox->setVisible(false);
	sprBlood = Sprite::create("monster/4.png");  //创建血条
	ProgressTimer* progress = ProgressTimer::create(sprBlood); //创建progress对象
	progress->setType(ProgressTimer::Type::BAR);        //类型：条状
	progress->setScaleX(0.1f); // 将精灵在x轴上的大小缩小到原来的50%  
	progress->setScaleY(0.1f); // 将精灵在y轴上的大小缩小到原来的50%
	progress->setVisible(false);
	progress->setPosition(40, 90);
	//从右到左减少血量
	progress->setMidpoint(Point(0, 0.5));     //如果是从左到右的话，改成(1,0.5)即可
	progress->setBarChangeRate(Point(1, 0));
	progress->setTag(BLOOD_BAR);       //做一个标记
	this->addChild(progress);
}

void Barrier::scheduleBlood() {
	auto progress = (ProgressTimer*)this->getChildByTag(BLOOD_BAR);
	progress->setPercentage(((_hp) / hp_total) * 100);  //这里是百分制显示
}

void Barrier::betouched() {
	if (this->choosed == 1 || !this->isalive)
		return;
	choice = Sprite::create("monster/16.png");   //创建进度框
	this->addChild(choice, 10000);            //加到默认图层里面去
	choice->setPosition(50, 100); //设置框的位置
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

void Barrier::touched() {
	// 添加鼠标点击事件监听器  
	auto listener = EventListenerMouse::create();
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

bool Barrier::isDie() {
	if (_hp <= 0)
	{
		game_money1 += getMoney();
		if (this->choosed == 1 && this->choice != nullptr)
		{
			getActionManager()->removeAllActionsFromTarget(choice);
			this->choice->setVisible(false);
			choose_a_object = 0;
		}
		bloodbox->setVisible(false);
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
		this->schedule(schedule_selector(Barrier::deletemonster), 0.4);
		BarrierContainer.eraseObject(this, 0);
		die_monsternum++;
		return true;
	}
	else
		return false;
}


void Barrier::deletemonster(float a) {
	this->removeFromParent();
}

void Barrier::behurt(int monster_blood, int type) {
	_hp -= monster_blood;
	behit->setVisible(true); // 设置为可见  
	if (this->bloodbox != nullptr)
		bloodbox->setVisible(true);
	auto progress = (ProgressTimer*)this->getChildByTag(BLOOD_BAR);
	progress->setVisible(true);
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
	this->isDie();
	schedule(schedule_selector(Barrier::deletebehit), 0.4);
}

void Barrier::deletebehit(float a) {
	behit->setVisible(false);
}
