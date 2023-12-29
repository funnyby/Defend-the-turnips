#include "EnterScene.h"
#include "SimpleAudioEngine.h"
#include "ChooseLevel.h"
#include "GameMap1.h"
USING_NS_CC;
using namespace cocos2d::ui;

cocos2d::Scene* EnterScene::createScene()
{
	return EnterScene::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading:%s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in EnterScene.cpp\n");
}

bool EnterScene::init()
{
	if (!InitUI())
		return false;

	return true;
}

bool EnterScene::InitUI()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// 添加背景
	auto background = Sprite::create("EnterScene/enterscene1.png");  // 使用你的背景图片文件名
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	// 计算缩放比例，以适应屏幕
	float scaleX = visibleSize.width / background->getContentSize().width;
	float scaleY = visibleSize.height / background->getContentSize().height;

	// 设置精灵的缩放
	background->setScale(scaleX, scaleY);
	this->addChild(background);

	// 在这里可以添加其他场景元素，如角色、按钮等
	

	//添加返回上一界面按钮
	auto returnBtn = Button::create("EnterScene/return1.png", "EnterScene/return1.png", "null.png");
	returnBtn->setPosition(Vec2(origin.x + 45, origin.y + 607));
	returnBtn->setPressedActionEnabled(true);
	this->addChild(returnBtn, 1);

	//触摸事件
	returnBtn->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
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
		
	//添加开始游戏按钮
	auto startBtn = Button::create("EnterScene/startbtn1.png", "EnterScene/startbtn1.png", "null.png");
	startBtn->setPosition(Vec2(origin.x + 562, origin.y + 75));
	startBtn->setPressedActionEnabled(true);
	this->addChild(startBtn, 1);

	//触摸事件
	startBtn->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
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
				auto GameMap = GameMap1::createScene();
				Director::getInstance()->replaceScene(GameMap);
				break;
			}
			default:
				break;
		}
		});

	return true;
}