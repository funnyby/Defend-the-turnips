#include "Tower.h"

USING_NS_CC;


Tower::Tower()
    : state(TowerState::IDLE),
    attackInterval(0.5f),//设置的初始攻击间隔是0.5s
    attackTimer(0.0f)
{
    level = 1;
}


Tower* Tower::create(const std::string& towerImage)
{
    Tower* tower = new Tower();
    if (tower && tower->init(towerImage))
    {
        tower->autorelease();
        return tower;
    }
    CC_SAFE_DELETE(tower);
    return nullptr;
}

bool Tower::init(const std::string& towerImage)
{
    if (!Sprite::initWithFile(towerImage))
    {
        return false;
    }
    // 初始化其他属性


    //----------------todo：攻击范围---可以再改一下，因为我是随便设的参数-----
    attackrange = 80 * 0.6 * (level + 3);


    return true;
}
//---------------------暂时没用基类的这个函数------------------
void Tower::update(float dt)
{
    if (state == TowerState::ATTACKING)
    {
        attackTimer += dt;

        if (attackTimer >= attackInterval)
        {
            // 执行攻击动作
            performAttack();

            // 重置计时器
            attackTimer = 0.0f;
        }
    }
}

bool Tower::isTargetInRange() 
{
    my_pos = getPosition();//获得我的位置

    for (auto barrier : BarrierContainer) {
        if (barrier->choosed) {
            target_pos = barrier->getPosition();
            float distance = my_pos.distance(target_pos);
            if (distance <= attackrange) {
                return true;
            }
        }
    }
    //有被选中的怪物
    for (auto target : monsterContainer) {
        if (target->choosed) {
            target_pos = target->getPosition();//获得目标位置
            float distance = my_pos.distance(target_pos);
            if (distance <= attackrange) {
                return true;
            }
        }
    }
    //什么也没有选中，就只攻击距离最近的怪物
    for (auto target : monsterContainer) {

        target_pos = target->getPosition();//获得目标位置
        float distance = my_pos.distance(target_pos);
        if (distance <= attackrange) {
            return true;
        }

    }

    return false;
}

void Tower::performAttack()
{
    // 在这里执行防御塔的攻击逻辑，可以创建子弹、特效等
    
    // 示例：简单地输出一条信息
    CCLOG("Tower attacks the target!");
}
