#pragma once

#ifndef __SUN_TOWER_H__
#define __SUN_TOWER_H__

#include "..\Classes\Tower\Tower.h"

class SunTower : public Tower
{
public:
    // ��������
    static SunTower* create(const std::string& towerImage);

    // ���캯��
    SunTower();

    // ��ʼ������
    virtual bool init(const std::string& towerImage) override;

    // ��д����Ĺ�����Ϊ
    virtual void performAttack() override;
    void update(float d);

};

#endif  __SUN_TOWER_H__
