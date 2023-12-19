/*
 Carrot Class����Father:Class ActionSprite


*/
#include "Carrot.h"

bool Carrots::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!ActionSprite::initWithFile("Carrot_1.png"));

        //���þ�ֹ״̬����
        Vector<SpriteFrame*> idleFrames(1);
        SpriteFrame* frame1 = SpriteFrame::create("Carrot_1.png", Rect(0, 0, 100, 126));
        idleFrames.pushBack(frame1);
        Animation* idleAnimation = Animation::createWithSpriteFrames(idleFrames, float(6.0 / 12.0));
        this->setIdleAction(CCRepeatForever::create(CCAnimate::create(idleAnimation)));

        //��������״̬����
        int i;
        Vector<SpriteFrame*> walkFrames(4);
        for (i = 0; i < 4; i++)
        {
            SpriteFrame* frame2 = SpriteFrame::create(CCString::createWithFormat("Carrot_1.png", i + 1)->getCString(), Rect(0, 0, 100, 126));
            walkFrames.pushBack(frame2);
        }

        Animation* walkAnimation = Animation::createWithSpriteFrames(walkFrames, float(6.0 / 12.0));
        this->setWalkAction(CCRepeatForever::create(CCAnimate::create(walkAnimation)));


        bRet = true;

    } while (0);

    return bRet;
}

bool Carrots::initWithLocation(Point location)
{
    bool bRet = false;
    do
    {
        //ʵ����һ������
        auto thisCarrot = Carrots::create();
        this->setMySprite(thisCarrot);
        //��Ӿ��鵽��ǰGril��
        this->addChild(thisCarrot);
        //����Ϊ��ֹ
        thisCarrot->idle();
        //���㵱ǰ������1/2��
        int myHeight = thisCarrot->getTextureRect().size.height / 2.0f;
        //���������У���ṩ�����λ�߶�
        location.add(Vec2(0, myHeight));
        thisCarrot->setPosition(location);
        GameMediator* m = sharedMediator();
        m->getRunningScene()->addChild(this, 10000);
        bRet = true;
    } while (0);
    return bRet;
}
