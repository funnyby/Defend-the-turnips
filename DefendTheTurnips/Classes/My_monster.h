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
    //�Ƿ�����
    bool isDie;
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
    //�Ƿ�ɹ�ҧ���ܲ�
    void BiteTurnips();

    CREATE_FUNC(Monster);
};
