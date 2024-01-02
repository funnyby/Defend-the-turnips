#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Carrot.h"
#include "..\Classes\Barrier\Barrier.h"
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
    int mapNum;
    //�����Ƿ񻹻���
    bool isAlive;
    virtual void update(float dt);
    void initMonsterType1();
    void initMonsterType2();
    void initMonsterType3();
    //�Ƿ����ˣ��ӵ�ÿ�ι���ʱ���øú���
    void beHurt(int monster_blood, int type);
    bool choosed;
    bool beShoot=0;
    Sprite* choice;
private:
    Sprite* bloodBox;
    Sprite* beHit;
    Sprite* sprBlood;
    Sprite* freeze;
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
    int BLOOD_BAR_m;
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
    void deletebehit(float a);
    CREATE_FUNC(Monster);
};

extern cocos2d::Vector<Monster*> monsterContainer;
extern int monsternum;
extern int die_monsternum;
extern bool choose_a_object;