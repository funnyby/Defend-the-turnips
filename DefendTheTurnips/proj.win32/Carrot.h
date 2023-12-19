#ifndef __CARROT_H_
#define __CARROT_H_
#include "cocos2d.h"

using namespace cocos2d;
class Carrots :public Sprite
{
public:
	Carrots();
	~Carrots();

	CREATE_FUNC(Carrots);

	virtual bool init();

	virtual bool initWithLocation(Point location);

	Rect getRect();
private:
	CC_SYNTHESIZE_RETAIN(ActionSprite*, _mySprite, MySprite);
};
#endif // __CHOOSE_LEVEL_H__