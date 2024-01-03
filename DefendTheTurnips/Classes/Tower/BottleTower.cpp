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

    // 这里可以添加炮塔特有的初始化行为
    // 注册 update 函数
    schedule([=](float dt) {
        this->update(dt);
        }, "update_key");
    return true;

}


void BottleTower::performAttack()
{
    // 这里实现炮塔特有的攻击行为
    // 例如，发射炮弹、产生爆炸效果等

    my_pos = getPosition();//获得我的位置
    float distance;


    //方向向量
    Vec2 direction = target_pos - my_pos;
    setAnchorPoint(Vec2(0.5, 0.5));
    // 计算角度（弧度）
    const float angle = atan2(direction.y, direction.x);

    // 将弧度转换为角度
    const float rotation = CC_RADIANS_TO_DEGREES(angle);

    // 设置炮塔的旋转角度
    setRotation(-rotation + 90);


    CCLOG("Cannon Tower attacks!");
    // ...
}

void BottleTower::update(float d)
{
    //------------------这个不一定对，但是能实现攻击间隔
    // 更新攻击计时器
  
    if (isTargetInRange()) {
        attackTimer += d;
        performAttack();
        if (attackTimer >= attackInterval) {
            attackTimer = 0.0f;  // 重置计时器

            auto BulletSprite1 = GreenTowerBullet::create();
            this->addChild(BulletSprite1, 9);
            BulletSprite1->initGreenBullet(level);

            //BulletSprite1->monsterContainer.pushBack(monsterSprite);
            BulletSprite1->inputBulletAction(Vec2::ZERO, target_pos - my_pos);//src\dst
            BulletSprite1->shoot();

        }
    }
    
}