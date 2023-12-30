#include "ChooseLevel.h"
#include "MainScene.h"
#include"EnterScene1.h"
#include"GameMap1.h"
#include"GameMap2.h"
#include <string.h>
#include"..\Classes\Monster\My_monster.h"
#include"..\Classes\Tower\Tower.h"
#include"..\Classes\Tower\BottleTower.h"
#include"..\Classes\Tower\ShitTower.h"
#include"..\Classes\Barrier\Barrier.h"
#include<vector>


USING_NS_CC;
using namespace cocos2d::ui;
//-------------------------------------  ȫ�ֱ��� ------------------------------------------------
int monsternum;
int die_monsternum;

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
	// ���ӱ���
	auto background = Sprite::create("GameMap/map.png");  // ʹ����ı���ͼƬ�ļ���
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	// �������ű���������Ӧ��Ļ
	float scaleX = visibleSize.width / background->getContentSize().width;
	float scaleY = visibleSize.height / background->getContentSize().height;
	// ���þ��������
	background->setScale(scaleX, scaleY);
	this->addChild(background);
	// ����׮��
	auto flag = Sprite::create("GameMap/flag.png");  // ʹ����ı���ͼƬ�ļ���
	flag->setPosition(165, 505);
	this->addChild(flag);
	//---------------------------------------UI��ť�ؼ���------------------------------------------------
	auto layerUI = Layer::create();
	this->addChild(layerUI,7);
	auto upPanelPinfo = AutoPolygon::generatePolygon("GameMap/top.png");

	auto upPanel = Sprite::create(upPanelPinfo);
	upPanel->setAnchorPoint(Vec2(0, 1));
	upPanel->setPosition(0, Director::getInstance()->getVisibleSize().height+330);
	upPanel->setScale(1.05);
	layerUI->addChild(upPanel);

	setPauseButton(layerUI);
	setMenuButton(layerUI);
	//����ʱ
	countDown();
	
	//-------------------------------------�����ܲ�------------------------------------------------------
	auto CarrotSprite = Carrot::create();
	CarrotSprite->setLocation(Vec2(1000, 460));
	this->addChild(CarrotSprite, 100);
	CarrotSprite->initCarrot();
	CarrotSprite->schedule(schedule_selector(Carrot::update), 0.4f);
	//-----------------------------------�����ϰ���----------------------------------------------------------
	InitBarrier();

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

	auto wave_background = Sprite::create("GameMap/waves_bg.png");  // ʹ����ı���ͼƬ�ļ���
	wave_background->setPosition(570, 592);
	layerUI->addChild(wave_background);

	auto wave_05 = Sprite::create("GameMap/wave05.png");  // ʹ����ı���ͼƬ�ļ���
	wave_05->setPosition(570, 600);
	layerUI->addChild(wave_05);
	scaleX = 0.78;
	scaleY = 0.78;
	// ���þ��������
	wave_05->setScale(scaleX, scaleY);

	wave = Sprite::create("GameMap/wave_0.png");  // ʹ����ı���ͼƬ�ļ���
	wave->setPosition(505, 600);
	layerUI->addChild(wave);

	this->schedule(schedule_selector(Monster::update), 0.05f);

	//----------------------------------------------------------------------------------------------------
	return true;
}
void GameMap1::InitBarrier()
{
	Texture2D* texture41 = Director::getInstance()->getTextureCache()->addImage("Barrier/barrier41.png");
	Texture2D* texture42 = Director::getInstance()->getTextureCache()->addImage("Barrier/barrier42.png");
	Texture2D* texture21 = Director::getInstance()->getTextureCache()->addImage("Barrier/barrier21.png");
	Texture2D* texture11 = Director::getInstance()->getTextureCache()->addImage("Barrier/barrier11.png");
	Texture2D* texture12 = Director::getInstance()->getTextureCache()->addImage("Barrier/barrier12.png");

	auto BarrierSprite1 = Barrier::create();
	this->addChild(BarrierSprite1, 5);
	BarrierSprite1->initBarrier(300, 300, texture41, Vec2(460, 485));

	auto BarrierSprite2 = Barrier::create();
	this->addChild(BarrierSprite2, 0);
	BarrierSprite2->initBarrier(2500, 2500, texture42, Vec2(620, 405));

	auto BarrierSprite3 = Barrier::create();
	this->addChild(BarrierSprite3, 0);
	BarrierSprite3->initBarrier(150, 150, texture21, Vec2(620, 205));

	auto BarrierSprite4 = Barrier::create();
	this->addChild(BarrierSprite4, 0);
	BarrierSprite4->initBarrier(70, 70, texture11, Vec2(420, 205));

	auto BarrierSprite5 = Barrier::create();
	this->addChild(BarrierSprite5, 0);
	BarrierSprite5->initBarrier(70, 70, texture12, Vec2(250, 365));

	auto BarrierSprite6 = Barrier::create();
	this->addChild(BarrierSprite6, 0);
	BarrierSprite6->initBarrier(70, 70, texture11, Vec2(250, 525));

	auto BarrierSprite7 = Barrier::create();
	this->addChild(BarrierSprite7, 0);
	BarrierSprite7->initBarrier(70, 70, texture11, Vec2(420, 365));

	auto BarrierSprite8 = Barrier::create();
	this->addChild(BarrierSprite8, 0);
	BarrierSprite8->initBarrier(70, 70, texture11, Vec2(500, 365));

	auto BarrierSprite9 = Barrier::create();
	this->addChild(BarrierSprite9, 0);
	BarrierSprite9->initBarrier(70, 70, texture11, Vec2(580, 285));

	auto BarrierSprite10 = Barrier::create();
	this->addChild(BarrierSprite10, 0);
	BarrierSprite10->initBarrier(70, 70, texture12, Vec2(905, 205));

	auto BarrierSprite11 = Barrier::create();
	this->addChild(BarrierSprite11, 0);
	BarrierSprite11->initBarrier(150, 150, texture21, Vec2(945, 365));

	auto BarrierSprite12 = Barrier::create();
	this->addChild(BarrierSprite12, 0);
	BarrierSprite12->initBarrier(70, 70, texture12, Vec2(745, 285));
}
void GameMap1::setMenuButton(Layer* layerUI)
{
	menubtn = Button::create("GameMap/menu.png", "GameMap/menu.png");
	menubtn->setPressedActionEnabled(true);
	menubtn->setPosition(Vec2(975, 590));
	menubtn->setScale(1.05);
	layerUI->addChild(menubtn);

	// ���ð�ť����¼�������
	menubtn->addClickEventListener([=](Ref* sender) {

		auto gamemenu = Sprite::create("GameMap/gamemenu.png");
	// ���ò˵�λ��
	gamemenu->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
		Director::getInstance()->getVisibleSize().height * 2));
	this->addChild(gamemenu, 200);
	// ִ�в˵����Ϸ��ƶ�������Ķ���
	auto moveAction = EaseBackOut::create(MoveTo::create(0.5f, Vec2(Director::getInstance()->getVisibleSize().width / 2,
		Director::getInstance()->getVisibleSize().height / 2)));
	gamemenu->runAction(moveAction);

	//������Ϸ��ť
	auto continuebtn = Button::create("GameMap/continue.png", "GameMap/continue.png", "");
	gamemenu->addChild(continuebtn);
	continuebtn->setPressedActionEnabled(true);
	continuebtn->setPosition(Vec2(233, 310));
	continuebtn->setScale(1.12);
	continuebtn->addClickEventListener([=](Ref* sender) {
		isGamePaused = false;
	Director::getInstance()->resume();
	gamemenu->removeFromParent();
		});

	//ѡ��ؿ���ť
	auto chooselevelbtn = Button::create("GameMap/chooselevel.png", "GameMap/chooselevel.png", "");
	gamemenu->addChild(chooselevelbtn);
	chooselevelbtn->setPressedActionEnabled(true);
	chooselevelbtn->setPosition(Vec2(233, 202));
	chooselevelbtn->setScale(1.12);
	chooselevelbtn->addClickEventListener([=](Ref* sender) {
		auto chooselevel = ChooseLevel::create();
	Director::getInstance()->replaceScene(chooselevel);
	//?????????????????�ٴν���Ῠס
		});

	//���¿�ʼ��ť
	auto restartbtn = Button::create("GameMap/restart.png", "GameMap/restart.png", "");
	gamemenu->addChild(restartbtn);
	restartbtn->setPressedActionEnabled(true);
	restartbtn->setPosition(Vec2(233, 100));
	restartbtn->setScale(1.12);
	restartbtn->addClickEventListener([=](Ref* sender) {
		auto gamemap1 = GameMap1::create();
	Director::getInstance()->replaceScene(gamemap1);
	//?????????????????�ٴν���Ῠס
		});

	// ʹ��Sequence���Ӷ����ͻص�����
	gamemenu->runAction(Sequence::create(moveAction, CallFunc::create([this]() {
		// �ڶ���ִ�����ִ�еĻص�����
		// ��Ϸ��ͣ
		isGamePaused = true;
	Director::getInstance()->pause();
		}), nullptr));
	
		});
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

// ����bottle��ť����¼���������
void GameMap1::bottlebuttonClickCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type,int i,int j,int placex,int placey)
{
	// ������ť����¼�
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

		// �����������ӵ�������������
		this->addChild(bottletower,8);
		bottletowers.pushBack(bottletower);
	}
}

// ����shit��ť����¼���������
void GameMap1::shitbuttonClickCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type, int i, int j, int placex, int placey)
{
	// ������ť����¼�
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

		// �����������ӵ�������������
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
			// ���������˰�ť����ȡ��ѡ�У����Ǵ�����ť����¼�
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

		// �����澫�����ӵ�����
		this->addChild(warning,6);

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

		//��ʾ����������ͼƬ��
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
	
}
//������ť�Ļص�����
void GameMap1::upgradebuttonClickCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type, const std::string& towerImage,BottleTower*bt,ShitTower*st)
{
	// ������ť����¼�
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
	// ������ť����¼�
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
	this->addChild(range,9);
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
	this->addChild(time_layer,500);

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
	cocos2d::Texture2D* texture;
	switch (current_wave)
	{
		case 1:
			//��һ�����������
			schedule(schedule_selector(GameMap1::init_m3), 1, 4, 1);
			texture = Director::getInstance()->getTextureCache()->addImage("Gamemap/wave_1.png");
			// �����µ�����  
			wave->setTexture(texture);
			break;
		case 2:
			//�ڶ����������ú��
			texture = Director::getInstance()->getTextureCache()->addImage("Gamemap/wave_2.png");
			// �����µ�����  
			wave->setTexture(texture);
			schedule(schedule_selector(GameMap1::init_m1), 1, 4, 1);
			break;
		case 3:
			//�����������С����
			texture = Director::getInstance()->getTextureCache()->addImage("Gamemap/wave_3.png");
			// �����µ�����  
			wave->setTexture(texture);
			schedule(schedule_selector(GameMap1::init_m2), 1, 4, 1);
			break;
		case 4:
			//���Ĳ����������
			texture = Director::getInstance()->getTextureCache()->addImage("Gamemap/wave_4.png");
			// �����µ�����  
			wave->setTexture(texture);
			schedule(schedule_selector(GameMap1::init_m3), 1, 4, 1);
			break;
		case 5:
			texture = Director::getInstance()->getTextureCache()->addImage("Gamemap/wave_5.png");
			// �����µ�����  
			wave->setTexture(texture);
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
	if (current_wave >= 8)
		this->schedule(schedule_selector(GameMap1::next_bo), 0.05f);
	if (current_wave < 6)
		this->schedule(schedule_selector(GameMap1::next_bo), 3);
	else
	{
		this->scheduleOnce(schedule_selector(GameMap1::bo), 5);
	}
}

void GameMap1::next_bo(float a) {
	if (current_wave >= 8) {
		if (die_monsternum >= 35)
		{//-------------------todo:�ж���Ӯ�Ľӿ�--------------------------------------------------------------------------
			win();
			this->unschedule(schedule_selector(GameMap1::next_bo));
		}
	}
	else if (monsterContainer.empty())
	{
		this->unschedule(schedule_selector(GameMap1::next_bo));
		this->GameMap1::bo(0.1f);
	}
}

void GameMap1::win()
{
	auto winmenu = Sprite::create("GameMap/win.png");
	// ���ò˵�λ��
	winmenu->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
		Director::getInstance()->getVisibleSize().height * 2));
	this->addChild(winmenu, 200);
	// ִ�в˵����Ϸ��ƶ�������Ķ���
	auto moveAction = EaseBackOut::create(MoveTo::create(0.5f, Vec2(Director::getInstance()->getVisibleSize().width / 2,
		Director::getInstance()->getVisibleSize().height / 2)));
	winmenu->runAction(moveAction);

	//�����ķ���
	auto champion = Sprite::create("GameMap/champion.png");
	winmenu->addChild(champion);
	champion -> setPosition(Vec2(360, 400));

	//������Ϸ��ť
	auto continuebtn = Button::create("GameMap/continue.png", "GameMap/continue.png", "");
	winmenu->addChild(continuebtn);
	continuebtn->setPressedActionEnabled(true);
	continuebtn->setPosition(Vec2(360, 255));
	continuebtn->setScale(1.12);
	continuebtn->addClickEventListener([=](Ref* sender) {
		isGamePaused = false;
	auto gamemap2 = GameMap2::create();
	//removeAllChildrenWithCleanup(true);
	Director::getInstance()->replaceScene(gamemap2);
		});

	//ѡ��ؿ���ť
	auto chooselevelbtn = Button::create("GameMap/chooselevel.png", "GameMap/chooselevel.png", "");
	winmenu->addChild(chooselevelbtn);
	chooselevelbtn->setPressedActionEnabled(true);
	chooselevelbtn->setPosition(Vec2(360, 100));
	chooselevelbtn->setScale(1.12);
	chooselevelbtn->addClickEventListener([=](Ref* sender) {
		auto chooselevel = ChooseLevel::create();
	//removeAllChildrenWithCleanup(true);
	Director::getInstance()->replaceScene(chooselevel);
	//?????????????????�ٴν���Ῠס
		});


	// ʹ��Sequence���Ӷ����ͻص�����
	winmenu->runAction(Sequence::create(moveAction, CallFunc::create([this]() {
		// �ڶ���ִ�����ִ�еĻص�����
		// ��Ϸ��ͣ
		isGamePaused = true;
	Director::getInstance()->pause();
		}), nullptr));

}

void GameMap1::lose()
{
	auto losemenu = Sprite::create("GameMap/lose.png");
	// ���ò˵�λ��
	losemenu->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
		Director::getInstance()->getVisibleSize().height * 2));
	this->addChild(losemenu, 200);
	// ִ�в˵����Ϸ��ƶ�������Ķ���
	auto moveAction = EaseBackOut::create(MoveTo::create(0.5f, Vec2(Director::getInstance()->getVisibleSize().width / 2,
		Director::getInstance()->getVisibleSize().height / 2)));
	losemenu->runAction(moveAction);


	//���¿�ʼ��Ϸ��ť
	auto restartbtn = Button::create("GameMap/restart.png", "GameMap/restart.png", "");
	losemenu->addChild(restartbtn);
	restartbtn->setPressedActionEnabled(true);
	restartbtn->setPosition(Vec2(360, 300));
	restartbtn->setScale(1.12);
	restartbtn->addClickEventListener([=](Ref* sender) {
		isGamePaused = false;
	auto gamemap1 = GameMap1::create();
	//removeAllChildrenWithCleanup(true);
	Director::getInstance()->replaceScene(gamemap1);
		});

	//ѡ��ؿ���ť
	auto chooselevelbtn = Button::create("GameMap/chooselevel.png", "GameMap/chooselevel.png", "");
	losemenu->addChild(chooselevelbtn);
	chooselevelbtn->setPressedActionEnabled(true);
	chooselevelbtn->setPosition(Vec2(360, 150));
	chooselevelbtn->setScale(1.12);
	chooselevelbtn->addClickEventListener([=](Ref* sender) {
		auto chooselevel = ChooseLevel::create();
	//removeAllChildrenWithCleanup(true);
	Director::getInstance()->replaceScene(chooselevel);
	//?????????????????�ٴν���Ῠס
		});


	// ʹ��Sequence���Ӷ����ͻص�����
	losemenu->runAction(Sequence::create(moveAction, CallFunc::create([this]() {
		// �ڶ���ִ�����ִ�еĻص�����
		// ��Ϸ��ͣ
		isGamePaused = true;
	Director::getInstance()->pause();
		}), nullptr));

}