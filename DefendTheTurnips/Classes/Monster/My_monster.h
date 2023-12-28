#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include"EnterScene.h"
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
    //�����Ƿ񻹻���
    bool isalive;
    virtual void update(float dt);
    void initmonster_type1();
    void initmonster_type2();
    void initmonster_type3();
    //�Ƿ����ˣ��ӵ�ÿ�ι���ʱ���øú���
    void behurt(float a);
    //void behurt(int monster_blood);
private:
    Sprite* bloodbox;
    Sprite* choice;
    bool choosed;
    //��Ѫ��
    int hp_total;
    int freeze_total;
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
    int BLOOD_BAR;
    //������ţ�Ϊÿ�־����һ�����
    int _spriteIndex;
    //GameMediator* m;
    //��ǰ�����λ��
    cocos2d::Point myPosition;
    //��ǰ�ߵ��ڼ��������
    int waypoint;
    //��ʼ·��
    cocos2d::Point beginningWaypoint;
    //����·��
    cocos2d::Point destinationWaypoint;
    //�Ƿ�ɹ�ҧ���ܲ�
    void BiteTurnips();
    //�Ƿ�����
    bool isDie();
    //�Ƿ񱻱���
    bool isFreezed();
    //����Ѫ������ͼ
    void create_Health_bar();
    //Ѫ��������Ѫ���ı�
    void scheduleBlood();
    //��ʱ��ȡ������Ч��
    void unFreezed(float a);
    //�����ƶ�
    void walk();
    //�жϹ����Ƿ�����һ�����
    bool judge_dest();
    //ɾ����ǰ������
    void deletemonster(float a);
    //�����Ƿ�ѡ��
    void touched();
    //ѡ�к����ͷ�Ϻ��
    void betouched();
    CREATE_FUNC(Monster);
};