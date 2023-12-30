#include "SunTower.h"

SunTower::SunTower()
{

}

SunTower* SunTower::create(const std::string& towerImage)
{
    SunTower* tower = new SunTower();
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


bool SunTower::init(const std::string& towerImage)
{
    if (!Tower::init(towerImage))
    {
        return false;
    }

    // 这里可以添加炮塔特有的初始化行为

    return true;
}

void SunTower::performAttack()
{
    // 这里实现炮塔特有的攻击行为
    // 例如，发射炮弹、产生爆炸效果等
    CCLOG("Cannon Tower attacks!");
    // ...
}
