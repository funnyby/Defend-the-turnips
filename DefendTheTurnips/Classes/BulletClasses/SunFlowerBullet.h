#ifndef __SUN_FLOWER_BULLET_H_
#define __SUN_FLOWER_BULLET_H_
#include "..\Classes\BulletClasses\Bullet.h"
#include "..\Classes\Monster\My_monster.h"
using namespace cocos2d;
class SunFlowerBullet : public Bullet {
public:
    virtual bool initSunBullet(int grade);

    CREATE_FUNC(SunFlowerBullet);
    
    void spread();
    
    void removeBullet();
    
    virtual void inputBulletAction(Point towerLoc);
   // cocos2d::Vector<Monster*> monsterContainer;
private:
    int speed;

    MoveTo* spreadTo;

    Point src;

    int myGrade;
};
#endif//__SUN_FLOWER_BULLET_H_