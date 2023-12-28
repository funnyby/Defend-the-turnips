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

    // ��ʼ����������

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
            // ִ�й�������
            performAttack();

            // ���ü�ʱ��
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
    // ������ִ�з������Ĺ����߼������Դ����ӵ�����Ч��

    // ʾ�����򵥵����һ����Ϣ
    CCLOG("Tower attacks the target!");
}
