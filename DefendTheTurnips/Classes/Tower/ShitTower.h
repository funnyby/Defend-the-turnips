#pragma once

#ifndef __SHIT_TOWER_H__
#define __SHIT_TOWER_H__

#include "Tower.h"

class ShitTower : public Tower
{
public:
    // ��������
    static ShitTower* create(const std::string& towerImage);

    // ���캯��
    ShitTower();

    // ��ʼ������
    virtual bool init(const std::string& towerImage) override;

    // ��д����Ĺ�����Ϊ
    virtual void performAttack() override;

    void update(float d);
};

#endif  __SHITTOWER_TOWER_H__
