#include "ShitTower.h"
#include"..\Classes\Monster\My_monster.h"
#include"..\Classes\BulletClasses\shit.h"
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

    // 这里可以添加炮塔特有的初始化行为
    // 注册 update 函数
    schedule([=](float dt) {
        this->update(dt);
        }, "update_key");
    
    return true;
}

void ShitTower::performAttack()
{
    // 这里实现炮塔特有的攻击行为
    // 例如，发射炮弹、产生爆炸效果等
    my_pos = getPosition();//获得我的位置


    CCLOG("Cannon Tower attacks!");
    // ...
}
void ShitTower::update(float d)
{
    //------------------这个不一定对，但是能实现攻击间隔
    // 更新攻击计时器

    if (isTargetInRange()) {
        attackTimer += d;
        performAttack();
        if (attackTimer >= attackInterval) {
            attackTimer = 0.0f;  // 重置计时器

            auto BulletSprite1 = shitBullet::create();
            this->addChild(BulletSprite1, -1);
            BulletSprite1->initshitBullet(level);

            //BulletSprite1->monsterContainer.pushBack(monsterSprite);
            // 
            //----------todo：子弹不能按照正确的路径打出
            //----------todo：对接出现问题，应该是参数传递有问题
            BulletSprite1->inputBulletAction(my_pos, target_pos);//src\dst
            BulletSprite1->shoot();

        }
    }
}