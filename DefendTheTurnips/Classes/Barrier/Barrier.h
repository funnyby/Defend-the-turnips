#pragma once
#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Carrot.h"
#include "Way.h"

#include "../Classes/Monster/My_monster.h"
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




class Barrier : public cocos2d::CCSprite
{
public:
    //�����Ƿ񻹻���
    bool is_alive;
    virtual void update(float dt);
    //�Ƿ����ˣ��ӵ�ÿ�ι���ʱ���øú���
    void behurt(int monster_blood, int type);
    Sprite* choice;
    bool choosed;
    struct pos {
        int x;
        int y;
    };
    pos position[4] = { (0,0), (0,0), (0,0), (0,0) };
private:
    Sprite* bloodbox;
    Sprite* behit;
    Sprite* sprBlood;
    //��Ѫ��
    int hp_total;
    //����ֵ
    CC_SYNTHESIZE(float, _hp, HP);
    //��Ǯ
    CC_SYNTHESIZE(float, _money, Money);
    int BLOOD_BAR;
    //�Ƿ�����
    bool isDie();
    //����Ѫ������ͼ
    void create_Health_bar();
    //Ѫ��������Ѫ���ı�
    void scheduleBlood();
    //ɾ����ǰ������
    void deletemonster(float a);
    //�����Ƿ�ѡ��
    void touched();
    //ѡ�к����ͷ�Ϻ��
    void betouched();
    void deletebehit(float a);
    void initBarrier(int hp, int money, Texture2D* texture, Vec2 pos);
    void clear();
    CREATE_FUNC(Barrier);
};

extern cocos2d::Vector<Barrier*> BarrierContainer;