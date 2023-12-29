#include "ChooseLevel.h"
#include "MainScene.h"
#include"EnterScene.h"
#include"GameMap1.h"
#include <string.h>
#include"..\Classes\Monster\My_monster.h"
#include"..\Classes\Tower\Tower.h"
#include"..\Classes\Tower\BottleTower.h"
#include"..\Classes\Tower\ShitTower.h"
#include"Barrier.h"
#include<vector>

#define i_max 6
#define j_max 13
#define x_min 90
#define x_max 1050
#define y_min 90
#define y_max 520


USING_NS_CC;
using namespace cocos2d::ui;
//-------------------------------------  全局变量 ------------------------------------------------
//关卡选项
int if_speed_up;//是否加速
bool isGamePaused = false;//是否暂停
//游戏内数据
int game_money;//金钱
int current_wave;//当前波数

int max_waves;//总波数
int carrot_hp;//记录萝卜血量
int monsternum ;
int die_monsternum ;
//pos carrot_position;//记录萝卜位置
int tower_available[3];//可建造防御塔存储
//Tower_information tower_map[7][12];//储存防御塔信息的数组
//Enemy* destination;
//vector<LevelPath> levelPath;
//vector<Enemy*> barrier;
//vector<Enemy*> monster;
//游戏统计数据
int money_total;//击杀获得金钱总数
int monster_total;//击杀怪物总数
int boss_total;//击杀boss总数
int barrier_total;//摧毁障碍总数

int map[i_max][j_max] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,1,1,0,0,0,0,0,1,1,1,0,
	0,0,0,1,0,0,0,0,0,1,0,0,0,
	0,0,0,1,0,0,0,0,0,1,0,0,0,
	0,0,0,1,0,0,0,0,0,1,0,0,0,
	0,0,0,1,1,1,1,1,1,1,0,0,0
};

//----------------------------------------- GameMap1 ------------------------------------------------
cocos2d::Scene* GameMap1::createScene()
{
	return GameMap1::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading:%s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameMap.cpp\n");
}


bool GameMap1::init()
{
	if (!Scene::init())
		return false;

	//---------------------------------------设置背景地图-----------------------------------------------
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// 添加背景
	auto background = Sprite::create("GameMap/map.png");  // 使用你的背景图片文件名
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	// 计算缩放比例，以适应屏幕
	float scaleX = visibleSize.width / background->getContentSize().width;
	float scaleY = visibleSize.height / background->getContentSize().height;
	// 设置精灵的缩放
	background->setScale(scaleX, scaleY);
	this->addChild(background);
	 
	//---------------------------------------UI按钮控件栏------------------------------------------------
	auto layerUI = Layer::create();
	this->addChild(layerUI);
	auto upPanelPinfo = AutoPolygon::generatePolygon("GameMap/top.png");

	auto upPanel = Sprite::create(upPanelPinfo);
	upPanel->setAnchorPoint(Vec2(0, 1));
	upPanel->setPosition(0, Director::getInstance()->getVisibleSize().height+330);
	upPanel->setScale(1.05);
	layerUI->addChild(upPanel);

	setPauseButton(layerUI);

	//倒计时
	countDown();

	//-------------------------------------放置萝卜------------------------------------------------------
	auto CarrotSprite = Carrot::create();
	CarrotSprite->setLocation(Vec2(1000, 485));
	this->addChild(CarrotSprite, 100);
	CarrotSprite->initCarrot();
	CarrotSprite->schedule(schedule_selector(Carrot::update), 0.4f);
	//-----------------------------------放置障碍物----------------------------------------------------------
	auto BarrierSprite = Barrier::create();
	this->addChild(BarrierSprite, 100);
	BarrierSprite->initBarrier();
	BarrierSprite->schedule(schedule_selector(Barrier::update), 0.4f);

	//-------------------------------------设置点击事件监听----------------------------------------------
	// 设置点击事件监听
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = CC_CALLBACK_1(GameMap1::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	//-----------------------------------怪物波数----------------------------------------------------------
	current_wave = 1;
	monsternum = 0;
	die_monsternum = 0;
	this->scheduleOnce(schedule_selector(GameMap1::bo), 5);
	/*auto BulletSprite1 = GreenTowerBullet::create();
	this->addChild(BulletSprite1, 3);
	BulletSprite1->initGreenBullet(1);

	BulletSprite->monsterContainer.pushBack(monsterSprite);
	BulletSprite1->inputBulletAction(Vec2(1000, 300), Vec2(335, 300));//src\dst
	BulletSprite1->shoot();
	*/

	return true;
}
void GameMap1::setPauseButton(Layer* layerUI)
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
		}
		else {
			// 游戏暂停
			Director::getInstance()->pause();
			isGamePaused = true;
			pausebtn->loadTextures("GameMap/pause_1.png", "GameMap/pause_1.png");
		}
	// 消耗触摸事件，阻止传递给其他节点
	Event* event = static_cast<Event*>(sender);
	event->stopPropagation();
		});
}
bool GameMap1::is_out_of_range(int x, int y)
{
	if (x<x_min || x>x_max || y<y_min || y>y_max)
		return true;
	else
		return false;
}

void GameMap1::transform_xy_to_ij(int& i, int& j, const int x, const int y)
{
	j = (x - 50) / 80;
	i = 6 - (y - 10) / 80;
}

void GameMap1::transform_ij_to_xy(const int i, const int j, int& x, int& y)
{
	x = 90 + 80 * j;
	y = 40 + 80 * (6 - i);

}

int GameMap1::getStatus(int x, int y)
{
	int i, j;
	transform_xy_to_ij(i, j, x, y);
	
	//如果在地图边缘，则不能放置
	if (is_out_of_range(x,y))
		return -1;
	//如果在路径上或者是障碍，则不能被放置
	if (map[i][j] == PATH|| map[i][j] == BARRIER)
		return -1;
	//如果位置为空，则可以放置
	if (map[i][j] == EMPTY)
		return EMPTY;
	//如果位置有炮塔，则可以升级
	if (map[i][j] == PLACED)
		return PLACED;
	return -1;
}

// 设置bottle按钮点击事件处理函数
void GameMap1::bottlebuttonClickCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type,int i,int j,int placex,int placey)
{
	// 处理按钮点击事件
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		CCLOG("Button Clicked!");

		map[i][j] = PLACED;

		// 移除所有按钮
		hideButton();

		// 创建BottleTower
		auto bottletower = BottleTower::create("Tower/Bottle11.png");
		bottletower->pos_i = i;
		bottletower->pos_j = j;
		bottletower->setPosition(Vec2(placex, placey));

		// 将防御塔添加到场景和容器中
		this->addChild(bottletower,8);
		bottletowers.pushBack(bottletower);
	}
}

// 设置shit按钮点击事件处理函数
void GameMap1::shitbuttonClickCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type, int i, int j, int placex, int placey)
{
	// 处理按钮点击事件
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		CCLOG("Button Clicked!");

		map[i][j] = PLACED;

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

//移除button
void GameMap1::hideButton()
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

void GameMap1::onMouseDown(EventMouse* event)
{
	// 获取点击的位置
	int mousex = event->getCursorX();
	int mousey = event->getCursorY();
	int placex, placey;
	Vec2 clickLocation = Vec2(mousex, mousey);
	int i, j;
	int status = getStatus(mousex, mousey);


	// 如果已经选中了位置，取消选中并隐藏按钮
	if (selectedPosition != Vec2::ZERO) {
		//消除所有按钮和显示
		if (bottlebtn && bottlebtn->getBoundingBox().containsPoint(clickLocation)) {
			// 如果点击到了按钮，则不取消选中，而是处理按钮点击事件
			return;
		}
		else if (shitbtn && shitbtn->getBoundingBox().containsPoint(clickLocation)) {
			return;
		}
		else if (upgradebtn && upgradebtn->getBoundingBox().containsPoint(clickLocation)) {
			return;
		}
		else if (cancelbtn && cancelbtn->getBoundingBox().containsPoint(clickLocation)) {
			return;
		}
		else if (maxbtn && maxbtn->getBoundingBox().containsPoint(clickLocation)) {
			return;
		}
		else {
			hideButton();
			selectedPosition = Vec2::ZERO;
			return;
		}
	}

	if (status == -1) {//当前位置不能放置炮塔

		// 创建警告精灵并设置图片
		auto warning = Sprite::create("GameMap/warning.png");
		warning->setScale(0.8);
		warning->setPosition(clickLocation);

		// 将警告精灵添加到场景
		this->addChild(warning);

		// 延迟一定时间后移除精灵
		auto delayAction = DelayTime::create(0.5f); // 延迟0.5秒
		auto removeAction = RemoveSelf::create();
		auto sequence = Sequence::create(delayAction, removeAction, nullptr);

		warning->runAction(sequence);
		return;
	}
	else if (status == EMPTY) {//当前位置可以放置炮塔

		transform_xy_to_ij(i, j, mousex, mousey);
		transform_ij_to_xy(i, j, placex, placey);

		//显示添加炮塔的图片框
		setTower = Sprite::create("GameMap/select_01.png");
		setTower->setPosition(Vec2(90 + 80 * j, 40 + 80 * (6 - i)));
		this->addChild(setTower, 5);
		selectedPosition = clickLocation;

		//-------------------------------------------------------------------------
		// todo：在下方出现创建炮塔的按钮，有钱创建，没钱创建

		if (/*money_is_enough*/1) {
			// 创建按钮
			bottlebtn = Button::create("Tower/Bottle01.png", "Tower/Bottle01.png", "");
			bottlebtn->setPosition(Vec2(placex - 40, placey - 70));
			bottlebtn->setScale(0.8);
			bottlebtn->addTouchEventListener(CC_CALLBACK_2(GameMap1::bottlebuttonClickCallback, this, i, j, placex, placey));
			this->addChild(bottlebtn, 10);

			shitbtn = Button::create("Tower/shit01.png", "Tower/shit01.png", "");
			shitbtn->setPosition(Vec2(placex + 40, placey - 70));
			shitbtn->setScale(0.7);
			shitbtn->addTouchEventListener(CC_CALLBACK_2(GameMap1::shitbuttonClickCallback, this, i, j, placex, placey));
			this->addChild(shitbtn, 10);

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

		if (bt != NULL)
			upgradeBottle(bt);
		if (st != NULL)
			upgradeShit(st);
		//---------------todo:升级----------------------
	}
	// 吞噬触摸事件，阻止其传递给下层的节点
	event->stopPropagation();
}
//升级按钮的回调函数
void GameMap1::upgradebuttonClickCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type, const std::string& towerImage,BottleTower*bt,ShitTower*st)
{
	// 处理按钮点击事件
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		CCLOG("Button Clicked!");
		if (bt ) {
			//更新等级
			bt->level++;
			//升级换图片
			bt->setTexture(towerImage);
			// 移除所有按钮
			hideButton();
			return;
		}
		if (st ) {
			//更新等级
			st->level++;
			//升级换图片
			st->setTexture(towerImage);
			st->setScale(0.9);
			// 移除所有按钮
			hideButton();
			return;
		}
	}
}

//拆除按钮的回调函数
void GameMap1::cancelbuttonClickCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type, BottleTower* bt, ShitTower* st)
{
	// 处理按钮点击事件
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		CCLOG("Button Clicked!");

		//拆除bottle
		if (bt) {
			map[bt->pos_i][bt->pos_j] = EMPTY;
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
			map[st->pos_i][st->pos_j] = EMPTY;
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
	}
}


void GameMap1::upgradeBottle(BottleTower* bt) 
{
	ShitTower* emptytower = NULL;
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

		setUpgradeButton(upgradebtnImage, towerImage, pos_x, pos_y, 1, bt, emptytower);
		setCancelButton(cancelbtnImage, pos_x, pos_y, bt, emptytower);
		
	}
	/*二级炮塔升级*/
	else if (bt->level == 2) {

		//放置范围灰色圈
		setRange(scale2, pos_x, pos_y);

		//放置升级和删除的按钮
		std::string upgradebtnImage = "Tower/upgradebottle2.png";
		std::string towerImage = "Tower/Bottle31.png";
		std::string cancelbtnImage = "Tower/cancelbottle2.png";

		setUpgradeButton(upgradebtnImage, towerImage, pos_x, pos_y, 1, bt, emptytower);
		setCancelButton(cancelbtnImage, pos_x, pos_y, bt, emptytower);

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

		setCancelButton(cancelbtnImage, pos_x, pos_y, bt, emptytower);
	}
}

void GameMap1::upgradeShit(ShitTower*st)
{
	BottleTower* emptytower = NULL;
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

		setUpgradeButton(upgradebtnImage, towerImage, pos_x, pos_y, 1, emptytower, st);
		setCancelButton(cancelbtnImage, pos_x, pos_y, emptytower, st);

	}
	/*二级炮塔升级*/
	else if (st->level == 2) {

		//放置范围灰色圈
		setRange(scale2, pos_x, pos_y);

		//放置升级和删除的按钮
		std::string upgradebtnImage = "Tower/upgradeshit2.png";
		std::string towerImage = "Tower/shit3.png";
		std::string cancelbtnImage = "Tower/cancelshit2.png";

		setUpgradeButton(upgradebtnImage, towerImage, pos_x, pos_y, 1, emptytower, st);
		setCancelButton(cancelbtnImage, pos_x, pos_y, emptytower, st);

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

		setCancelButton(cancelbtnImage, pos_x, pos_y, emptytower, st);
	}
}


void GameMap1::setUpgradeButton(const std::string& btnImage, const std::string& towerImage, int pos_x, int pos_y, bool can_be_clicked, BottleTower* bt, ShitTower* st)
{
	upgradebtn = Button::create(btnImage, btnImage, "");
	upgradebtn->setPosition(Vec2(pos_x, pos_y + 70));
	upgradebtn->setScale(0.8);
	if (can_be_clicked)
		upgradebtn->addTouchEventListener(CC_CALLBACK_2(GameMap1::upgradebuttonClickCallback, this, towerImage, bt, st));
	this->addChild(upgradebtn, 10);
}

void GameMap1::setRange(float scale, int pos_x, int pos_y)
{
	range = Sprite::create("Tower/range.png");
	range->setPosition(Vec2(pos_x, pos_y));
	range->setScale(scale);
	this->addChild(range);
}

void GameMap1::setCancelButton(const std::string& btnImage, int pos_x, int pos_y, BottleTower* bt, ShitTower* st)
{
	cancelbtn = Button::create(btnImage, btnImage, "");
	cancelbtn->setPosition(Vec2(pos_x, pos_y - 70));
	cancelbtn->setScale(0.8);
	cancelbtn->addTouchEventListener(CC_CALLBACK_2(GameMap1::cancelbuttonClickCallback, this, bt,st));
	this->addChild(cancelbtn, 10);
}

//倒计时
void GameMap1::countDown()
{
	//获取屏幕大小
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//倒计时的时候游戏是暂停的
	//if_pause = 1;
	//倒计时页
	auto time_layer = Layer::create();
	this->addChild(time_layer);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch* touch, Event* event) {
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, time_layer);

	//倒计时背景盘
	auto timepanel = Sprite::create("GameMap/timepanel.png");
	timepanel->setPosition(Vec2(origin.x + visibleSize.width / 2,origin.y + visibleSize.height / 2));
	time_layer->addChild(timepanel);

	//倒计时数字
	auto number = Sprite::create("GameMap/time3.png");
	number->setPosition(Vec2(origin.x + visibleSize.width * 0.5,origin.y + visibleSize.height / 2+10));
	time_layer->addChild(number);

	//倒计时转圈
	auto circle = Sprite::create("GameMap/timecircle.png");
	circle->setPosition(Vec2(visibleSize.width / 2+2, + visibleSize.height / 2));
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

void GameMap1::init_m1(float delta) {
	auto monsterSprite = Monster::create();
	this->addChild(monsterSprite, 100 - monsternum);
	monsterSprite->initmonster_type1();
	monsterSprite->schedule(schedule_selector(Monster::update), 0.05f);
	monsternum++;
}

void GameMap1::init_m2(float delta) {
	auto monsterSprite = Monster::create();
	this->addChild(monsterSprite, 100 - monsternum);
	monsterSprite->initmonster_type2();
	monsterSprite->schedule(schedule_selector(Monster::update), 0.05f);
	monsternum++;
}

void GameMap1::init_m3(float delta) {
	monsternum++;
	auto monsterSprite = Monster::create();
	this->addChild(monsterSprite, 100 - monsternum);
	monsterSprite->initmonster_type3();
	monsterSprite->schedule(schedule_selector(Monster::update), 0.05f);
}




void GameMap1::bo(float a) {

	switch (current_wave)
	{
		case 1:
			//第一波：五个便便怪
			schedule(schedule_selector(GameMap1::init_m3), 1, 4, 1);
			break;
		case 2:
			//第二波：五个黑煤球
			schedule(schedule_selector(GameMap1::init_m1), 1, 4, 1);
			break;
		case 3:
			//第三波：五个小蝙蝠
			schedule(schedule_selector(GameMap1::init_m2), 1, 4, 1);
			break;
		case 4:
			//第四波：五个便便怪
			schedule(schedule_selector(GameMap1::init_m3), 1, 4, 1);
			break;
		case 5:
			schedule(schedule_selector(GameMap1::init_m3), 1, 4, 1);
			break;
		case 6:
			//第五波：各五个
			schedule(schedule_selector(GameMap1::init_m2), 1, 4, 1);
			break;
		case 7:
			schedule(schedule_selector(GameMap1::init_m1), 1, 4, 1);
			break;
	}
	current_wave++;
	if (current_wave < 6)
		this->schedule(schedule_selector(GameMap1::next_bo), 3);
	else
	{
		this->scheduleOnce(schedule_selector(GameMap1::bo), 5);
	}
}

void GameMap1::next_bo(float a) {
	if (die_monsternum == monsternum)
	{
		this->unschedule(schedule_selector(GameMap1::next_bo));
		this->GameMap1::bo(0.1f);
	}
}