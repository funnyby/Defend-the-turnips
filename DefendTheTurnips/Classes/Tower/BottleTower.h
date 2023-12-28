#pragma once

#ifndef __BOTTLETOWER_TOWER_H__
#define __BOTTLETOWER_TOWER_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Tower.h"

class BottleTower : public Tower
{
public:
    cocos2d::Sprite* range;
    cocos2d::ui::Button* upgradebtn;
    cocos2d::ui::Button* cancelbtn;
    cocos2d::Vec2 selectedPosition; // ѡ�е�λ��
    // ��������
    static BottleTower* create(const std::string& towerImage);

    // ���캯��
    BottleTower();
    

    // ��ʼ������
    bool init(const std::string& towerImage) override;

    // ��д����Ĺ�����Ϊ
    void performAttack() override;

};

#endif  __BOTTLETOWER_TOWER_H__
