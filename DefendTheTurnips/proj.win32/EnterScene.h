#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class EnterScene :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(EnterScene);
private:

	bool InitUI();
};
