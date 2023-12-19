#pragma once
/*
this class rises form CCSprite
all characters' actions base on this class
cited from:https://www.cnblogs.com/hll2008/p/4266776.html
this first version created by wsy for monsters class setup on 23.12.17
also fby create it for carrots class on 23.12.18

*/
#ifndef __ACTION_SPRITE_H_
#define __ACTION_SPRITE_H_
#include "cocos2d.h"
using namespace cocos2d;

typedef enum _ActionState {
    kActionStateNone = 0, //��״̬
    kActionStateIdle, //��ֹ״̬
    kActionStateWalk, //����״̬
    kActionStateDeath //����״̬
}ActionState;

class ActionSprite : public cocos2d::CCSprite
{
public:
    ActionSprite(void);
    ~ActionSprite(void);
    //��ֹ
    void idle();
    //����
    void death();
    //����
    void walk();
    //�۸�
    CC_SYNTHESIZE(int, _price, Price);
    //����ֵ
    CC_SYNTHESIZE(float, _hp, HP);
    //��ֹ״̬����
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _idleAction, IdleAction);
    //����״̬����
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _deathAction, DeathAction);
    //����״̬����
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _walkAction, WalkAction);
    //��ǰ����״̬
    CC_SYNTHESIZE(ActionState, _actionState, ActionState);
    //�����ٶ�
    CC_SYNTHESIZE(float, _walkSpeed, WalkSpeed);
    //�˺�ֵ
    CC_SYNTHESIZE(float, _damage, Damage);
    //��Ǯ
    CC_SYNTHESIZE(float, _money, Money);
    //�Ƿ��й⻷
    CC_SYNTHESIZE(bool, _halo, Halo);

};
#endif //__ACTION_SPRITE_H_