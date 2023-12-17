#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class MainScene :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(MainScene);
private:
	void InitSprite(cocos2d::Sprite*& outSprite, cocos2d::Node* parentNode, const std::string& fileName, float x, float y, int localZOrder);

	bool InitUI();
};
