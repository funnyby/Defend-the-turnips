#pragma once

#ifndef __SHITTOWER_TOWER_H__
#define __SHITTOWER_TOWER_H__

#include "Tower.h"

class ShitTower : public Tower
{
public:
    // 创建炮塔
    static ShitTower* create(const std::string& towerImage);

    // 构造函数
    ShitTower();

    // 初始化炮塔
    bool init(const std::string& towerImage) override;

    // 重写父类的攻击行为
    void performAttack() override;

   
};

#endif  __SHITTOWER_TOWER_H__
