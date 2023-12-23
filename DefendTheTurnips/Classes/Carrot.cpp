/*
 Carrot Class——Father:Class ActionSprite


*/

#include "Carrot.h"
using namespace cocos2d::ui;

bool Carrot::init()
{
    _hp = 10;
    auto myCarrot=initWithFile("Carrot_1.png");
    int myHeight =50;
   //对坐标进行校正提供半个身位高度
    location.add(Vec2(0, myHeight));
    this->setPosition(location);
    return true;
   /* bool bRet = false;
    do
    {
        CC_BREAK_IF(!ActionSprite::initWithFile("Carrot/CarrotStay/Carrot_1.png"));

        //设置静止状态动作
        Vector<SpriteFrame*> idleFrames(1);
        SpriteFrame* frame1 = SpriteFrame::create("Carrot/CarrotStay/Carrot_1.png", Rect(0, 0, 100, 126));
        idleFrames.pushBack(frame1);
        Animation* idleAnimation = Animation::createWithSpriteFrames(idleFrames, float(6.0 / 12.0));
        this->setIdleAction(CCRepeatForever::create(CCAnimate::create(idleAnimation)));

        //设置行走状态动作
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
 */
}
void Carrot::setLocation(Point mapDest) {
    location = mapDest;
}

void Carrot::beBiten() {
    _hp--;
}
bool Carrot::GameOver() {
    if (_hp == 0)
        return true;
    return false;
 }