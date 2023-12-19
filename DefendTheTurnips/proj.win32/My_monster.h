#pragma once
#include "cocos2d.h"

class Monster : public cocos2d::CCSprite
{
public:
    void initmonster();
    //是否死亡
    bool isDie;
    //void update(float delta);
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
};
