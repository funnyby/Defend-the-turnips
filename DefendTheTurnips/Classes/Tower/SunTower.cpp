#include "SunTower.h"
#include"..\Classes\BulletClasses\SunFlowerBullet.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
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

    // �����������������еĳ�ʼ����Ϊ

    return true;
}

void SunTower::performAttack()
{
    // ����ʵ���������еĹ�����Ϊ
    // ���磬�����ڵ���������ըЧ����

    my_pos = getPosition();//����ҵ�λ��

    CCLOG("Cannon Tower attacks!");
    // ...
}

void SunTower::update(float d)
{
    //------------------�����һ���ԣ�������ʵ�ֹ������
    // ���¹�����ʱ��

    if (isTargetInRange()) {
        attackTimer += d;
        performAttack();
        if (attackTimer >= attackInterval) {
            attackTimer = 0.0f;  // ���ü�ʱ��
            SimpleAudioEngine::getInstance()->playEffect("Music/TowerMusic/Sun.mp3");
            auto BulletSprite1 = SunFlowerBullet::create();
            this->addChild(BulletSprite1, -1);
            BulletSprite1->initSunBullet(level);

            //BulletSprite1->monsterContainer.pushBack(monsterSprite);
            // 
            //----------todo���ӵ����ܰ�����ȷ��·�����
            //----------todo���Խӳ������⣬Ӧ���ǲ�������������
            BulletSprite1->inputBulletAction(Vec2(0, 0));//src\dst
            BulletSprite1->spread();

        }
    }


}
