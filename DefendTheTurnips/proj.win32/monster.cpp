#include "monster.h"

//根据提供的spriteIndex实例化成不同的色狼
Monster* Monster::nodeWithType(int spriteIndex)
{
    Monster* pRet = new Monster();
    bool b = false;
    if (pRet && pRet->initWithType(spriteIndex, b))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
//初始化方法
bool Monster::initWithType(int spriteIndex, bool halo)
{
    bool bRet = false;
    do
    {
        //色狼类型index
        _spriteIndex = spriteIndex;
        //
        //m = GameMediator::sharedMediator();
        //不激活
        active = false;
        //行走速度
        walkingSpeed = 0.2f;
        ActionSprite* sprite = NULL;
        if (spriteIndex == 1)//如果类型是1初始化成大叔色狼
        {
            //sprite = Monster::create();
            sprite->setHalo(halo);
            //设置速度
            walkingSpeed = sprite->getWalkSpeed();
        }
        this->setMySprite(sprite);
        //添加精灵到当前Selang中
        this->addChild(_mySprite);
        //计算当前色狼精灵1/2高
        myHeight = sprite->getTextureRect().size.height / 2.0f;
        //获得路点集合中的最后一个点
        //Waypoint* waypoint = (Waypoint*)m->getWayPoints().back();
        //设置为色狼出发点
        //beginningWaypoint = waypoint;
        //获取出发点的下个点为色狼目标点
        //destinationWaypoint = waypoint->getNextWaypoint();
        //获得出发点坐标
        //Point pos = waypoint->getMyPosition();
        //对坐标进行校正提供半个身位高度
        //pos.add(Vec2(0, myHeight));
        //记录位置坐标
        //myPosition = pos;
        //设置精灵的初始坐标
        //_mySprite->setPosition(pos);
        //设置初始不可见
        this->setVisible(false);
        //把当前色狼添加到游戏的MainScene场景中显示
        //m->getNowScene()->addChild(this);
        //启动定时器
        this->scheduleUpdate();
        bRet = true;
    } while (0);
    return bRet;
}

void Monster::doActivate(float dt)
{
    //激活色狼
    active = true;
    //设置色狼可见
    this->setVisible(true);
}

//获取精灵Rect
/*Rect Monster::getRect()
{
    Rect rect = Rect(_mySprite->getPosition().x - _mySprite->getContentSize().width * 0.5f,
        _mySprite->getPosition().y - _mySprite->getContentSize().height * 0.5f,
        _mySprite->getContentSize().width,
        _mySprite->getContentSize().height);
    return rect;
}*/

//设置精灵是否激活
void Monster::setActive(bool aactive)
{
    active = aactive;
    this->setVisible(true);
}

/*void Monster::update(float delta)
{
    if (!active)
    {
        return;
    }
    //Point destinationPos = destinationWaypoint->getMyPosition();
    //提升色狼半个身位
    //destinationPos.add(Vec2(0, myHeight));
    //是否拐弯
    if (this->collisionWithCircle(myPosition, 1, destinationPos, 1))
    {
        if (destinationWaypoint->getNextWaypoint())
        {
            //设置新的出发点和目标点
            beginningWaypoint = destinationWaypoint;
            destinationWaypoint = destinationWaypoint->getNextWaypoint();
        }
    }
    Point targetPoint = destinationWaypoint->getMyPosition();
    //提升色狼半个身位
    targetPoint.add(Vec2(0, myHeight));
    float movementSpeed = walkingSpeed;
    //计算目标点的向量
    Point normalized = Point(targetPoint.x - myPosition.x, targetPoint.y - myPosition.y).getNormalized();
    //根据速度和向量分别计算x,y方式上的偏移值
    float ox = normalized.x * walkingSpeed;
    float oy = normalized.y * walkingSpeed;
    //更新色狼移动后的位置
    myPosition = Point(myPosition.x + ox, myPosition.y + oy);
    _mySprite->setPosition(myPosition);
}
//两个点的碰撞检测
bool Selang::collisionWithCircle(cocos2d::Point circlePoint, float radius, cocos2d::Point circlePointTwo, float radiusTwo)
{
    float xdif = circlePoint.x - circlePointTwo.x;
    float ydif = circlePoint.y - circlePointTwo.y;
    //计算两点间的距离
    float distance = sqrt(xdif * xdif + ydif * ydif);
    if (distance <= radius + radiusTwo)
    {
        return true;
    }
    return false;
}*/