#ifndef __SUN_FLOWER_BULLET_H_
#define __SUN_FLOWER_BULLET_H_
#include "..\Classes\BulletClasses\Bullet.h"
#include "..\Classes\Monster\My_monster.h"
#include "..\Classes\GameData\GameManager.h"
#include "proj.win32/GameMap.h"
using namespace cocos2d;
class SunFlowerBullet : public Bullet {
public:
    virtual bool initSunBullet();
    CREATE_FUNC(SunFlowerBullet);
    void spread();
    void removeBullet();
    virtual void upgradeAttackDamage(int increase) {
        attackDamage += increase;
        bulletSprite->setTexture("Bullets/GreenBottleBullets/PBottle" + StringUtils::toString(attackDamage + 10) + ".png");
    }
    //GameMap* getMap(GameMap* nowMap) { return nowMap;}
    virtual void inputBulletAction(Point towerLoc, Point MonsterLoc);
    //void rotateSpriteToDirection(Point src, Point dst);
   // cocos2d::Vector<Monster*> monsterContainer;
private:
    int speed;
    MoveTo* spreadTo;

};
#endif//__SUN_FLOWER_BULLET_H_