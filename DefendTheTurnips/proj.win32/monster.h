#include "ActionSprite.h"

class Monster : public cocos2d::CCNode
{
public:
    //�����ṩ��spriteIndexʵ�����ɲ�ͬ��ɫ��
    static Monster* nodeWithType(int spriteIndex);
    //��ʼ������
    bool initWithType(int spriteIndex, bool halo);
    //����ɫ��
    void doActivate(float dt);
    //��ȡ����Rect
    //virtual cocos2d::Rect getRect();
    //���þ����Ƿ񼤻�
    void setActive(bool active);
    //�Ƿ�����
    bool isDie;
    //void update(float delta);
    //ɫ�Ǿ���
    CC_SYNTHESIZE_RETAIN(ActionSprite*, _mySprite, MySprite);

private:
    //������ţ�Ϊÿ�־����һ�����
    int _spriteIndex;
    //GameMediator* m;
    //��ǰ�����λ��
    cocos2d::Point myPosition;
    //��·�ٶ�
    float walkingSpeed;
    //��ʼ·��
    //Waypoint* beginningWaypoint;
    //����·��
    //Waypoint* destinationWaypoint;
    //�Ƿ񼤻�
    bool active;
    //ɫ�Ǹ߶�
    float myHeight;
    //���������ײ���
    bool collisionWithCircle(cocos2d::Point circlePoint, float radius, cocos2d::Point circlePointTwo, float radiusTwo);
}; 
