#include "Tower.h"

USING_NS_CC;


Tower::Tower()
    : state(TowerState::IDLE),
    attackInterval(0.5f),//���õĳ�ʼ���������0.5s
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


    //----------------todo��������Χ---�����ٸ�һ�£���Ϊ���������Ĳ���-----
    attackrange = 80 * 0.6 * (level + 3);


    return true;
}
//---------------------��ʱû�û�����������------------------
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

bool Tower::isTargetInRange() 
{
    my_pos = getPosition();//����ҵ�λ��

    for (auto barrier : BarrierContainer) {
        if (barrier->choosed) {
            target_pos = barrier->getPosition();
            float distance = my_pos.distance(target_pos);
            if (distance <= attackrange) {
                return true;
            }
        }
    }
    //�б�ѡ�еĹ���
    for (auto target : monsterContainer) {
        if (target->choosed) {
            target_pos = target->getPosition();//���Ŀ��λ��
            float distance = my_pos.distance(target_pos);
            if (distance <= attackrange) {
                return true;
            }
        }
    }
    //ʲôҲû��ѡ�У���ֻ������������Ĺ���
    for (auto target : monsterContainer) {

        target_pos = target->getPosition();//���Ŀ��λ��
        float distance = my_pos.distance(target_pos);
        if (distance <= attackrange) {
            return true;
        }

    }

    return false;
}

void Tower::performAttack()
{
    // ������ִ�з������Ĺ����߼������Դ����ӵ�����Ч��
    
    // ʾ�����򵥵����һ����Ϣ
    CCLOG("Tower attacks the target!");
}
