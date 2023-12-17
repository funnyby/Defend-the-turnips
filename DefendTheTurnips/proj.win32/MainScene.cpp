#include "MainScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
using namespace cocos2d::ui;

cocos2d::Scene* MainScene::createScene()
{
	return MainScene::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading:%s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MainScene.cpp\n");
}


void MainScene::InitSprite(cocos2d::Sprite*& outSprite, cocos2d::Node* parentNode, const std::string& fileName, float x, float y, int localZOrder)
{
	if (fileName == "MainMenu/front_front.png" || fileName == "MainMenu/front_smoke_3.png" || fileName == "MainMenu/front_smoke_1.png")
		outSprite = Sprite::create(fileName);
	else
	{
		auto pinfo = AutoPolygon::generatePolygon(fileName);
		outSprite = Sprite::create(pinfo);
	}
	if (nullptr == outSprite)
	{
		outSprite = nullptr;
		problemLoading(fileName.c_str());
		return;
	}
	outSprite->setPosition(Vec2(x, y));
	parentNode->addChild(outSprite, localZOrder);
}

bool MainScene::InitUI()
{
	if (!Scene::init())
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//±³¾°
	Sprite* rootNode = nullptr;
	InitSprite(rootNode, this, "MainMenu/zh/front_bg.png", origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2, -1);
	if (nullptr == rootNode)
		return false;

	//Ç°ÖÃ±³¾°
	/*
	Sprite* frontNode = nullptr;
	InitSprite(frontNode, this, "MainMenu/front_front.png", origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2, 3);
	if (nullptr == frontNode)
		return false;
		*/

	//¿ªÊ¼Ã°ÏÕ°´Å¥
	auto startGameBtn = Button::create("MainMenu/zh/front_btn_start_normal.png", "MainMenu/zh/front_btn_start_pressed.png", "null.png");
	if (nullptr == startGameBtn)
		problemLoading("MainMenu/zh/front_btn_start_normal.png||MainMenu/zh/front_btn_start_pressed.png");
	else
	{
		startGameBtn->setPosition(Vec2(origin.x + 562, origin.y + 395));
		this->addChild(startGameBtn, 1);
	}

	/*
	//Monster4
	Sprite* monster4 = nullptr;
	InitSprite(monster4, this, "MainMenu/front_monster_4.png", origin.x + 227, origin.y + 475, 1);
	if (nullptr == monster4)
		return false;
	monster4->setScale(0.75);

	//ÉèÖÃ°´Å¥
	auto setUpBtn = Button::create("MainMenu/front_btn_setting_normal.png", "MainMenu/front_btn_setting_pressed.png", "null.png");
	if (nullptr == setUpBtn)
		problemLoading("MainMenu/front_btn_setting_normal.png||MainMenu/front_btn_setting_pressed.png");
	else
	{
		monster4->addChild(setUpBtn, 1);
		setUpBtn->setPosition(Vec2(176, 89));
	}

	//±£ÎÀµÄÂÜ²·
	Sprite* carrot = nullptr;
	InitSprite(carrot, this, "MainMenu/front_carrot.png", origin.x + 620, origin.y + 14, 2);
	if (nullptr == carrot)
		return false;
	carrot->setScale(0.75);

	//Monster6
	Sprite* monster6 = nullptr;
	InitSprite(monster6, this, "MainMenu/front_monster_6.png", origin.x + 995, origin.y + 248, 1);
	if (nullptr == monster6)
		return false;
	monster6->setScale(0.75);
	//Monster6Hand
	Sprite* monster6Hand = nullptr;
	InitSprite(monster6Hand, this, "MainMenu/front_monster_6_hand.png", origin.x + 894, origin.y + 256, -1);
	if (nullptr == monster6Hand)
		return false;
	monster6Hand->setScale(0.75);

	//´ðÒÉ°´Å¥
	auto confuseBtn = Button::create("MainMenu/front_btn_help_normal.png", "MainMenu/front_btn_help_pressed.png", "null.png");
	if (nullptr == confuseBtn)
		problemLoading("MainMenu/front_btn_help_normal.png||MainMenu/front_btn_help_pressed.png");
	else
	{
		monster6Hand->addChild(confuseBtn, 0);
		confuseBtn->setPosition(Vec2(170, 405));
	}


	//Monster5
	Sprite* monster5 = nullptr;
	InitSprite(monster5, this, "MainMenu/front_monster_5.png", origin.x + 882, origin.y + 155, 1);
	if (nullptr == monster5)
		return false;
	monster5->setScale(0.75);


	//ÑÌÎí2
	Sprite* smoke2 = nullptr;
	InitSprite(smoke2, this, "MainMenu/front_smoke_3.png", origin.x + 1020, origin.y + 165, 1);
	if (nullptr == smoke2)
		return false;


	//Monster3
	Sprite* monster3 = nullptr;
	InitSprite(monster3, this, "MainMenu/front_monster_3.png", origin.x + 160, origin.y + 190, 1);
	if (nullptr == monster3)
		return false;
	monster3->setScale(0.75);


	//Monste1
	Sprite* monster1 = nullptr;
	InitSprite(monster1, this, "MainMenu/front_monster_1.png", origin.x + 230, origin.y + 155, 1);
	if (nullptr == monster1)
		return false;
	monster1->setScale(0.85);


	//ÑÌÎí1
	Sprite* smoke1 = nullptr;
	InitSprite(smoke1, this, "MainMenu/front_smoke_1.png", origin.x + 120, origin.y + 170, 1);
	if (nullptr == smoke1)
		return false;

	//Monster2
	Sprite* monster2 = nullptr;
	InitSprite(monster2, this, "MainMenu/front_monster_2.png", origin.x + 342, origin.y + 140, 1);
	if (nullptr == monster2)
		return false;
	monster2->setScale(0.75);*/
	return true;
}

bool MainScene::init()
{
	if (!InitUI())
		return false;

	return true;
}
