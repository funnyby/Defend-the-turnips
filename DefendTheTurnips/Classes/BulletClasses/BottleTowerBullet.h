#ifndef __BOTTLE_TOWER_BULLET_H_
#define __BOTTLE_TOWER_BULLET_H_
#include "..\Classes\BulletClasses\Bullet.h"
#include "..\Classes\Monster\My_monster.h"
#include "..\Classes\GameData\GameManager.h"
#include "proj.win32/GameMap.h"
using namespace cocos2d;
class GreenTowerBullet : public Bullet {
public:
    virtual bool initGreenBullet(int grade);

    CREATE_FUNC(GreenTowerBullet);
    
    void shoot();
    

    void removeBullet();
    
    virtual void upgradeAttackDamage(int increase) {
        attackDamage += increase;
        speed += increase*3;
        bulletSprite->setTexture("Bullets/GreenBottleBullets/PBottle" + StringUtils::toString(attackDamage + 10) + ".png");

    }
    virtual void inputBulletAction(Point towerLoc, Point MonsterLoc);
    void rotateSpriteToDirection();
    cocos2d::Vector<Monster*> monsterContainer;
private:
    int speed;
    MoveTo* shootTo;
    MoveBy* shootBy;
    Point src, dst;
    int myGrade;
};
#endif//__BOTTLE_TOWER_BULLET_H_