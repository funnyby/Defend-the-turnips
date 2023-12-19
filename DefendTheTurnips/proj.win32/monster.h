#include "ActionSprite.h"

class Monster : public cocos2d::CCNode
{
public:
    //根据提供的spriteIndex实例化成不同的色狼
    static Monster* nodeWithType(int spriteIndex);
    //初始化方法
    bool initWithType(int spriteIndex, bool halo);
    //激活色狼
    void doActivate(float dt);
    //获取精灵Rect
    //virtual cocos2d::Rect getRect();
    //设置精灵是否激活
    void setActive(bool active);
    //是否死亡
    bool isDie;
    //void update(float delta);
    //色狼精灵
    CC_SYNTHESIZE_RETAIN(ActionSprite*, _mySprite, MySprite);

private:
    //精灵序号，为每种精灵编一个序号
    int _spriteIndex;
    //GameMediator* m;
    //当前精灵的位置
    cocos2d::Point myPosition;
    //走路速度
    float walkingSpeed;
    //开始路点
    //Waypoint* beginningWaypoint;
    //结束路点
    //Waypoint* destinationWaypoint;
    //是否激活
    bool active;
    //色狼高度
    float myHeight;
    //两个点的碰撞检测
    bool collisionWithCircle(cocos2d::Point circlePoint, float radius, cocos2d::Point circlePointTwo, float radiusTwo);
}; 
