#pragma once

#ifndef __SUN_TOWER_H__
#define __SUN_TOWER_H__

#include "..\Classes\Tower\Tower.h"

class SunTower : public Tower
{
public:
    // 创建炮塔
    static SunTower* create(const std::string& towerImage);

    // 构造函数
    SunTower();

    // 初始化炮塔
    bool init(const std::string& towerImage) override;

    // 重写父类的攻击行为
    void performAttack() override;


};

#endif  __SUN_TOWER_H__
