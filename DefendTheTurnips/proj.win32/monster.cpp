#include "monster.h"

//�����ṩ��spriteIndexʵ�����ɲ�ͬ��ɫ��
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
//��ʼ������
bool Monster::initWithType(int spriteIndex, bool halo)
{
    bool bRet = false;
    do
    {
        //ɫ������index
        _spriteIndex = spriteIndex;
        //
        //m = GameMediator::sharedMediator();
        //������
        active = false;
        //�����ٶ�
        walkingSpeed = 0.2f;
        ActionSprite* sprite = NULL;
        if (spriteIndex == 1)//���������1��ʼ���ɴ���ɫ��
        {
            //sprite = Monster::create();
            sprite->setHalo(halo);
            //�����ٶ�
            walkingSpeed = sprite->getWalkSpeed();
        }
        this->setMySprite(sprite);
        //��Ӿ��鵽��ǰSelang��
        this->addChild(_mySprite);
        //���㵱ǰɫ�Ǿ���1/2��
        myHeight = sprite->getTextureRect().size.height / 2.0f;
        //���·�㼯���е����һ����
        //Waypoint* waypoint = (Waypoint*)m->getWayPoints().back();
        //����Ϊɫ�ǳ�����
        //beginningWaypoint = waypoint;
        //��ȡ��������¸���Ϊɫ��Ŀ���
        //destinationWaypoint = waypoint->getNextWaypoint();
        //��ó���������
        //Point pos = waypoint->getMyPosition();
        //���������У���ṩ�����λ�߶�
        //pos.add(Vec2(0, myHeight));
        //��¼λ������
        //myPosition = pos;
        //���þ���ĳ�ʼ����
        //_mySprite->setPosition(pos);
        //���ó�ʼ���ɼ�
        this->setVisible(false);
        //�ѵ�ǰɫ����ӵ���Ϸ��MainScene��������ʾ
        //m->getNowScene()->addChild(this);
        //������ʱ��
        this->scheduleUpdate();
        bRet = true;
    } while (0);
    return bRet;
}

void Monster::doActivate(float dt)
{
    //����ɫ��
    active = true;
    //����ɫ�ǿɼ�
    this->setVisible(true);
}

//��ȡ����Rect
/*Rect Monster::getRect()
{
    Rect rect = Rect(_mySprite->getPosition().x - _mySprite->getContentSize().width * 0.5f,
        _mySprite->getPosition().y - _mySprite->getContentSize().height * 0.5f,
        _mySprite->getContentSize().width,
        _mySprite->getContentSize().height);
    return rect;
}*/

//���þ����Ƿ񼤻�
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
    //����ɫ�ǰ����λ
    //destinationPos.add(Vec2(0, myHeight));
    //�Ƿ����
    if (this->collisionWithCircle(myPosition, 1, destinationPos, 1))
    {
        if (destinationWaypoint->getNextWaypoint())
        {
            //�����µĳ������Ŀ���
            beginningWaypoint = destinationWaypoint;
            destinationWaypoint = destinationWaypoint->getNextWaypoint();
        }
    }
    Point targetPoint = destinationWaypoint->getMyPosition();
    //����ɫ�ǰ����λ
    targetPoint.add(Vec2(0, myHeight));
    float movementSpeed = walkingSpeed;
    //����Ŀ��������
    Point normalized = Point(targetPoint.x - myPosition.x, targetPoint.y - myPosition.y).getNormalized();
    //�����ٶȺ������ֱ����x,y��ʽ�ϵ�ƫ��ֵ
    float ox = normalized.x * walkingSpeed;
    float oy = normalized.y * walkingSpeed;
    //����ɫ���ƶ����λ��
    myPosition = Point(myPosition.x + ox, myPosition.y + oy);
    _mySprite->setPosition(myPosition);
}
//���������ײ���
bool Selang::collisionWithCircle(cocos2d::Point circlePoint, float radius, cocos2d::Point circlePointTwo, float radiusTwo)
{
    float xdif = circlePoint.x - circlePointTwo.x;
    float ydif = circlePoint.y - circlePointTwo.y;
    //���������ľ���
    float distance = sqrt(xdif * xdif + ydif * ydif);
    if (distance <= radius + radiusTwo)
    {
        return true;
    }
    return false;
}*/