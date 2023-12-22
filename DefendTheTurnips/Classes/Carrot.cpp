/*
 Carrot Class����Father:Class ActionSprite


*/
#include "Carrot.h"

bool Carrot::init()
{

    bool bRet = false;
    do
    {
        CC_BREAK_IF(!ActionSprite::initWithFile("Carrot/CarrotStay/Carrot_1.png"));

        //���þ�ֹ״̬����
        Vector<SpriteFrame*> idleFrames(1);
        SpriteFrame* frame1 = SpriteFrame::create("Carrot/CarrotStay/Carrot_1.png", Rect(0, 0, 100, 126));
        idleFrames.pushBack(frame1);
        Animation* idleAnimation = Animation::createWithSpriteFrames(idleFrames, float(6.0 / 12.0));
        this->setIdleAction(CCRepeatForever::create(CCAnimate::create(idleAnimation)));

        //��������״̬����
        int i;
        Vector<SpriteFrame*> walkFrames(12);
        for (i = 0; i < 12; i++)
        {
            SpriteFrame* frame2 = SpriteFrame::create(CCString::createWithFormat("hlb1_%d.png", i + 10)->getCString(), Rect(0, 0, 100, 126));
            walkFrames.pushBack(frame2);
        }

        Animation* walkAnimation = Animation::createWithSpriteFrames(walkFrames, float(6.0 / 12.0));
        this->setWalkAction(CCRepeatForever::create(CCAnimate::create(walkAnimation)));

        bRet = true;

    } while (0);

    return bRet;
}
bool Carrot::initWithLocation(Point location)
{
    bool bRet = false;
    do
    {
        //ʵ����һ���ܲ�
        auto sprite = Carrot::create();
        sprite->initWithFile("Carrot/CarrotStay/Carrot_1.png");
        //��Ӿ��鵽��ǰCarrot��
        this->addChild(sprite);
        //����Ϊ��ֹ
        sprite->idle();
        //���㵱ǰ������1/2��
        int myHeight = sprite->getTextureRect().size.height / 2.0f;
        //���������У���ṩ�����λ�߶�
        location.add(Vec2(0, myHeight));
        sprite->setPosition(location);
        Director* pDirector = Director::getInstance();
        Scene* curScene = pDirector->getRunningScene();
        curScene->addChild(this, 10000);
        bRet = true;
    } while (0);
    return bRet;
}


