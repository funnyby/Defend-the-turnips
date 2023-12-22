#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Way.h"
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


class Monster : public cocos2d::CCSprite
{
public:
    void initmonster();
    //是否死亡
    bool isDie;
private:
    //生命值
    CC_SYNTHESIZE(float, _hp, HP);
    //行走速度
    CC_SYNTHESIZE(float, _walkSpeed, WalkSpeed);
    //伤害值
    CC_SYNTHESIZE(float, _damage, Damage);
    //金钱
    CC_SYNTHESIZE(float, _money, Money);
    //冰冻
    CC_SYNTHESIZE(float, _freeze, Freeze);
    //精灵序号，为每种精灵编一个序号
    int _spriteIndex;
    //GameMediator* m;
    //当前精灵的位置
    cocos2d::Point myPosition;
    //开始路点
    cocos2d::Point beginningWaypoint;
    //结束路点
    cocos2d::Point destinationWaypoint;
    //是否成功咬了萝卜
    void BiteTurnips();

    CREATE_FUNC(Monster);
};
