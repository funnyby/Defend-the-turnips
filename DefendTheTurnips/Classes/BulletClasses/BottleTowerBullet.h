#ifndef __BOTTLE_TOWER_BULLET_H_
#define __BOTTLE_TOWER_BULLET_H_
#include "..\Classes\BulletClasses\Bullet.h"
#include "..\Classes\Monster\My_monster.h"
#include "..\Classes\GameData\GameManager.h"
using namespace cocos2d;
class GreenTowerBullet : public Bullet {
public:
    virtual bool init();
    CREATE_FUNC(GreenTowerBullet);
    void shoot();
    void removeBullet();

private:
    Monster* monster;
};
#endif//__BOTTLE_TOWER_BULLET_H_