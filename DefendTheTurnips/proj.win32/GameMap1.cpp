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
//-------------------------------------  ȫ�ֱ��� ------------------------------------------------
//�ؿ�ѡ��
int if_speed_up;//�Ƿ����
bool isGamePaused = false;//�Ƿ���ͣ
//��Ϸ������
int game_money;//��Ǯ
int current_wave;//��ǰ����

int max_waves;//�ܲ���
int carrot_hp;//��¼�ܲ�Ѫ��
int monsternum ;
int die_monsternum ;
//pos carrot_position;//��¼�ܲ�λ��
int tower_available[3];//�ɽ���������洢
//Tower_information tower_map[7][12];//�����������Ϣ������
//Enemy* destination;
//vector<LevelPath> levelPath;
//vector<Enemy*> barrier;
//vector<Enemy*> monster;
//��Ϸͳ������
int money_total;//��ɱ��ý�Ǯ����
int monster_total;//��ɱ��������
int boss_total;//��ɱboss����
int barrier_total;//�ݻ��ϰ�����

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

	//---------------------------------------���ñ�����ͼ-----------------------------------------------
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// ��ӱ���
	auto background = Sprite::create("GameMap/map.png");  // ʹ����ı���ͼƬ�ļ���
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	// �������ű���������Ӧ��Ļ
	float scaleX = visibleSize.width / background->getContentSize().width;
	float scaleY = visibleSize.height / background->getContentSize().height;
	// ���þ��������
	background->setScale(scaleX, scaleY);
	this->addChild(background);
	 
	//---------------------------------------UI��ť�ؼ���------------------------------------------------
	auto layerUI = Layer::create();
	this->addChild(layerUI);
	auto upPanelPinfo = AutoPolygon::generatePolygon("GameMap/top.png");

	auto upPanel = Sprite::create(upPanelPinfo);
	upPanel->setAnchorPoint(Vec2(0, 1));
	upPanel->setPosition(0, Director::getInstance()->getVisibleSize().height+330);
	upPanel->setScale(1.05);
	layerUI->addChild(upPanel);

	setPauseButton(layerUI);

	//����ʱ
	countDown();

	//-------------------------------------�����ܲ�------------------------------------------------------
	auto CarrotSprite = Carrot::create();
	CarrotSprite->setLocation(Vec2(1000, 485));
	this->addChild(CarrotSprite, 100);
	CarrotSprite->initCarrot();
	CarrotSprite->schedule(schedule_selector(Carrot::update), 0.4f);
	//-----------------------------------�����ϰ���----------------------------------------------------------
	auto BarrierSprite = Barrier::create();
	this->addChild(BarrierSprite, 100);
	BarrierSprite->initBarrier();
	BarrierSprite->schedule(schedule_selector(Barrier::update), 0.4f);

	//-------------------------------------���õ���¼�����----------------------------------------------
	// ���õ���¼�����
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = CC_CALLBACK_1(GameMap1::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	//-----------------------------------���ﲨ��----------------------------------------------------------
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

	// ���ð�ť����¼�������
	pausebtn->addClickEventListener([=](Ref* sender) {
		if (isGamePaused) {
			// ��Ϸ����
			Director::getInstance()->resume();
			isGamePaused = false;
			pausebtn->loadTextures("GameMap/pause_0.png", "GameMap/pause_0.png");
		}
		else {
			// ��Ϸ��ͣ
			Director::getInstance()->pause();
			isGamePaused = true;
			pausebtn->loadTextures("GameMap/pause_1.png", "GameMap/pause_1.png");
		}
	// ���Ĵ����¼�����ֹ���ݸ������ڵ�
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
	
	//����ڵ�ͼ��Ե�����ܷ���
	if (is_out_of_range(x,y))
		return -1;
	//�����·���ϻ������ϰ������ܱ�����
	if (map[i][j] == PATH|| map[i][j] == BARRIER)
		return -1;
	//���λ��Ϊ�գ�����Է���
	if (map[i][j] == EMPTY)
		return EMPTY;
	//���λ�������������������
	if (map[i][j] == PLACED)
		return PLACED;
	return -1;
}

// ����bottle��ť����¼�������
void GameMap1::bottlebuttonClickCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type,int i,int j,int placex,int placey)
{
	// ����ť����¼�
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		CCLOG("Button Clicked!");

		map[i][j] = PLACED;

		// �Ƴ����а�ť
		hideButton();

		// ����BottleTower
		auto bottletower = BottleTower::create("Tower/Bottle11.png");
		bottletower->pos_i = i;
		bottletower->pos_j = j;
		bottletower->setPosition(Vec2(placex, placey));

		// ����������ӵ�������������
		this->addChild(bottletower,8);
		bottletowers.pushBack(bottletower);
	}
}

// ����shit��ť����¼�������
void GameMap1::shitbuttonClickCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type, int i, int j, int placex, int placey)
{
	// ����ť����¼�
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		CCLOG("Button Clicked!");

		map[i][j] = PLACED;

		// �Ƴ����а�ť
		hideButton();

		// ����ShitTower
		auto shittower = ShitTower::create("Tower/shit1.png");
		shittower->pos_i = i;
		shittower->pos_j = j;
		shittower->setPosition(Vec2(placex, placey));
		shittower->setScale(0.9);

		// ����������ӵ�������������
		this->addChild(shittower, 8);
		shittowers.pushBack(shittower);
	}
}

//�Ƴ�button
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
		// ��ʽ���� range�������ڶ����ڼ䲶������ָ��
		auto rangePtr = range;

		range->runAction(Sequence::create(
			// ���Ŷ������ӳ�ʼ��С�� 0
			ScaleTo::create(scaleDuration, 0.0f),

			// ���ؾ���
			Hide::create(),

			// ������������
			cocos2d::CallFunc::create([rangePtr]() {
				// �ڶ�������ʱ������ִ��һЩ��������
				// ����ӳ������Ƴ�����
				if (rangePtr) {
					rangePtr->removeFromParent();
				}
				}),
			nullptr
					));

		// Ϊ�˱����ڶ���ִ���ڼ��޸�ָ�룬�� range ����Ϊ nullptr
		range = nullptr;
	}
	selectedPosition = Vec2::ZERO;
}

void GameMap1::onMouseDown(EventMouse* event)
{
	// ��ȡ�����λ��
	int mousex = event->getCursorX();
	int mousey = event->getCursorY();
	int placex, placey;
	Vec2 clickLocation = Vec2(mousex, mousey);
	int i, j;
	int status = getStatus(mousex, mousey);


	// ����Ѿ�ѡ����λ�ã�ȡ��ѡ�в����ذ�ť
	if (selectedPosition != Vec2::ZERO) {
		//�������а�ť����ʾ
		if (bottlebtn && bottlebtn->getBoundingBox().containsPoint(clickLocation)) {
			// ���������˰�ť����ȡ��ѡ�У����Ǵ���ť����¼�
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

	if (status == -1) {//��ǰλ�ò��ܷ�������

		// �������澫�鲢����ͼƬ
		auto warning = Sprite::create("GameMap/warning.png");
		warning->setScale(0.8);
		warning->setPosition(clickLocation);

		// �����澫����ӵ�����
		this->addChild(warning);

		// �ӳ�һ��ʱ����Ƴ�����
		auto delayAction = DelayTime::create(0.5f); // �ӳ�0.5��
		auto removeAction = RemoveSelf::create();
		auto sequence = Sequence::create(delayAction, removeAction, nullptr);

		warning->runAction(sequence);
		return;
	}
	else if (status == EMPTY) {//��ǰλ�ÿ��Է�������

		transform_xy_to_ij(i, j, mousex, mousey);
		transform_ij_to_xy(i, j, placex, placey);

		//��ʾ���������ͼƬ��
		setTower = Sprite::create("GameMap/select_01.png");
		setTower->setPosition(Vec2(90 + 80 * j, 40 + 80 * (6 - i)));
		this->addChild(setTower, 5);
		selectedPosition = clickLocation;

		//-------------------------------------------------------------------------
		// todo�����·����ִ��������İ�ť����Ǯ������ûǮ����

		if (/*money_is_enough*/1) {
			// ������ť
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
			// ������ť
			bottlebtn = Button::create("Tower/Bottle00.png", "Tower/Bottle00.png", "");
			bottlebtn->setScale(0.8);
			bottlebtn->setPosition(Vec2(placex - 40, placey - 70));
			this->addChild(bottlebtn, 10);
		}
	}
	else {//��ǰλ����������������

		transform_xy_to_ij(i, j, mousex, mousey);
		selectedPosition = clickLocation;

		BottleTower* bt = NULL;//�ҵ���i��j��λ�õ�bottletower���Ҳ�������NULL
		for (auto tower : bottletowers) {
			if (tower->pos_i == i && tower->pos_j == j) {
				bt = tower;
				break;
			}
		}

		ShitTower* st = NULL;//�ҵ���i��j��λ�õ�shittower���Ҳ�������NULL
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
		//---------------todo:����----------------------
	}
	// ���ɴ����¼�����ֹ�䴫�ݸ��²�Ľڵ�
	event->stopPropagation();
}
//������ť�Ļص�����
void GameMap1::upgradebuttonClickCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type, const std::string& towerImage,BottleTower*bt,ShitTower*st)
{
	// ����ť����¼�
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		CCLOG("Button Clicked!");
		if (bt ) {
			//���µȼ�
			bt->level++;
			//������ͼƬ
			bt->setTexture(towerImage);
			// �Ƴ����а�ť
			hideButton();
			return;
		}
		if (st ) {
			//���µȼ�
			st->level++;
			//������ͼƬ
			st->setTexture(towerImage);
			st->setScale(0.9);
			// �Ƴ����а�ť
			hideButton();
			return;
		}
	}
}

//�����ť�Ļص�����
void GameMap1::cancelbuttonClickCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type, BottleTower* bt, ShitTower* st)
{
	// ����ť����¼�
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		CCLOG("Button Clicked!");

		//���bottle
		if (bt) {
			map[bt->pos_i][bt->pos_j] = EMPTY;
			bt->removeFromParent();
			auto it = bottletowers.begin();
			while (it != bottletowers.end()) {
				if (*it == bt) {//�ҵ���ǰ����
					delete* it;  // �����Ҫ�ֶ��ͷ��ڴ�
					it = bottletowers.erase(it);  // �� vector ��ɾ��Ԫ��
				}
				else
					++it;
			}
			// �Ƴ����а�ť
			hideButton();
			return;
		}
		//���shit
		if (st) {
			map[st->pos_i][st->pos_j] = EMPTY;
			st->removeFromParent();
			auto it = shittowers.begin();
			while (it != shittowers.end()) {
				if (*it == st) {//�ҵ���ǰ����
					delete* it;  // �����Ҫ�ֶ��ͷ��ڴ�
					it = shittowers.erase(it);  // �� vector ��ɾ��Ԫ��
				}
				else
					++it;
			}
			// �Ƴ����а�ť
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

	/*һ����������*/
	if (bt->level == 1) {
		
		//���÷�Χ��ɫȦ
		setRange(scale1, pos_x, pos_y);

		//����������ɾ���İ�ť
		std::string upgradebtnImage = "Tower/upgradebottle1.png";
		std::string towerImage = "Tower/Bottle21.png";
		std::string cancelbtnImage = "Tower/cancelbottle1.png";

		setUpgradeButton(upgradebtnImage, towerImage, pos_x, pos_y, 1, bt, emptytower);
		setCancelButton(cancelbtnImage, pos_x, pos_y, bt, emptytower);
		
	}
	/*������������*/
	else if (bt->level == 2) {

		//���÷�Χ��ɫȦ
		setRange(scale2, pos_x, pos_y);

		//����������ɾ���İ�ť
		std::string upgradebtnImage = "Tower/upgradebottle2.png";
		std::string towerImage = "Tower/Bottle31.png";
		std::string cancelbtnImage = "Tower/cancelbottle2.png";

		setUpgradeButton(upgradebtnImage, towerImage, pos_x, pos_y, 1, bt, emptytower);
		setCancelButton(cancelbtnImage, pos_x, pos_y, bt, emptytower);

	}
	/*��������������������ֻ�ܲ�*/
	else {

		std::string cancelbtnImage = "Tower/cancelbottle3.png";
		//���÷�Χ��ɫȦ
		setRange(scale3, pos_x, pos_y);

		//����max��ɾ���İ�ť
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

	/*һ����������*/
	if (st->level == 1) {

		//���÷�Χ��ɫȦ
		setRange(scale1, pos_x, pos_y);

		//����������ɾ���İ�ť
		std::string upgradebtnImage = "Tower/upgradeshit1.png";
		std::string towerImage = "Tower/shit2.png";
		std::string cancelbtnImage = "Tower/cancelshit1.png";

		setUpgradeButton(upgradebtnImage, towerImage, pos_x, pos_y, 1, emptytower, st);
		setCancelButton(cancelbtnImage, pos_x, pos_y, emptytower, st);

	}
	/*������������*/
	else if (st->level == 2) {

		//���÷�Χ��ɫȦ
		setRange(scale2, pos_x, pos_y);

		//����������ɾ���İ�ť
		std::string upgradebtnImage = "Tower/upgradeshit2.png";
		std::string towerImage = "Tower/shit3.png";
		std::string cancelbtnImage = "Tower/cancelshit2.png";

		setUpgradeButton(upgradebtnImage, towerImage, pos_x, pos_y, 1, emptytower, st);
		setCancelButton(cancelbtnImage, pos_x, pos_y, emptytower, st);

	}
	/*��������������������ֻ�ܲ�*/
	else {

		std::string cancelbtnImage = "Tower/cancelshit3.png";
		//���÷�Χ��ɫȦ
		setRange(scale3, pos_x, pos_y);

		//����max��ɾ���İ�ť
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

//����ʱ
void GameMap1::countDown()
{
	//��ȡ��Ļ��С
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//����ʱ��ʱ����Ϸ����ͣ��
	//if_pause = 1;
	//����ʱҳ
	auto time_layer = Layer::create();
	this->addChild(time_layer);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch* touch, Event* event) {
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, time_layer);

	//����ʱ������
	auto timepanel = Sprite::create("GameMap/timepanel.png");
	timepanel->setPosition(Vec2(origin.x + visibleSize.width / 2,origin.y + visibleSize.height / 2));
	time_layer->addChild(timepanel);

	//����ʱ����
	auto number = Sprite::create("GameMap/time3.png");
	number->setPosition(Vec2(origin.x + visibleSize.width * 0.5,origin.y + visibleSize.height / 2+10));
	time_layer->addChild(number);

	//����ʱתȦ
	auto circle = Sprite::create("GameMap/timecircle.png");
	circle->setPosition(Vec2(visibleSize.width / 2+2, + visibleSize.height / 2));
	circle->setAnchorPoint(Vec2(1, 0.5));
	circle->setScale(0.95);
	time_layer->addChild(circle);
	circle->runAction(Sequence::create(Repeat::create(RotateBy::create(1, -360), 3), FadeOut::create(0.1), nullptr));
	timepanel->runAction(Sequence::create(DelayTime::create(4), FadeOut::create(0.1), nullptr));

	//����֡����������ֵĵ���ʱ
	Vector<SpriteFrame*> frame;
	frame.pushBack(SpriteFrame::create("GameMap/time3.png", Rect(0, 0, 95, 114)));
	frame.pushBack(SpriteFrame::create("GameMap/time2.png", Rect(0, 0, 95, 114)));
	frame.pushBack(SpriteFrame::create("GameMap/time1.png", Rect(0, 0, 95, 114)));
	frame.pushBack(SpriteFrame::create("GameMap/timego.png", Rect(0, 0, 210, 114)));
	number->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(frame, 1)), FadeOut::create(0.1), nullptr));


	//���������ֲ�ɾ��
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
			//��һ�����������
			schedule(schedule_selector(GameMap1::init_m3), 1, 4, 1);
			break;
		case 2:
			//�ڶ����������ú��
			schedule(schedule_selector(GameMap1::init_m1), 1, 4, 1);
			break;
		case 3:
			//�����������С����
			schedule(schedule_selector(GameMap1::init_m2), 1, 4, 1);
			break;
		case 4:
			//���Ĳ����������
			schedule(schedule_selector(GameMap1::init_m3), 1, 4, 1);
			break;
		case 5:
			schedule(schedule_selector(GameMap1::init_m3), 1, 4, 1);
			break;
		case 6:
			//���岨�������
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