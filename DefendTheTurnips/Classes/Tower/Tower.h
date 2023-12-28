#pragma once
#ifndef __TOWER_H__
#define __TOWER_H__

#include "cocos2d.h"

class Tower : public cocos2d::Sprite
{
public:

    // �������ĵȼ�
    int level;
    //��������λ��
    int pos_i, pos_j;


    // ��������״̬
    enum class TowerState
    {
        IDLE,     // ����״̬
        ATTACKING // ����״̬
    };

    // ���캯��
    Tower();

    // ��ʼ��������
    virtual bool init(const std::string& towerImage);

    // ����������
    static Tower* create(const std::string& towerImage);

    // ���÷������Ĺ���Ŀ��
    void setTarget(cocos2d::Sprite* target);

    // ���·��������߼�
    void update(float dt) override;

    // ��ʼ����
    void startAttack();

    // ֹͣ����
    void stopAttack();

    // ��ȡ�������Ĺ�����Χ
    float getAttackRange() const;


   

private:
    // ��������״̬
    TowerState state;

    // �������Ĺ���Ŀ��
    cocos2d::Sprite* target;

    // �������Ĺ�����Χ
    float attackRange;

    // �������Ĺ������
    float attackInterval;

    // ��ʱ�������ڿ��ƹ������
    float attackTimer;

    

    // ���Ŀ���Ƿ��ڹ�����Χ��
    bool isTargetInRange() const;

    // ִ�й�������
    virtual void performAttack();
};

#endif __TOWER_H__
