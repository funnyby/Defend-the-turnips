#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../Classes/Monster/My_monster.h"
#include <string.h>

class GameMap :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void deletemonster(Monster* m_MonsterSprite);

	CREATE_FUNC(GameMap);

private:
	int boshu;

	bool InitUI();

	void InitEvent();

	void init_m1(float delta);

	void init_m2(float delta);

	void init_m3(float delta);

	void bo(float a);

	void next_bo(float a);
};
#pragma once