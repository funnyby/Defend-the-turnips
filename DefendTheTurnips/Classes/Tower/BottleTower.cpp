#include "..\Classes\Tower\BottleTower.h"
#include"..\Classes\Monster\My_monster.h"
#include"..\Classes\BulletClasses\BottleTowerBullet.h"



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
    // ע�� update ����
    schedule([=](float dt) {
        this->update(dt);
        }, "update_key");
    return true;

}


void BottleTower::performAttack()
{
    // ����ʵ���������еĹ�����Ϊ
    // ���磬�����ڵ���������ըЧ����

    my_pos = getPosition();//����ҵ�λ��
    float distance;


    //��������
    Vec2 direction = target_pos - my_pos;
    setAnchorPoint(Vec2(0.5, 0.5));
    // ����Ƕȣ����ȣ�
    const float angle = atan2(direction.y, direction.x);

    // ������ת��Ϊ�Ƕ�
    const float rotation = CC_RADIANS_TO_DEGREES(angle);

    // ������������ת�Ƕ�
    setRotation(-rotation + 90);


    CCLOG("Cannon Tower attacks!");
    // ...
}

void BottleTower::update(float d)
{
    //------------------�����һ���ԣ�������ʵ�ֹ������
    // ���¹�����ʱ��
  
    if (isTargetInRange()) {
        attackTimer += d;
        performAttack();
        if (attackTimer >= attackInterval) {
            attackTimer = 0.0f;  // ���ü�ʱ��

            auto BulletSprite1 = GreenTowerBullet::create();
            this->addChild(BulletSprite1, 9);
            BulletSprite1->initGreenBullet(level);

            //BulletSprite1->monsterContainer.pushBack(monsterSprite);
            BulletSprite1->inputBulletAction(Vec2::ZERO, target_pos - my_pos);//src\dst
            BulletSprite1->shoot();

        }
    }
    
}