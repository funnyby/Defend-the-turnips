#include "Tower.h"

USING_NS_CC;


Tower::Tower()
    : state(TowerState::IDLE),
    target(nullptr),
    attackRange(100.0f),
    attackInterval(2.0f),
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

    return true;
}

void Tower::setTarget(Sprite* target)
{
    this->target = target;
}

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

void Tower::startAttack()
{
    state = TowerState::ATTACKING;
}

void Tower::stopAttack()
{
    state = TowerState::IDLE;
}

float Tower::getAttackRange() const
{
    return attackRange;
}

bool Tower::isTargetInRange() const
{
    if (target)
    {
        float distance = this->getPosition().getDistance(target->getPosition());
        return distance <= attackRange;
    }
    return false;
}

void Tower::performAttack()
{
    // 在这里执行防御塔的攻击逻辑，可以创建子弹、特效等

    // 示例：简单地输出一条信息
    CCLOG("Tower attacks the target!");
}
