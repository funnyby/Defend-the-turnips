/*
 Carrot Class——Father:Class ActionSprite


*/
#include "Carrot.h"

bool Carrots::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!ActionSprite::initWithFile("Carrot_1.png"));

        //设置静止状态动作
        Vector<SpriteFrame*> idleFrames(1);
        SpriteFrame* frame1 = SpriteFrame::create("Carrot_1.png", Rect(0, 0, 100, 126));
        idleFrames.pushBack(frame1);
        Animation* idleAnimation = Animation::createWithSpriteFrames(idleFrames, float(6.0 / 12.0));
        this->setIdleAction(CCRepeatForever::create(CCAnimate::create(idleAnimation)));

        //设置行走状态动作
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
        //实例化一个萝莉
        auto thisCarrot = Carrots::create();
        this->setMySprite(thisCarrot);
        //添加精灵到当前Gril中
        this->addChild(thisCarrot);
        //设置为静止
        thisCarrot->idle();
        //计算当前萝莉精灵1/2高
        int myHeight = thisCarrot->getTextureRect().size.height / 2.0f;
        //对坐标进行校正提供半个身位高度
        location.add(Vec2(0, myHeight));
        thisCarrot->setPosition(location);
        GameMediator* m = sharedMediator();
        m->getRunningScene()->addChild(this, 10000);
        bRet = true;
    } while (0);
    return bRet;
}
