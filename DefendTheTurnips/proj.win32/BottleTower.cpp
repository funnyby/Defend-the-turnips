#include "..\Classes\Tower\BottleTower.h"

BottleTower::BottleTower()
{

}

BottleTower* BottleTower::create(const std::string& towerImage)
{
    BottleTower* tower = new BottleTower();
    if (tower && tower->init(towerImage))
    {
        tower->autorelease();
        return tower;
    }
    else
    {
        delete tower;
        return nullptr;
    }
}


bool BottleTower::init(const std::string& towerImage)
{
    if (!Tower::init(towerImage))
    {
        return false;
    }

    // �����������������еĳ�ʼ����Ϊ

    return true;
}

void BottleTower::performAttack()
{
    // ����ʵ���������еĹ�����Ϊ
    // ���磬�����ڵ���������ըЧ����
    CCLOG("Cannon Tower attacks!");
    // ...
}
