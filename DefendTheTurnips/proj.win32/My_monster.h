#pragma once
#include "cocos2d.h"

class Monster : public cocos2d::CCSprite
{
public:
    void initmonster();
    //�Ƿ�����
    bool isDie;
    //void update(float delta);
private:
    //����ֵ
    CC_SYNTHESIZE(float, _hp, HP);
    //�����ٶ�
    CC_SYNTHESIZE(float, _walkSpeed, WalkSpeed);
    //�˺�ֵ
    CC_SYNTHESIZE(float, _damage, Damage);
    //��Ǯ
    CC_SYNTHESIZE(float, _money, Money);
    //����
    CC_SYNTHESIZE(float, _freeze, Freeze);
    //������ţ�Ϊÿ�־����һ�����
    int _spriteIndex;
    //GameMediator* m;
    //��ǰ�����λ��
    cocos2d::Point myPosition;
    //��ʼ·��
    cocos2d::Point beginningWaypoint;
    //����·��
    cocos2d::Point destinationWaypoint;
};
