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

    // 这里可以添加炮塔特有的初始化行为

    return true;
}

void SunTower::performAttack()
{
    // 这里实现炮塔特有的攻击行为
    // 例如，发射炮弹、产生爆炸效果等

    my_pos = getPosition();//获得我的位置

    CCLOG("Cannon Tower attacks!");
    // ...
}

void SunTower::update(float d)
{
    //------------------这个不一定对，但是能实现攻击间隔
    // 更新攻击计时器

    if (isTargetInRange()) {
        attackTimer += d;
        performAttack();
        if (attackTimer >= attackInterval) {
            attackTimer = 0.0f;  // 重置计时器
            SimpleAudioEngine::getInstance()->playEffect("Music/TowerMusic/Sun.mp3");
            auto BulletSprite1 = SunFlowerBullet::create();
            this->addChild(BulletSprite1, -1);
            BulletSprite1->initSunBullet(level);

            //BulletSprite1->monsterContainer.pushBack(monsterSprite);
            // 
            //----------todo：子弹不能按照正确的路径打出
            //----------todo：对接出现问题，应该是参数传递有问题
            BulletSprite1->inputBulletAction(Vec2(0, 0));//src\dst
            BulletSprite1->spread();

        }
    }


}
