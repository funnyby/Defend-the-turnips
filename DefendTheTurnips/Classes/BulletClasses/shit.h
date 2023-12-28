#ifndef __SHIT_H_
#define __SHIT_H_
#include "..\Classes\BulletClasses\Bullet.h"
#include "..\Classes\Monster\My_monster.h"
#include "..\Classes\GameData\GameManager.h"
#include "proj.win32/GameMap.h"
using namespace cocos2d;
class shitBullet : public Bullet {
public:
    virtual bool initshitBullet();
    CREATE_FUNC(shitBullet);
    void shoot();
    void removeBullet();
    virtual void upgradeAttackDamage(int increase) {
        attackDamage += increase;
        bulletSprite->setTexture("Bullets/GreenBottleBullets/PBottle" + StringUtils::toString(attackDamage + 10) + ".png");
    }
    virtual void inputBulletAction(Point towerLoc, Point MonsterLoc);
    void rotateSpriteToDirection(Point src, Point dst);
    cocos2d::Vector<Monster*> monsterContainer;
private:
    int speed;
    int freeze = attackDamage - 4;//
    MoveTo* shootTo;

};
#endif//__SHIT_H_