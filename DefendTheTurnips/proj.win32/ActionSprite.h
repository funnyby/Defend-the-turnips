#pragma once
#include "cocos2d.h"
//声明一个动作状态的枚举类型
typedef enum _ActionState {
    kActionStateNone = 0, //无状态
    kActionStateIdle, //静止状态
    kActionStateWalk, //行走状态
    kActionStateDeath //死亡状态
}ActionState;

class ActionSprite : public cocos2d::CCSprite
{
public:
    ActionSprite(void);
    ~ActionSprite(void);
    //静止
    void idle();
    //死亡
    void death();
    //行走
    void walk();
    //价格
    CC_SYNTHESIZE(int, _price, Price);
    //生命值
    CC_SYNTHESIZE(float, _hp, HP);
    //静止状态动作
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _idleAction, IdleAction);
    //死亡状态动作
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _deathAction, DeathAction);
    //行走状态动作
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _walkAction, WalkAction);
    //当前动作状态
    CC_SYNTHESIZE(ActionState, _actionState, ActionState);
    //行走速度
    CC_SYNTHESIZE(float, _walkSpeed, WalkSpeed);
    //伤害值
    CC_SYNTHESIZE(float, _damage, Damage);
    //金钱
    CC_SYNTHESIZE(float, _money, Money);
    //是否有光环
    CC_SYNTHESIZE(bool, _halo, Halo);

};