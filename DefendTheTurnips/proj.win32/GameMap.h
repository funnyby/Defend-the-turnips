#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string.h>

class GameMap :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameMap);

private:
	bool InitUI();

	void InitEvent();

	void init_m(float delta);
};
#pragma once