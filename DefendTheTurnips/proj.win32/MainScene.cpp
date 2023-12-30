#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "ChooseLevel.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
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
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/BackGroundMusic/StartBGMusic.mp3");

	// 播放音乐
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/BackGroundMusic/StartBGMusic.mp3", true);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//背景
	Sprite* rootNode = nullptr;
	InitSprite(rootNode, this, "MainMenu/zh/front_bg.png", origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2, -1);
	if (nullptr == rootNode)
		return false;

	//开始冒险按钮
	auto startGameBtn = Button::create("MainMenu/zh/front_btn_start_normal.png", "MainMenu/zh/front_btn_start_pressed.png", "null.png");
	if (nullptr == startGameBtn)
		problemLoading("MainMenu/zh/front_btn_start_normal.png||MainMenu/zh/front_btn_start_pressed.png");
	else
	{
		startGameBtn->setPosition(Vec2(origin.x + 562, origin.y + 395));
		this->addChild(startGameBtn, 1);

		//触摸事件
		startGameBtn->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
			switch (type)
			{
				case ui::Widget::TouchEventType::BEGAN:
				{
					//SimpleAudioEngine::getInstance()->playEffect("Sound/MainMenu/Select.mp3", false, 1.0f, 1.0f, 1.0f);
					break;
				}
				case ui::Widget::TouchEventType::ENDED:
				{
					//log("_startGameBtn ENDERD");
					 //跳转场景
					auto chooseLevel = ChooseLevel::createScene();
					Director::getInstance()->replaceScene(chooseLevel);
					break;
				}
				default:
					break;
			}
			});

	}


	return true;
}

bool MainScene::init()
{
	if (!InitUI())
		return false;

	//0.5秒后调用startGame方法
	//this->schedule(schedule_selector(MainScene::startGame), 0.5f);

	return true;
}
