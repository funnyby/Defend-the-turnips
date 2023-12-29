#pragma once
#ifndef __TOWER_H__
#define __TOWER_H__

#include "cocos2d.h"

class Tower : public cocos2d::Sprite
{
public:

    // 防御塔的等级
    int level;
    //防御塔的位置
    int pos_i, pos_j;


    // 防御塔的状态
    enum class TowerState
    {
        IDLE,     // 空闲状态
        ATTACKING // 攻击状态
    };

    // 构造函数
    Tower();

    // 初始化防御塔
    virtual bool init(const std::string& towerImage);

    // 创建防御塔
    static Tower* create(const std::string& towerImage);

    // 设置防御塔的攻击目标
    void setTarget(cocos2d::Sprite* target);

    // 更新防御塔的逻辑
    void update(float dt) override;

    // 开始攻击
    void startAttack();

    // 停止攻击
    void stopAttack();

    // 获取防御塔的攻击范围
    float getAttackRange() const;


   

private:
    // 防御塔的状态
    TowerState state;

    // 防御塔的攻击目标
    cocos2d::Sprite* target;

    // 防御塔的攻击范围
    float attackRange;

    // 防御塔的攻击间隔
    float attackInterval;

    // 计时器，用于控制攻击间隔
    float attackTimer;

    

    // 检测目标是否在攻击范围内
    bool isTargetInRange() const;

    // 执行攻击动作
    virtual void performAttack();
};

#endif __TOWER_H__
