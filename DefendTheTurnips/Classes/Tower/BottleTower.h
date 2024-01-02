#pragma once

#ifndef __BOTTLETOWER_TOWER_H__
#define __BOTTLETOWER_TOWER_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Tower.h"

class BottleTower : public Tower
{
public:

    // ��������
    static BottleTower* create(const std::string& towerImage);

    // ���캯��
    BottleTower();


    // ��ʼ������
    bool init(const std::string& towerImage) override;

    // ��д����Ĺ�����Ϊ
    void performAttack() override;
    void update(float d);

};

#endif  __BOTTLETOWER_TOWER_H__
