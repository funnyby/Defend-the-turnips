#include "..\Classes\Carrot.h"
#include "SimpleAudioEngine.h"
#include "GameMap1.h"
#include "GameMap2.h"
using namespace CocosDenshion;
USING_NS_CC;
Vector<Carrot*> myCarrot;
extern int game_money1;
/*-----------------public---------------------*/
bool Carrot::initCarrot() {
	myCarrot.pushBack(this);
	if (!initWithFile("Carrot/CarrotStay/Carrot_1.png")) {
		CCLOG("Failed to load carrot image");
		return false;
	}
	this->setHP(10.0);
	bitenDamage = 1;
	scale = 1;
	myGrade = 1;
	_beBiten = false;
	this->createBloodBox();
	this->changeBloodBox();
	isAlive = true;
	//_biten = false;
	//this->setLocation();  //再初始化场景时放置位置。

	 //设置萝卜被咬后的状态
	bitenTectures[0].fileName = "Carrot/CarrotBiten/hlb1_1.png";
	bitenTectures[1].fileName = "Carrot/CarrotBiten/hlb1_2.png";
	bitenTectures[2].fileName = "Carrot/CarrotBiten/hlb1_3.png";
	bitenTectures[3].fileName = "Carrot/CarrotBiten/hlb1_4.png";
	bitenTectures[4].fileName = "Carrot/CarrotBiten/hlb1_5.png";
	bitenTectures[5].fileName = "Carrot/CarrotBiten/hlb1_6.png";
	bitenTectures[6].fileName = "Carrot/CarrotBiten/hlb1_7.png";
	bitenTectures[7].fileName = "Carrot/CarrotBiten/hlb1_8.png";
	bitenTectures[8].fileName = "Carrot/CarrotBiten/hlb1_9.png";
	bitenTectures[9].fileName = "Carrot/CarrotBiten/hlb1_10.png";

	this->runTwistAnimation();
}
void Carrot::setLocation(Point mapDest) {
	CarrotPos = mapDest;
	int myHeight = 50;//carrot's half body height
	CarrotPos.add(Vec2(0, myHeight));
	this->setPosition(CarrotPos);
}

void Carrot::setBitenAttack(float a) {
	bitenDamage = a;
	_beBiten = true;
}

void Carrot::runTwistAnimation() {

	//create animation and set intervals
	Animation* twistAnimation = Animation::create();    //twist animate action
	twistAnimation->setDelayPerUnit(1.5f / 12);//动画共12帧，运行时间3.0秒
	twistAnimation->setRestoreOriginalFrame(false);//动画执行完后不返回第一帧

	//加载精灵帧
	Texture2D* texture1 = Director::getInstance()->getTextureCache()->addImage("Carrot/CarrotTwist/hlb1_10.png");
	twistAnimation->addSpriteFrameWithTexture(texture1, Rect(0, 0, 150 * scale, 168 * scale));
	Texture2D* texture2 = Director::getInstance()->getTextureCache()->addImage("Carrot/CarrotTwist/hlb1_11.png");
	twistAnimation->addSpriteFrameWithTexture(texture2, Rect(0, 0, 150 * scale, 168 * scale));
	Texture2D* texture3 = Director::getInstance()->getTextureCache()->addImage("Carrot/CarrotTwist/hlb1_12.png");
	twistAnimation->addSpriteFrameWithTexture(texture3, Rect(0, 0, 150 * scale, 168 * scale));
	Texture2D* texture4 = Director::getInstance()->getTextureCache()->addImage("Carrot/CarrotTwist/hlb1_13.png");
	twistAnimation->addSpriteFrameWithTexture(texture4, Rect(0, 0, 150 * scale, 168 * scale));
	Texture2D* texture5 = Director::getInstance()->getTextureCache()->addImage("Carrot/CarrotTwist/hlb1_14.png");
	twistAnimation->addSpriteFrameWithTexture(texture5, Rect(0, 0, 150 * scale, 168 * scale));
	Texture2D* texture6 = Director::getInstance()->getTextureCache()->addImage("Carrot/CarrotTwist/hlb1_15.png");
	twistAnimation->addSpriteFrameWithTexture(texture6, Rect(0, 0, 150 * scale, 168 * scale));
	Texture2D* texture7 = Director::getInstance()->getTextureCache()->addImage("Carrot/CarrotTwist/hlb1_16.png");
	twistAnimation->addSpriteFrameWithTexture(texture7, Rect(0, 0, 150 * scale, 168 * scale));
	Texture2D* texture8 = Director::getInstance()->getTextureCache()->addImage("Carrot/CarrotTwist/hlb1_17.png");
	twistAnimation->addSpriteFrameWithTexture(texture8, Rect(0, 0, 150 * scale, 168 * scale));
	Texture2D* texture9 = Director::getInstance()->getTextureCache()->addImage("Carrot/CarrotTwist/hlb1_18.png");
	twistAnimation->addSpriteFrameWithTexture(texture9, Rect(0, 0, 150 * scale, 168 * scale));
	Texture2D* texture10 = Director::getInstance()->getTextureCache()->addImage("Carrot/CarrotTwist/hlb1_19.png");
	twistAnimation->addSpriteFrameWithTexture(texture10, Rect(0, 0, 150 * scale, 168 * scale));
	Texture2D* texture11 = Director::getInstance()->getTextureCache()->addImage("Carrot/CarrotTwist/hlb1_20.png");
	twistAnimation->addSpriteFrameWithTexture(texture11, Rect(0, 0, 150 * scale, 168 * scale));
	Texture2D* texture12 = Director::getInstance()->getTextureCache()->addImage("Carrot/CarrotTwist/hlb1_21.png");
	twistAnimation->addSpriteFrameWithTexture(texture12, Rect(0, 0, 150 * scale, 168 * scale));
	SimpleAudioEngine::getInstance()->playEffect("Music/carrot.mp3");

	this->runAction(Animate::create(twistAnimation));
}

void Carrot::update(float dt) {
	//待修改 
	this->isDie();
	this->changeCarrotAppearance();//显示新的hp对应的萝卜
	this->beBiten();
	if (_hp == 10)
		this->beTouched();
	if (!this->isAlive)
		this->unschedule(schedule_selector(Carrot::update));
}

void Carrot::beBiten() {
	if (_beBiten == true) {
		_hp -= bitenDamage;
		_beBiten = false;
		bitenDamage = 1;
		this->changeBloodBox();//更换血条数字
		this->changeCarrotAppearance();//显示新的hp对应的萝卜
	}

}

void Carrot::beTouched() {
	if (!this->isAlive)
		return;
	// 添加鼠标点击事件监听器 
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = [this](EventMouse* event) {
		// 获取鼠标点击的位置  
		Vec2 location = event->getLocationInView();
		if (this->getBoundingBox().containsPoint(location)) {
			this->runTwistAnimation();
			this->changeCarrotAppearance();//显示新的hp对应的萝卜
			this->upgrade();
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}
/*-----------------private---------------------*/
void Carrot::changeCarrotAppearance() {
	// 在动画完成后执行的逻辑
	if(_hp>0)
		this->setTexture(bitenTectures[int(_hp - 1)].fileName);//according to _hp callback to tecture
}

void Carrot::createBloodBox() {
	CarrotBloodBox = Sprite::create();//create a blood box
	if (!CarrotBloodBox->initWithFile("Carrot/CarrotBlood/carrot_hp_bg.png")) {
		CCLOG("Failed to load carrot image");
		exit(1);
	}
	CarrotBloodBox->setScale(0.8f);//set sprite 0.8f size in x and y
	CarrotBloodBox->setPosition(Vec2(85, 120));//height higher 50 than carrot
	this->addChild(CarrotBloodBox, 20);            //add to picture layer 
	BloodNum = Sprite::create("Carrot/CarrotBlood/number_10.png");  //create blood number_hp10
	BloodNum->setScale(0.5f);
	BloodNum->setPosition(Vec2(72, 120));
	this->addChild(BloodNum, 10000);
}
void Carrot::changeBloodBox() {
	std::string hpFrameName = StringUtils::format("Carrot/CarrotBlood/number_%d.png", static_cast<int>(_hp));
	BloodNum->setTexture(hpFrameName);
}

bool Carrot::isDie() {
	if (_hp <= 0) {
		CarrotBloodBox->removeFromParent();
		BloodNum->removeFromParent();
		getActionManager()->removeAllActionsFromTarget(this);
		isAlive = false;

		//director 跳转场景至gameover
		// 获取场景类的实例  
		GameMap1* sceneInstance = dynamic_cast<GameMap1*>(this->getParent());
		if (sceneInstance) {
			// 调用自定义函数  
			sceneInstance->lose();
		}
		GameMap2* sceneInstance2 = dynamic_cast<GameMap2*>(this->getParent());
		if (sceneInstance2) {
			// 调用自定义函数  
			sceneInstance2->lose();
		}
		return true;
	}
	else
		return false;
}
bool Carrot::upgrade() {
	if (game_money1 >= 550) {
		myGrade += 1;
		if (myGrade > 3){
			myGrade = 3;
			if (_hp < 3){
				_hp = 10;
				this->changeBloodBox();
				this->changeCarrotAppearance();
			}
		}
		else {
			scale = myGrade / 20 + 1;
			this->setScale(scale);
			this->runTwistAnimation();
			game_money1 -= 125;
			for (int j = 0; j < monsterContainer.size(); j++) {
				auto monster = monsterContainer.at(j);
				monster->beHurt(monster->getHP() / (myGrade * 10 - 10), 4);
			}
		}
			return true;
		
	}
	return false;
}