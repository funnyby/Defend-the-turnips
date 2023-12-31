#include "ChooseLevel.h"
#include "MainScene.h"
#include"EnterScene2.h"
#include"GameMap2.h"
#include <string.h>
#include"..\Classes\Monster\My_monster.h"
#include"..\Classes\Tower\Tower.h"
#include"..\Classes\Tower\BottleTower.h"
#include"..\Classes\Tower\ShitTower.h"
#include"..\Classes\Tower\SunTower.h"
#include"..\Classes\Barrier\Barrier.h"
#include "SimpleAudioEngine.h"
#include<vector>

#define i_max 6
#define j_max 12


USING_NS_CC;
using namespace cocos2d::ui;
using namespace CocosDenshion;
//-------------------------------------  全局变量 ------------------------------------------------
extern int monsternum;
extern int die_monsternum;
extern int game_money1;//金钱  

int map1[i_max][j_max] = {
	0,0,3,0,0,0,3,3,3,3,1,0,
	0,1,1,1,1,3,3,3,3,3,1,0,
	3,1,0,3,1,1,1,1,1,0,1,0,
	0,1,0,0,3,3,0,3,1,3,1,0,
	0,1,1,3,0,3,3,0,1,1,1,0,
	0,0,1,1,1,1,1,0,0,3,3,0
};

//----------------------------------------- GameMap2 ------------------------------------------------
cocos2d::Scene* GameMap2::createScene()
{
	return GameMap2::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading:%s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameMap.cpp\n");
}

bool GameMap2::init()
{
	if (!Scene::init())
		return false;
	game_money1 = 550;
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/BackGroundMusic/BGMusic02.mp3");

	// 播放音乐
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/BackGroundMusic/BGMusic02.mp3", true);

	//---------------------------------------设置背景地图-----------------------------------------------
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// 添加背景
	auto background = Sprite::create("GameMap/map2.png");  // 使用你的背景图片文件名
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	// 计算缩放比例，以适应屏幕
	float scaleX = visibleSize.width / background->getContentSize().width;
	float scaleY = visibleSize.height / background->getContentSize().height;
	// 设置精灵的缩放
	background->setScale(scaleX, scaleY);
	this->addChild(background);
	// 怪物桩子
	auto flag = Sprite::create("GameMap/flag.png");  // 使用你的背景图片文件名
	flag->setPosition(620, 120);
	this->addChild(flag, 10);

	//---------------------------------------UI按钮控件栏------------------------------------------------
	auto layerUI = Layer::create();
	this->addChild(layerUI,7);
	auto upPanelPinfo = AutoPolygon::generatePolygon("GameMap/top.png");

	auto upPanel = Sprite::create(upPanelPinfo);
	upPanel->setAnchorPoint(Vec2(0, 1));
	upPanel->setPosition(0, Director::getInstance()->getVisibleSize().height + 330);
	upPanel->setScale(1.05);
	layerUI->addChild(upPanel);

	auto money0 = Sprite::create("GameMap/num.png");  // 使用你的背景图片文件名
	money0->setTextureRect(Rect(0, 0, 27, 28));
	money0->setPosition(200, 603);
	layerUI->addChild(money0);

	shiwei = Sprite::create("GameMap/num.png");  // 使用你的背景图片文件名
	shiwei->setPosition(175, 603);
	layerUI->addChild(shiwei);

	baiwei = Sprite::create("GameMap/num.png");  // 使用你的背景图片文件名
	baiwei->setPosition(150, 603);
	layerUI->addChild(baiwei);

	qianwei = Sprite::create("GameMap/num.png");  // 使用你的背景图片文件名
	qianwei->setPosition(125, 603);
	layerUI->addChild(qianwei);

	this->schedule(schedule_selector(GameMap2::updatemoney), 0.05f);

	setPauseButton(layerUI);

	//倒计时
	countDown();

	//-------------------------------------放置萝卜------------------------------------------------------
	auto CarrotSprite = Carrot::create();
	CarrotSprite->setLocation(Vec2(950, 485));
	this->addChild(CarrotSprite, 100);
	CarrotSprite->initCarrot();
	CarrotSprite->schedule(schedule_selector(Carrot::update), 0.4f);
	//-----------------------------------放置障碍物----------------------------------------------------------
	InitBarrier();

	//-------------------------------------设置点击事件监听----------------------------------------------
	// 设置点击事件监听
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameMap2::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//-----------------------------------怪物波数----------------------------------------------------------
	current_wave = 1;
	monsternum = 0;
	die_monsternum = 0;
	this->scheduleOnce(schedule_selector(GameMap2::bo), 5);

	auto wave_background = Sprite::create("GameMap/waves_bg.png");  // 使用你的背景图片文件名
	wave_background->setPosition(570, 592);
	layerUI->addChild(wave_background);

	auto wave_05 = Sprite::create("GameMap/wave05.png");  // 使用你的背景图片文件名
	wave_05->setPosition(570, 600);
	layerUI->addChild(wave_05);
	scaleX = 0.78;
	scaleY = 0.78;
	// 设置精灵的缩放
	wave_05->setScale(scaleX, scaleY);

	wave = Sprite::create("GameMap/wave_0.png");  // 使用你的背景图片文件名
	wave->setPosition(505, 600);
	layerUI->addChild(wave);

	this->schedule(schedule_selector(Monster::update), 0.05f);
	//this->scheduleOnce(schedule_selector(GameMap2::bo), 5);
	

	return true;
}

void GameMap2::updatemoney(float a) {
	int temp;
	if (game_money1 > 999) {
		qianwei->setVisible(true);
		baiwei->setVisible(true);
		shiwei->setVisible(true);
		temp = game_money1 / 10;
		int j = temp % 10;
		shiwei->setTextureRect(Rect(30 * j, 0, 30, 28));
		temp = temp / 10;
		j = temp % 10;
		baiwei->setTextureRect(Rect(30 * j, 0, 30, 28));
		temp = temp / 10;
		j = temp % 10;
		qianwei->setTextureRect(Rect(30 * j, 0, 30, 28));
		return;
	}
	qianwei->setVisible(false);
	if (game_money1 > 99) {
		baiwei->setVisible(true);
		shiwei->setVisible(true);
		temp = game_money1 / 10;
		int j = temp % 10;
		shiwei->setTextureRect(Rect(30 * j, 0, 30, 28));
		temp = temp / 10;
		j = temp % 10;
		baiwei->setTextureRect(Rect(30 * j, 0, 30, 28));
		return;
	}
	baiwei->setVisible(false);
	if (game_money1 > 9) {
		shiwei->setVisible(true);
		temp = game_money1 / 10;
		shiwei->setTextureRect(Rect(temp * 30, 0, 30, 28));
		return;
	}
	shiwei->setVisible(false);
}

void GameMap2::InitBarrier()
{
	Texture2D* texture41 = Director::getInstance()->getTextureCache()->addImage("Barrier/barrier41.png");
	Texture2D* texture42 = Director::getInstance()->getTextureCache()->addImage("Barrier/barrier42.png");
	Texture2D* texture21 = Director::getInstance()->getTextureCache()->addImage("Barrier/barrier21.png");
	Texture2D* texture11 = Director::getInstance()->getTextureCache()->addImage("Barrier/barrier11.png");
	Texture2D* texture12 = Director::getInstance()->getTextureCache()->addImage("Barrier/barrier12.png");


	auto BarrierSprite13 = Barrier::create();
	this->addChild(BarrierSprite13, 0);
	BarrierSprite13->initBarrier(70, 70, texture12, Vec2(110, 315));
	BarrierSprite13->position[0] = { 2,0 };

	auto BarrierSprite5 = Barrier::create();
	this->addChild(BarrierSprite5, 0);
	BarrierSprite5->initBarrier(70, 70, texture12, Vec2(290, 475));
	BarrierSprite5->position[0] = { 0,2 };

	auto BarrierSprite4 = Barrier::create();
	this->addChild(BarrierSprite4, 0);
	BarrierSprite4->initBarrier(70, 70, texture11, Vec2(370, 315));
	BarrierSprite4->position[0] = { 2,3 };

	auto BarrierSprite6 = Barrier::create();
	this->addChild(BarrierSprite6, 0);
	BarrierSprite6->initBarrier(70, 70, texture11, Vec2(370, 155));//
	BarrierSprite6->position[0] = {4,3 };

	auto BarrierSprite8 = Barrier::create();
	this->addChild(BarrierSprite8, 0);
	BarrierSprite8->initBarrier(70, 70, texture11, Vec2(450, 235));//
	BarrierSprite8->position[0] = { 3,4 };

	auto BarrierSprite7 = Barrier::create();
	this->addChild(BarrierSprite7, 0);
	BarrierSprite7->initBarrier(70, 70, texture11, Vec2(530, 401));//
	BarrierSprite7->position[0] = { 1,5 };

	auto BarrierSprite9 = Barrier::create();
	this->addChild(BarrierSprite9, 0);
	BarrierSprite9->initBarrier(70, 70, texture11, Vec2(530, 235));//
	BarrierSprite9->position[0] = { 3,5 };

	auto BarrierSprite3 = Barrier::create();
	this->addChild(BarrierSprite3, 0);
	BarrierSprite3->initBarrier(150, 150, texture21, Vec2(575, 150));//
	BarrierSprite3->position[0] = {4,5 };
	BarrierSprite3->position[1] = { 4,6 };

	auto BarrierSprite1 = Barrier::create();
	this->addChild(BarrierSprite1, 5);
	BarrierSprite1->initBarrier(300, 300, texture41, Vec2(650, 445));//
	BarrierSprite1->position[0] = { 0,6 };
	BarrierSprite1->position[1] = { 0,7 };
	BarrierSprite1->position[2] = { 1,6 };
	BarrierSprite1->position[3] = { 1,7 };

	auto BarrierSprite12 = Barrier::create();
	this->addChild(BarrierSprite12, 0);
	BarrierSprite12->initBarrier(70, 70, texture12, Vec2(699, 235));//
	BarrierSprite12->position[0] = { 3,7 };

	auto BarrierSprite2 = Barrier::create();
	this->addChild(BarrierSprite2, 0);
	BarrierSprite2->initBarrier(2500, 2500, texture42, Vec2(820, 445));//
	BarrierSprite2->position[0] = { 0,8 };
	BarrierSprite2->position[1] = { 0,9 };
	BarrierSprite2->position[2] = { 1,8 };
	BarrierSprite2->position[3] = { 1,9 };

	auto BarrierSprite10 = Barrier::create();
	this->addChild(BarrierSprite10, 0);
	BarrierSprite10->initBarrier(70, 70, texture12, Vec2(860, 235));//
	BarrierSprite10->position[0] = { 3,9 };

	auto BarrierSprite11 = Barrier::create();
	this->addChild(BarrierSprite11, 0);
	BarrierSprite11->initBarrier(150, 150, texture21, Vec2(900, 65));//
	BarrierSprite2->position[0] = { 5,10 };
	BarrierSprite2->position[1] = { 5,9 };

}

void GameMap2::setMenuButton(Layer* layerUI)
{
	menubtn = Button::create("GameMap/menu.png", "GameMap/menu.png");
	menubtn->setPressedActionEnabled(true);
	menubtn->setPosition(Vec2(975, 590));
	menubtn->setScale(1.05);
	layerUI->addChild(menubtn);

	// 设置按钮点击事件监听器
	menubtn->addClickEventListener([=](Ref* sender) {

		auto gamemenu = Sprite::create("GameMap/gamemenu.png");
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	// 设置菜单位置
	gamemenu->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
		Director::getInstance()->getVisibleSize().height * 2));
	this->addChild(gamemenu, 200);
	// 执行菜单从上方移动到中央的动作
	auto moveAction = EaseBackOut::create(MoveTo::create(0.5f, Vec2(Director::getInstance()->getVisibleSize().width / 2,
		Director::getInstance()->getVisibleSize().height / 2)));
	gamemenu->runAction(moveAction);

	//继续游戏按钮
	auto continuebtn = Button::create("GameMap/continue.png", "GameMap/continue.png", "");
	gamemenu->addChild(continuebtn);
	continuebtn->setPressedActionEnabled(true);
	continuebtn->setPosition(Vec2(233, 310));
	continuebtn->setScale(1.12);
	continuebtn->addClickEventListener([=](Ref* sender) {
		isGamePaused = false;
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	Director::getInstance()->resume();
	gamemenu->removeFromParent();
		});

	//选择关卡按钮
	auto chooselevelbtn = Button::create("GameMap/chooselevel.png", "GameMap/chooselevel.png", "");
	gamemenu->addChild(chooselevelbtn);
	chooselevelbtn->setPressedActionEnabled(true);
	chooselevelbtn->setPosition(Vec2(233, 202));
	chooselevelbtn->setScale(1.12);
	chooselevelbtn->addClickEventListener([=](Ref* sender) {
		auto chooselevel = ChooseLevel::create();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	return false;
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/BackGroundMusic/StartBGMusic.mp3");
	// 播放音乐
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/BackGroundMusic/StartBGMusic.mp3", true);
	Director::getInstance()->replaceScene(chooselevel);
	//?????????????????再次进入会卡住
		});

	//重新开始按钮
	auto restartbtn = Button::create("GameMap/restart.png", "GameMap/restart.png", "");
	gamemenu->addChild(restartbtn);
	restartbtn->setPressedActionEnabled(true);
	restartbtn->setPosition(Vec2(233, 100));
	restartbtn->setScale(1.12);
	restartbtn->addClickEventListener([=](Ref* sender) {
		auto gamemap1 = GameMap2::create();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	Director::getInstance()->replaceScene(gamemap1);
	//?????????????????再次进入会卡住
		});

	// 使用Sequence连接动作和回调函数
	gamemenu->runAction(Sequence::create(moveAction, CallFunc::create([this]() {
		// 在动作执行完后执行的回调函数
		// 游戏暂停
		isGamePaused = true;
	Director::getInstance()->pause();
		}), nullptr));

		});
}
void GameMap2::setPauseButton(Layer* layerUI)
{
	pausebtn = Button::create("GameMap/pause_0.png", "GameMap/pause_0.png");
	pausebtn->setPressedActionEnabled(true);
	pausebtn->setPosition(Vec2(900, 590));
	pausebtn->setScale(1.05);
	layerUI->addChild(pausebtn);

	// 设置按钮点击事件监听器
	pausebtn->addClickEventListener([=](Ref* sender) {
		if (isGamePaused) {
			// 游戏继续
			Director::getInstance()->resume();
			isGamePaused = false;
			pausebtn->loadTextures("GameMap/pause_0.png", "GameMap/pause_0.png");
			SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		}
		else {
			// 游戏暂停
			Director::getInstance()->pause();
			isGamePaused = true;
			pausebtn->loadTextures("GameMap/pause_1.png", "GameMap/pause_1.png");
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		}

		});
}
bool GameMap2::is_out_of_range(int x, int y)
{
	if (x<x_min || x>x_max || y<y_min || y>y_max)
		return true;
	else
		return false;
}

void GameMap2::transform_xy_to_ij(int& i, int& j, const int x, const int y)
{
	j = (x - 80) / 82;
	i = 6 - (y + 40) / 82;
}

void GameMap2::transform_ij_to_xy(const int i, const int j, int& x, int& y)
{
	x = 120 + 82 * j;
	y = -10 + 82 * (6 - i);

}

int GameMap2::getStatus(int x, int y)
{
	int i, j;
	transform_xy_to_ij(i, j, x, y);

	//如果在地图边缘，则不能放置
	if (is_out_of_range(x, y))
		return -1;
	//如果在路径上或者是障碍，则不能被放置
	if (map1[i][j] == PATH)
		return -1;
	//如果位置为空，则可以放置
	if (map1[i][j] == EMPTY)
		return EMPTY;
	//如果位置有炮塔，则可以升级
	if (map1[i][j] == PLACED)
		return PLACED;
	if (map1[i][j] == BARRIER)
		return BARRIER;
	return -1;
}

// 设置bottle按钮点击事件处理函数
void GameMap2::bottlebuttonClickCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type, int i, int j, int placex, int placey)
{
	// 处理按钮点击事件
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		CCLOG("Button Clicked!");
		SimpleAudioEngine::getInstance()->playEffect("Music/TowerMusic/TowerBulid.mp3");
		//扣钱
		if (game_money1 >= 100)
			game_money1 -= 100;
		else
			return;
		map1[i][j] = PLACED;

		// 移除所有按钮
		hideButton();
		// 创建BottleTower
		auto bottletower = BottleTower::create("Tower/Bottle11.png");
		bottletower->pos_i = i;
		bottletower->pos_j = j;
		bottletower->setPosition(Vec2(placex, placey));

		// 将防御塔添加到场景和容器中
		this->addChild(bottletower, 8);
		bottletowers.pushBack(bottletower);
	}
}

// 设置shit按钮点击事件处理函数
void GameMap2::shitbuttonClickCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type, int i, int j, int placex, int placey)
{
	// 处理按钮点击事件
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		CCLOG("Button Clicked!");
		SimpleAudioEngine::getInstance()->playEffect("Music/TowerMusic/TowerBulid.mp3");
		//扣钱
		if (game_money1 >= 120)
			game_money1 -= 120;
		else
			return;
		map1[i][j] = PLACED;

		// 移除所有按钮
		hideButton();
		// 创建ShitTower
		auto shittower = ShitTower::create("Tower/shit1.png");
		shittower->pos_i = i;
		shittower->pos_j = j;
		shittower->setPosition(Vec2(placex, placey));
		shittower->setScale(0.9);

		// 将防御塔添加到场景和容器中
		this->addChild(shittower, 8);
		shittowers.pushBack(shittower);
	}
}

// 设置sun按钮点击事件处理函数
void GameMap2::sunbuttonClickCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type, int i, int j, int placex, int placey)
{
	// 处理按钮点击事件
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		CCLOG("Button Clicked!");
		SimpleAudioEngine::getInstance()->playEffect("Music/TowerMusic/TowerBulid.mp3");
		if (game_money1 >= 180)
			game_money1 -= 180;
		else
			return;
		map1[i][j] = PLACED;

		// 移除所有按钮
		hideButton();

		// 创建SunTower
		auto suntower = SunTower::create("Tower/sun11.png");
		suntower->pos_i = i;
		suntower->pos_j = j;
		suntower->setPosition(Vec2(placex, placey));

		// 将防御塔添加到场景和容器中
		this->addChild(suntower, 8);
		suntowers.pushBack(suntower);
	}
}


//移除button
void GameMap2::hideButton()
{
	if (setTower) {
		setTower->removeFromParent();
		setTower = NULL;
	}
	if (bottlebtn) {
		bottlebtn->removeFromParent();
		bottlebtn = NULL;
	}
	if (shitbtn) {
		shitbtn->removeFromParent();
		shitbtn = NULL;
	}
	if (sunbtn) {
		sunbtn->removeFromParent();
		sunbtn = NULL;
	}
	if (upgradebtn) {
		upgradebtn->removeFromParent();
		upgradebtn = NULL;
	}
	if (cancelbtn) {
		cancelbtn->removeFromParent();
		cancelbtn = NULL;
	}
	if (maxbtn) {
		maxbtn->removeFromParent();
		maxbtn = NULL;
	}
	if (range) {
		float scaleDuration = 0.3f;
		// 显式传递 range，避免在动作期间捕获悬挂指针
		auto rangePtr = range;

		range->runAction(Sequence::create(
			// 缩放动作，从初始大小到 0
			ScaleTo::create(scaleDuration, 0.0f),

			// 隐藏精灵
			Hide::create(),

			// 结束动作序列
			cocos2d::CallFunc::create([rangePtr]() {
				// 在动作结束时，可以执行一些其他操作
				// 例如从场景中移除精灵
				if (rangePtr) {
					rangePtr->removeFromParent();
				}
				}),
			nullptr
					));

		// 为了避免在动作执行期间修改指针，将 range 设置为 nullptr
		range = nullptr;
	}
	selectedPosition = Vec2::ZERO;
}

bool GameMap2::onTouchBegan(Touch* touch, Event* event)
{
	// 获取点击的位置
	int placex, placey;
	Vec2 clickLocation = touch->getLocation();
	int mousex = clickLocation.x;
	int mousey = clickLocation.y;
	int i, j;
	int status = getStatus(mousex, mousey);


	// 如果已经选中了位置，取消选中并隐藏按钮
	if (selectedPosition != Vec2::ZERO) {
		//消除所有按钮和显示
		if (bottlebtn && bottlebtn->getBoundingBox().containsPoint(clickLocation)) {
			// 如果点击到了按钮，则不取消选中，而是处理按钮点击事件
			return true;
		}
		else if (shitbtn && shitbtn->getBoundingBox().containsPoint(clickLocation)) {
			return true;
		}
		else if (sunbtn && sunbtn->getBoundingBox().containsPoint(clickLocation)) {
			return true;
		}
		else if (upgradebtn && upgradebtn->getBoundingBox().containsPoint(clickLocation)) {
			return true;
		}
		else if (cancelbtn && cancelbtn->getBoundingBox().containsPoint(clickLocation)) {
			return true;
		}
		else if (maxbtn && maxbtn->getBoundingBox().containsPoint(clickLocation)) {
			return true;
		}
		else {
			hideButton();
			selectedPosition = Vec2::ZERO;
			return true;
		}
	}

	if (status == -1) {//当前位置不能放置炮塔

		// 创建警告精灵并设置图片
		auto warning = Sprite::create("GameMap/warning.png");
		SimpleAudioEngine::getInstance()->playEffect("Music/SelectFault.mp3");
		warning->setScale(0.8);
		warning->setPosition(clickLocation);

		// 将警告精灵添加到场景
		this->addChild(warning,6);

		// 延迟一定时间后移除精灵
		auto delayAction = DelayTime::create(0.5f); // 延迟0.5秒
		auto removeAction = RemoveSelf::create();
		auto sequence = Sequence::create(delayAction, removeAction, nullptr);

		warning->runAction(sequence);
		return true;
	}
	else if (status == EMPTY) {//当前位置可以放置炮塔

		transform_xy_to_ij(i, j, mousex, mousey);
		transform_ij_to_xy(i, j, placex, placey);

		//显示添加炮塔的图片框
		setTower = Sprite::create("GameMap/select_01.png");
		setTower->setPosition(Vec2(120 + 82 * j, -10 + 82 * (6 - i)));
		this->addChild(setTower, 5);
		selectedPosition = clickLocation;

		//-------------------------------------------------------------------------
		// todo：在下方出现创建炮塔的按钮，有钱创建，没钱创建

		if (/*money_is_enough*/1) {
			// 创建按钮
			bottlebtn = Button::create("Tower/Bottle01.png", "Tower/Bottle01.png", "");
			bottlebtn->setPosition(Vec2(placex - 70, placey - 70));
			bottlebtn->setScale(0.8);
			bottlebtn->addTouchEventListener(CC_CALLBACK_2(GameMap2::bottlebuttonClickCallback, this, i, j, placex, placey));
			this->addChild(bottlebtn, 10);

			shitbtn = Button::create("Tower/shit01.png", "Tower/shit01.png", "");
			shitbtn->setPosition(Vec2(placex + 70, placey - 70));
			shitbtn->setScale(0.7);
			shitbtn->addTouchEventListener(CC_CALLBACK_2(GameMap2::shitbuttonClickCallback, this, i, j, placex, placey));
			this->addChild(shitbtn, 10);

			sunbtn = Button::create("Tower/sun01.png", "Tower/sun01.png", "");
			sunbtn->setPosition(Vec2(placex , placey - 70));
			sunbtn->setScale(0.75);
			sunbtn->addTouchEventListener(CC_CALLBACK_2(GameMap2::sunbuttonClickCallback, this, i, j, placex, placey));
			this->addChild(sunbtn, 10);

		}
		else {

			//------------------todo:----------------------------------------
			// 创建按钮
			bottlebtn = Button::create("Tower/Bottle00.png", "Tower/Bottle00.png", "");
			bottlebtn->setScale(0.8);
			bottlebtn->setPosition(Vec2(placex - 40, placey - 70));
			this->addChild(bottlebtn, 10);
		}
	}
	else {//当前位置有炮塔用来升级

		transform_xy_to_ij(i, j, mousex, mousey);
		selectedPosition = clickLocation;

		BottleTower* bt = NULL;//找到（i，j）位置的bottletower，找不到就是NULL
		for (auto tower : bottletowers) {
			if (tower->pos_i == i && tower->pos_j == j) {
				bt = tower;
				break;
			}
		}

		ShitTower* st = NULL;//找到（i，j）位置的shittower，找不到就是NULL
		for (auto tower : shittowers) {
			if (tower->pos_i == i && tower->pos_j == j) {
				st = tower;
				break;
			}
		}

		SunTower* sunt = NULL;//找到（i，j）位置的suntower，找不到就是NULL
		for (auto tower : suntowers) {
			if (tower->pos_i == i && tower->pos_j == j) {
				sunt = tower;
				break;
			}
		}

		if (bt != NULL)
			upgradeBottle(bt);
		if (st != NULL)
			upgradeShit(st);
		if (sunt != NULL)
			upgradeSun(sunt);
		//---------------todo:升级----------------------
	}
	return true;
}
//升级按钮的回调函数
void GameMap2::upgradebuttonClickCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type, const std::string& towerImage, BottleTower* bt, ShitTower* st, SunTower* sunt)
{
	// 处理按钮点击事件
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		CCLOG("Button Clicked!");
		SimpleAudioEngine::getInstance()->playEffect("Music/ToerMusic/TowerUpdata.mp3");
		if (bt) {
			if (bt->level == 1)
			{
				//扣钱
				if (game_money1 >= 180)
					game_money1 -= 180;
				else
					return;
			}
			else if (bt->level == 2)
			{
				//扣钱
				if (game_money1 >= 260)
					game_money1 -= 260;
				else
					return;
			}
			//更新等级
			bt->level++;
			//升级换图片
			bt->setTexture(towerImage);
			// 移除所有按钮
			hideButton();
			return;
		}
		if (st) {
			if (st->level == 1)
			{
				//扣钱
				if (game_money1 >= 220)
					game_money1 -= 220;
				else
					return;
			}
			else if (st->level == 2)
			{
				//扣钱
				if (game_money1 >= 260)
					game_money1 -= 260;
				else
					return;
			}
			//更新等级
			st->level++;
			//升级换图片
			st->setTexture(towerImage);
			st->setScale(0.9);
			// 移除所有按钮
			hideButton();
			return;
		}
		if (sunt) {
			if (sunt->level == 1)
			{
				//扣钱
				if (game_money1 >= 260)
					game_money1 -= 260;
				else
					return;
			}
			else if (sunt->level == 2)
			{
				//扣钱
				if (game_money1 >= 320)
					game_money1 -= 320;
				else
					return;
			}
			//更新等级
			sunt->level++;
			//升级换图片
			sunt->setTexture(towerImage);
			// 移除所有按钮
			hideButton();
			return;
		}
	}
}

//拆除按钮的回调函数
void GameMap2::cancelbuttonClickCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type, BottleTower* bt, ShitTower* st, SunTower* sunt)
{
	// 处理按钮点击事件
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		CCLOG("Button Clicked!");

		//拆除bottle
		if (bt) {
			map1[bt->pos_i][bt->pos_j] = EMPTY;
			if (bt->level == 1)
				game_money1 += 80;
			else if (bt->level == 2)
				game_money1 += 224;
			else if (bt->level == 3)
				game_money1 += 432;
			bt->removeFromParent();
			auto it = bottletowers.begin();
			while (it != bottletowers.end()) {
				if (*it == bt) {//找到当前炮塔
					delete* it;  // 如果需要手动释放内存
					it = bottletowers.erase(it);  // 从 vector 中删除元素
				}
				else
					++it;
			}
			// 移除所有按钮
			hideButton();
			return;
		}
		//拆除shit
		if (st) {
			map1[st->pos_i][st->pos_j] = EMPTY;
			if (st->level == 1)
				game_money1 += 96;
			else if (st->level == 2)
				game_money1 += 272;
			else if (st->level == 3)
				game_money1 += 480;
			st->removeFromParent();
			auto it = shittowers.begin();
			while (it != shittowers.end()) {
				if (*it == st) {//找到当前炮塔
					delete* it;  // 如果需要手动释放内存
					it = shittowers.erase(it);  // 从 vector 中删除元素
				}
				else
					++it;
			}
			// 移除所有按钮
			hideButton();
			return;
		}
		//拆除sun
		if (sunt) {
			map1[sunt->pos_i][sunt->pos_j] = EMPTY;
			if (sunt->level == 1)
				game_money1 += 144;
			else if (sunt->level == 2)
				game_money1 += 352;
			else if (sunt->level == 3)
				game_money1 += 608;
			sunt->removeFromParent();
			auto it = suntowers.begin();
			while (it != suntowers.end()) {
				if (*it == sunt) {//找到当前炮塔
					delete* it;  // 如果需要手动释放内存
					it = suntowers.erase(it);  // 从 vector 中删除元素
				}
				else
					++it;
			}
			// 移除所有按钮
			hideButton();
			return;
		}
	}
}


void GameMap2::upgradeBottle(BottleTower* bt)
{
	ShitTower* emptyshit = NULL;
	SunTower* emptysun = NULL;
	int pos_x, pos_y;
	transform_ij_to_xy(bt->pos_i, bt->pos_j, pos_x, pos_y);
	float scale1 = 0.4;
	float scale2 = 0.5;
	float scale3 = 0.65;

	/*一级炮塔升级*/
	if (bt->level == 1) {

		//放置范围灰色圈
		setRange(scale1, pos_x, pos_y);

		//放置升级和删除的按钮
		std::string upgradebtnImage = "Tower/upgradebottle1.png";
		std::string towerImage = "Tower/Bottle21.png";
		std::string cancelbtnImage = "Tower/cancelbottle1.png";

		setUpgradeButton(upgradebtnImage, towerImage, pos_x, pos_y, 1, bt, emptyshit,emptysun);
		setCancelButton(cancelbtnImage, pos_x, pos_y, bt, emptyshit, emptysun);

	}
	/*二级炮塔升级*/
	else if (bt->level == 2) {

		//放置范围灰色圈
		setRange(scale2, pos_x, pos_y);

		//放置升级和删除的按钮
		std::string upgradebtnImage = "Tower/upgradebottle2.png";
		std::string towerImage = "Tower/Bottle31.png";
		std::string cancelbtnImage = "Tower/cancelbottle2.png";

		setUpgradeButton(upgradebtnImage, towerImage, pos_x, pos_y, 1, bt, emptyshit, emptysun);
		setCancelButton(cancelbtnImage, pos_x, pos_y, bt, emptyshit, emptysun);

	}
	/*三级炮塔升级（不能升只能拆）*/
	else {

		std::string cancelbtnImage = "Tower/cancelbottle3.png";
		//放置范围灰色圈
		setRange(scale3, pos_x, pos_y);

		//放置max和删除的按钮
		maxbtn = Button::create("Tower/max.png", "Tower/max.png", "");
		maxbtn->setPosition(Vec2(pos_x, pos_y + 70));
		maxbtn->setScale(0.8);
		this->addChild(maxbtn, 10);

		setCancelButton(cancelbtnImage, pos_x, pos_y, bt, emptyshit, emptysun);
	}
}

void GameMap2::upgradeShit(ShitTower* st)
{
	BottleTower* emptybottle = NULL;
	SunTower* emptysun = NULL;
	int pos_x, pos_y;
	transform_ij_to_xy(st->pos_i, st->pos_j, pos_x, pos_y);
	float scale1 = 0.4;
	float scale2 = 0.5;
	float scale3 = 0.65;

	/*一级炮塔升级*/
	if (st->level == 1) {

		//放置范围灰色圈
		setRange(scale1, pos_x, pos_y);

		//放置升级和删除的按钮
		std::string upgradebtnImage = "Tower/upgradeshit1.png";
		std::string towerImage = "Tower/shit2.png";
		std::string cancelbtnImage = "Tower/cancelshit1.png";

		setUpgradeButton(upgradebtnImage, towerImage, pos_x, pos_y, 1, emptybottle, st, emptysun);
		setCancelButton(cancelbtnImage, pos_x, pos_y, emptybottle, st, emptysun);

	}
	/*二级炮塔升级*/
	else if (st->level == 2) {

		//放置范围灰色圈
		setRange(scale2, pos_x, pos_y);

		//放置升级和删除的按钮
		std::string upgradebtnImage = "Tower/upgradeshit2.png";
		std::string towerImage = "Tower/shit3.png";
		std::string cancelbtnImage = "Tower/cancelshit2.png";

		setUpgradeButton(upgradebtnImage, towerImage, pos_x, pos_y, 1, emptybottle, st, emptysun);
		setCancelButton(cancelbtnImage, pos_x, pos_y, emptybottle, st, emptysun);

	}
	/*三级炮塔升级（不能升只能拆）*/
	else {

		std::string cancelbtnImage = "Tower/cancelshit3.png";
		//放置范围灰色圈
		setRange(scale3, pos_x, pos_y);

		//放置max和删除的按钮
		maxbtn = Button::create("Tower/max.png", "Tower/max.png", "");
		maxbtn->setPosition(Vec2(pos_x, pos_y + 70));
		maxbtn->setScale(0.8);
		this->addChild(maxbtn, 10);

		setCancelButton(cancelbtnImage, pos_x, pos_y, emptybottle, st, emptysun);
	}
}

void GameMap2::upgradeSun(SunTower* sunt)
{
	BottleTower* emptybottle = NULL;
	ShitTower* emptyshit = NULL;
	int pos_x, pos_y;
	transform_ij_to_xy(sunt->pos_i, sunt->pos_j, pos_x, pos_y);
	float scale1 = 0.4;
	float scale2 = 0.5;
	float scale3 = 0.65;

	/*一级炮塔升级*/
	if (sunt->level == 1) {

		//放置范围灰色圈
		setRange(scale1, pos_x, pos_y);

		//放置升级和删除的按钮
		std::string upgradebtnImage = "Tower/upgradesun1.png";
		std::string towerImage = "Tower/sun22.png";
		std::string cancelbtnImage = "Tower/cancelsun1.png";

		setUpgradeButton(upgradebtnImage, towerImage, pos_x, pos_y, 1, emptybottle,emptyshit, sunt);
		setCancelButton(cancelbtnImage, pos_x, pos_y, emptybottle, emptyshit, sunt);

	}
	/*二级炮塔升级*/
	else if (sunt->level == 2) {

		//放置范围灰色圈
		setRange(scale2, pos_x, pos_y);

		//放置升级和删除的按钮
		std::string upgradebtnImage = "Tower/upgradesun2.png";
		std::string towerImage = "Tower/sun33.png";
		std::string cancelbtnImage = "Tower/cancelsun2.png";

		setUpgradeButton(upgradebtnImage, towerImage, pos_x, pos_y, 1, emptybottle, emptyshit, sunt);
		setCancelButton(cancelbtnImage, pos_x, pos_y, emptybottle, emptyshit, sunt);

	}
	/*三级炮塔升级（不能升只能拆）*/
	else {

		std::string cancelbtnImage = "Tower/cancelsun3.png";
		//放置范围灰色圈
		setRange(scale3, pos_x, pos_y);

		//放置max和删除的按钮
		maxbtn = Button::create("Tower/max.png", "Tower/max.png", "");
		maxbtn->setPosition(Vec2(pos_x, pos_y + 70));
		maxbtn->setScale(0.8);
		this->addChild(maxbtn, 10);

		setCancelButton(cancelbtnImage, pos_x, pos_y, emptybottle, emptyshit, sunt);
	}
}


void GameMap2::setUpgradeButton(const std::string& btnImage, const std::string& towerImage, int pos_x, int pos_y, bool can_be_clicked, BottleTower* bt, ShitTower* st,SunTower*sunt)
{
	upgradebtn = Button::create(btnImage, btnImage, "");
	upgradebtn->setPosition(Vec2(pos_x, pos_y + 70));
	upgradebtn->setScale(0.8);
	if (can_be_clicked)
		upgradebtn->addTouchEventListener(CC_CALLBACK_2(GameMap2::upgradebuttonClickCallback, this, towerImage, bt, st,sunt));
	this->addChild(upgradebtn, 10);
}

void GameMap2::setRange(float scale, int pos_x, int pos_y)
{
	range = Sprite::create("Tower/range.png");
	range->setPosition(Vec2(pos_x, pos_y));
	range->setScale(scale);
	this->addChild(range);
}

void GameMap2::setCancelButton(const std::string& btnImage, int pos_x, int pos_y, BottleTower* bt, ShitTower* st, SunTower* sunt)
{
	cancelbtn = Button::create(btnImage, btnImage, "");
	cancelbtn->setPosition(Vec2(pos_x, pos_y - 70));
	cancelbtn->setScale(0.8);
	cancelbtn->addTouchEventListener(CC_CALLBACK_2(GameMap2::cancelbuttonClickCallback, this, bt, st,sunt));
	this->addChild(cancelbtn, 10);
}

//倒计时
void GameMap2::countDown()
{
	//获取屏幕大小
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//倒计时的时候游戏是暂停的
	//if_pause = 1;
	//倒计时页
	auto time_layer = Layer::create();
	this->addChild(time_layer,50);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch* touch, Event* event) {
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, time_layer);

	//倒计时背景盘
	auto timepanel = Sprite::create("GameMap/timepanel.png");
	timepanel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	time_layer->addChild(timepanel);

	//倒计时数字
	auto number = Sprite::create("GameMap/time3.png");
	number->setPosition(Vec2(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height / 2 + 10));
	time_layer->addChild(number);

	//倒计时转圈
	auto circle = Sprite::create("GameMap/timecircle.png");
	circle->setPosition(Vec2(visibleSize.width / 2 + 2, +visibleSize.height / 2));
	circle->setAnchorPoint(Vec2(1, 0.5));
	circle->setScale(0.95);
	time_layer->addChild(circle);
	circle->runAction(Sequence::create(Repeat::create(RotateBy::create(1, -360), 3), FadeOut::create(0.1), nullptr));
	timepanel->runAction(Sequence::create(DelayTime::create(4), FadeOut::create(0.1), nullptr));

	//利用帧动画完成数字的倒计时
	Vector<SpriteFrame*> frame;
	frame.pushBack(SpriteFrame::create("GameMap/time3.png", Rect(0, 0, 95, 114)));
	frame.pushBack(SpriteFrame::create("GameMap/time2.png", Rect(0, 0, 95, 114)));
	frame.pushBack(SpriteFrame::create("GameMap/time1.png", Rect(0, 0, 95, 114)));
	frame.pushBack(SpriteFrame::create("GameMap/timego.png", Rect(0, 0, 210, 114)));
	number->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 1)), FadeOut::create(0.1), nullptr));


	//三秒后把遮罩层删除
	auto start_call_back = CallFunc::create([=]() {
		this->removeChild(time_layer);
		});
	time_layer->runAction(Sequence::create(DelayTime::create(4.1), start_call_back, nullptr));

	//if_pause = 0;
}

//

void GameMap2::init_m1(float delta) {
	auto monsterSprite = Monster::create();
	this->addChild(monsterSprite, 100 - monsternum);
	(monsterSprite->map_num) = 2;
	monsterSprite->initmonster_type1();
	monsterSprite->schedule(schedule_selector(Monster::update), 0.05f);
	monsternum++;
	monsterSprite->setPosition(620, 80);
}

void GameMap2::init_m2(float delta) {
	auto monsterSprite = Monster::create();
	this->addChild(monsterSprite, 100 - monsternum);
	(monsterSprite->map_num) = 2;
	monsterSprite->initmonster_type2();
	monsterSprite->schedule(schedule_selector(Monster::update), 0.05f);
	monsternum++;
	monsterSprite->setPosition(620, 80);
}

void GameMap2::init_m3(float delta) {
	monsternum++;
	auto monsterSprite = Monster::create();
	this->addChild(monsterSprite, 100 - monsternum);
	(monsterSprite->map_num) = 2;
	monsterSprite->initmonster_type3();
	monsterSprite->schedule(schedule_selector(Monster::update), 0.05f);
	monsterSprite->setPosition(620, 80);
}


void GameMap2::bo(float a) {
	cocos2d::Texture2D* texture;
	switch (current_wave)
	{
	case 1:
		//第一波：五个便便怪
		schedule(schedule_selector(GameMap2::init_m2), 1, 4, 1);
		texture = Director::getInstance()->getTextureCache()->addImage("Gamemap/wave_1.png");
		// 设置新的纹理  
		wave->setTexture(texture);
		break;
	case 2:
		//第二波：五个黑煤球
		texture = Director::getInstance()->getTextureCache()->addImage("Gamemap/wave_2.png");
		// 设置新的纹理  
		wave->setTexture(texture);
		schedule(schedule_selector(GameMap2::init_m1), 1, 4, 1);
		break;
	case 3:
		//第三波：五个小蝙蝠
		texture = Director::getInstance()->getTextureCache()->addImage("Gamemap/wave_3.png");
		// 设置新的纹理  
		wave->setTexture(texture);
		schedule(schedule_selector(GameMap2::init_m3), 1, 4, 1);
		break;
	case 4:
		//第四波：五个便便怪
		texture = Director::getInstance()->getTextureCache()->addImage("Gamemap/wave_4.png");
		// 设置新的纹理  
		wave->setTexture(texture);
		schedule(schedule_selector(GameMap2::init_m2), 1, 4, 1);
		break;
	case 5:
		texture = Director::getInstance()->getTextureCache()->addImage("Gamemap/wave_5.png");
		// 设置新的纹理  
		wave->setTexture(texture);
		schedule(schedule_selector(GameMap2::init_m3), 1, 4, 1);
		break;
	case 6:
		//第五波：各五个
		schedule(schedule_selector(GameMap2::init_m2), 1, 4, 1);
		break;
	case 7:
		schedule(schedule_selector(GameMap2::init_m1), 1, 4, 1);
		break;
	}
	current_wave++;
	if (current_wave < 6)
		this->schedule(schedule_selector(GameMap2::next_bo), 3);
	else
	{
		this->scheduleOnce(schedule_selector(GameMap2::bo), 5);
	}
}

void GameMap2::next_bo(float a) {
	if (current_wave >= 8) {
		if (monsternum >= 35 && monsterContainer.empty())
		{//-------------------todo:判断输赢的接口--------------------------------------------------------------------------
			//win();
			this->unschedule(schedule_selector(GameMap2::next_bo));
		}
	}
	else if (monsterContainer.empty())
	{
		this->unschedule(schedule_selector(GameMap2::next_bo));
		this->GameMap2::bo(0.1f);
	}
}