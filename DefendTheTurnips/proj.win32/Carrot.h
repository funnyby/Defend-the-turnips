#pragma once
#include "ActionSprite.h"
#include "cocos2d.h"

using namespace cocos2d;
class Carrots :public ActionSprite
{
public:
	Carrots();
	~Carrots();
	
	CREATE_FUNC(Carrots);

	virtual bool init();
};