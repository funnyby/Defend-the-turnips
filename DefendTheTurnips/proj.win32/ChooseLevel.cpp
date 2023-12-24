#include "ChooseLevel.h"
#include "MainScene.h"
#include"EnterScene.h"
#include<vector>

USING_NS_CC;
using namespace cocos2d::ui;
using namespace std;


//ö�٣����б����Ÿ���ڵ�Ĳ㼶������ʹ�ø���ڵ�Ĳ㼶���ڹ���
enum zOrderMap
{
	route = 1,//��·�㼶
	routeButtonEffect = 5,//��ť��Ч�㼶
	levelButton = 10//��ť�㼶
};

cocos2d::Scene* ChooseLevel::createScene()
{
	return ChooseLevel::create();
}

//ѡ��ؿ������ʼ��
//��ChooseLevel���е�init()�����е�����Щ����
bool ChooseLevel::init()
{
	if (!Scene::init())
		return false;

	InitUI();

	InitEvent();

	return true;
}

//UI���ʼ��
void ChooseLevel::InitUI()
{
	//������������
	auto scrollView = ScrollView::create();
	//���ù�������
	scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
	//���������¼�
	scrollView->setTouchEnabled(true);
	//�������ݴ�С
	scrollView->setContentSize(Director::getInstance()->getVisibleSize());
	//���ع�����
	scrollView->setScrollBarEnabled(false);
	this->addChild(scrollView);

	//����������ͼ
	Sprite* imageView = NULL;
	string filePath;
	float nextPosX = 0.f;
	for (int i = 1; i <= page_num; i++)
	{
		filePath = "ChooseLevel/chooselevel" + to_string(i) + ".png";
		imageView = Sprite::create(filePath);
		//����ê�㣿
		imageView->setAnchorPoint(Vec2(0, 0.5));
		imageView->setPosition(nextPosX, Director::getInstance()->getVisibleSize().height / 2);
		nextPosX += imageView->getContentSize().width;
		scrollView->addChild(imageView);
	}
	//����ScrollView�Ĳ���������С
	scrollView->setInnerContainerSize(Size(nextPosX, Director::getInstance()->getVisibleSize().height));


	//UI��ť�ؼ�
	auto layerUI = Layer::create();
	this->addChild(layerUI);
	auto leftPanelPinfo = AutoPolygon::generatePolygon("ChooseLevel/stagemap_toolbar_leftbg.png");
	//�ñ���ͼʼ������Ļ�����Ͻ�
	auto leftPanel = Sprite::create(leftPanelPinfo);
	leftPanel->setAnchorPoint(Vec2(0, 1));
	leftPanel->setPosition(0, Director::getInstance()->getVisibleSize().height);
	leftPanel->setScale(float(0.7));
	layerUI->addChild(leftPanel);

	//��������ͼ������ӽڵ㣨������ť��
	string toolbarHomeFilePath = "ChooseLevel/stagemap_toolbar_home.png";
	_toolbarHome = Button::create(toolbarHomeFilePath, toolbarHomeFilePath, "");
	_toolbarHome->setAnchorPoint(Vec2(0, 0));
	_toolbarHome->setPosition(Vec2(10, 10));
	_toolbarHome->setPressedActionEnabled(true);
	leftPanel->addChild(_toolbarHome);

	string toolbarShopFilePath = "ChooseLevel/stagemap_toolbar_shop.png";
	_toolbarShop = Button::create(toolbarShopFilePath, toolbarShopFilePath, "");
	_toolbarShop->setAnchorPoint(Vec2(0, 0));
	_toolbarShop->setPosition(Vec2(125, 10));
	_toolbarShop->setPressedActionEnabled(true);
	leftPanel->addChild(_toolbarShop);

	string toolbarLeaderboardFilePath = "ChooseLevel/stagemap_toolbar_leaderboard.png";
	_toolbarLeaderboard = Button::create(toolbarLeaderboardFilePath, toolbarLeaderboardFilePath, "");
	_toolbarLeaderboard->setAnchorPoint(Vec2(0, 0));
	_toolbarLeaderboard->setPosition(Vec2(235, 10));
	_toolbarLeaderboard->setPressedActionEnabled(true);
	leftPanel->addChild(_toolbarLeaderboard);

	TMXTiledMap* map = TMXTiledMap::create("ChooseLevel/tiledmap.tmx");
	//��ȡ��Ƭ��ͼ�е�point�����
	auto objectGroup = map->getObjectGroup("point");
	//��������е����ж����ȡ����
	auto objs = objectGroup->getObjects();
	//��������
	for (unsigned int i = 0; i < objs.size(); i++)
	{
		//ͼƬ����
		string texture = "ChooseLevel/stagepoint_adv.png";

		//������Ƭ��ͼ��λ��������Ϣ���ùؿ���ť
		auto button = Button::create(texture, texture, "null.png");
		scrollView->addChild(button, zOrderMap::levelButton, i);
		std::vector<cocos2d::ui::Button*> routeButtonArray;
		routeButtonArray.push_back(button);

		auto valueMap = objs[i].asValueMap();//�������ֵ��Valueת����ValueMap
	
		//��ť��λ������
		button->setPosition(Vec2(valueMap["x"].asFloat(), valueMap["y"].asFloat()));//��ȡ���������:(asһ��ķ��� ��ת�����ͣ�
		//���ð�ťTag�ǳ���Ҫ��ʵ���Ͼ��ǵ�ǰ�ؿ�����������0��ʼ����0��ʾ��1�أ�1��ʾ��2�أ��Դ����ơ�
		button->setTag(i);
		button->setScale(1.0);//����С
		button->setPressedActionEnabled(true);

		if (i == 0) {
			//�����¼�������
			button->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
				if (type == ui::Widget::TouchEventType::ENDED)
				{
					//��ǰ�ؿ��ȼ�������Tagֵ���ض�Ӧ�ؿ�������
					log("hello %d", ((Button*)sender)->getTag());

					
					 //��ת����
					auto enterscene = EnterScene::createScene();
					Director::getInstance()->replaceScene(enterscene);
				}
				});
		}
	}
}
//�ײ��¼����ʼ��
void ChooseLevel::InitEvent()
{
	//��ʼ����ҳ��ť���̵갴ť�����а�ť�������¼�
	_toolbarHome->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			auto mainScene = MainScene::createScene();
			Director::getInstance()->replaceScene(mainScene);
		}
		});

}


static void problemLoading(const char* filename)
{
	printf("Error while loading:%s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in ChooseLevel.cpp\n");
}
