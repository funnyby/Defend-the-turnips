#pragma once
#ifndef __TOWER_H__
#define __TOWER_H__

#include "cocos2d.h"
#include"..\Classes\Monster\My_monster.h";

class Tower : public cocos2d::Sprite
{
public:

    // �������ĵȼ�
    int level;
    //�������ڵ�ͼ�����ϵ�λ��
    int pos_i, pos_j;
    //������Χ
    int attackrange;

    //--------------------------------------
    Vec2 my_pos;//������λ��
    Vec2 target_pos;//����Ŀ���λ��
    //--------------------------------------
    // ��������״̬
    enum class TowerState
    {
        IDLE,     // ����״̬
        ATTACKING // ����״̬
    };
    // ��������״̬
    TowerState state;

    // �������Ĺ������
    float attackInterval;

    // ��ʱ�������ڿ��ƹ������
    float attackTimer;



    // ���캯��
    Tower();

    // ��ʼ��������
    virtual bool init(const std::string& towerImage);

    // ����������
    static Tower* create(const std::string& towerImage);

    // ���·��������߼�
    void update(float dt) override;


    // ���Ŀ���Ƿ��ڹ�����Χ��
    bool isTargetInRange() ;

    // ִ�й�������
    virtual void performAttack();
};

#endif __TOWER_H__
