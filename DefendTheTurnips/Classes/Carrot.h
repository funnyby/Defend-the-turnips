#ifndef __CARROT_H_
#define __CARROT_H_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ActionSprite.h"
using namespace cocos2d;
#define CREATE_FUNC(__TYPE__) \
static __TYPE__* create() \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
    if (pRet && pRet->init()) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}


class Carrot :public ActionSprite
{
public:

	bool init();
    //void whenTouched();
    void beBiten();
    bool GameOver();
    void setLocation(Point mapDest);
private:
    Point location;
    //生命值
    CC_SYNTHESIZE(float, _hp, HP);
    //当前精灵的位置

    CREATE_FUNC(Carrot);
};
#endif // __CHOOSE_LEVEL_H__