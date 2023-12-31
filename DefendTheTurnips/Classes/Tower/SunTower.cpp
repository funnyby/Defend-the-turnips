#include "SunTower.h"
#include"..\Classes\Monster\My_monster.h"
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
    attackInterval = 1.0f;
    // �����������������еĳ�ʼ����Ϊ
    schedule([=](float dt) {
        this->update(dt);
        }, "update_key");
    return true;
}

void SunTower::performAttack()
{
    // ����ʵ���������еĹ�����Ϊ
    // ���磬�����ڵ���������ըЧ����

    my_pos = getPosition();//����ҵ�λ��
    setAnchorPoint(Vec2(0.5, 0.5));
    CCLOG("Cannon Tower attacks!");
    // ...
}

void SunTower::update(float d)
{
    //------------------�����һ���ԣ�������ʵ�ֹ������
    // ���¹�����ʱ��
    SimpleAudioEngine::getInstance()->playEffect("Music/SelectFault.mp3");
    if (isTargetInRange()) {
        attackTimer += d;
        performAttack();
        if (attackTimer >= attackInterval) {
            attackTimer = 0.0f;  // ���ü�ʱ��
            SimpleAudioEngine::getInstance()->playEffect("Music/TowerMusic/Sun.mp3");
            auto BulletSprite1 = SunFlowerBullet::create();
            this->addChild(BulletSprite1, -1);
            BulletSprite1->initSunBullet(level);
            int x = BulletSprite1->getContentSize().width;
            int y = BulletSprite1->getContentSize().height;
            //BulletSprite1->monsterContainer.pushBack(monsterSprite);
            // 
            //----------todo���ӵ����ܰ�����ȷ��·�����
            //----------todo���Խӳ������⣬Ӧ���ǲ�������������
            BulletSprite1->inputBulletAction(Vec2(45, 50));//src
            BulletSprite1->spread();

        }
    }


}
