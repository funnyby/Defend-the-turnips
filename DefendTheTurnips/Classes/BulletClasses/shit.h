#ifndef __SHIT_H_
#define __SHIT_H_
#include "..\Classes\BulletClasses\Bullet.h"
#include "..\Classes\Monster\My_monster.h"
using namespace cocos2d;
class shitBullet : public Bullet {
public:
    virtual bool initshitBullet(int grade);

    CREATE_FUNC(shitBullet);

    void shoot();

    void removeBullet();

    virtual void inputBulletAction(Point towerLoc, Point MonsterLoc);
    
    void rotateSpriteToDirection();
    
    cocos2d::Vector<Monster*> monsterContainer;
private:
    int speed;
    
    CC_SYNTHESIZE(float, _freeze, Freeze);

    MoveBy* shootBy;

    Point src, dst;

    int myGrade;

};
#endif//__SHIT_H_