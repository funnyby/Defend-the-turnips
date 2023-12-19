#pragma once
#include "cocos2d.h"
//����һ������״̬��ö������
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