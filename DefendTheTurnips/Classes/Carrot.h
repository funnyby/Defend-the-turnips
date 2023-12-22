#ifndef __CARROT_H_
#define __CARROT_H_
#include "cocos2d.h"
#include "ActionSprite.h"
using namespace cocos2d;
class Carrot :public ActionSprite
{
public:
	Carrot();
	~Carrot();

	CREATE_FUNC(Carrot);

	virtual bool init();

	virtual bool initWithLocation(Point location);

	Rect getRect();
private:
	ActionSprite *_mySprite;
};
#endif // __CHOOSE_LEVEL_H__