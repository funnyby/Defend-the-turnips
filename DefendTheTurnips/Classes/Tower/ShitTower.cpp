#include "ShitTower.h"
#include"..\Classes\Monster\My_monster.h"
#include"..\Classes\BulletClasses\shit.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
ShitTower::ShitTower()
{

}

ShitTower* ShitTower::create(const std::string& towerImage)
{
    ShitTower* tower = new ShitTower();
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


bool ShitTower::init(const std::string& towerImage)
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

void ShitTower::performAttack()
{
    // ����ʵ���������еĹ�����Ϊ
    // ���磬�����ڵ���������ըЧ����
    my_pos = getPosition();//����ҵ�λ��


    CCLOG("Cannon Tower attacks!");
    // ...
}
void ShitTower::update(float d)
{
    //------------------�����һ���ԣ�������ʵ�ֹ������
    // ���¹�����ʱ��

    if (isTargetInRange()) {
        attackTimer += d;
        performAttack();
        if (attackTimer >= attackInterval) {
            attackTimer = 0.0f;  // ���ü�ʱ��
            SimpleAudioEngine::getInstance()->playEffect("Music/TowerMusic/Shit.mp3");
            auto bulletSprite1 = shitBullet::create();
            this->addChild(bulletSprite1, -1);
            bulletSprite1->initshitBullet(level);

            //BulletSprite1->monsterContainer.pushBack(monsterSprite);
            // 
            //----------todo���ӵ����ܰ�����ȷ��·�����
            //----------todo���Խӳ������⣬Ӧ���ǲ�������������
            bulletSprite1->inputBulletAction(my_pos, target_pos);//src\dst
            bulletSprite1->shoot();

        }
    }
}