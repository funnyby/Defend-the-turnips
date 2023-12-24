/*
 Carrot Class——Father:Class ActionSprite


*/

#include "Carrot.h"
using namespace cocos2d::ui;

bool Carrot::init()
{
    _idleAction = NULL;
    _twistAction = NULL;
    _deathAction = NULL;
    _biten=false;
    _hp = 10;
    if (!initWithFile("Carrot/CarrotBiten/hlb1_10.png")) {
        CCLOG("Failed to load carrot image");
        return false;
    }
    
   //对坐标进行校正提供半个身位高度

    //设置被咬
    bitenTectures[0].fileName = "Carrot/CarrotBiten/hlb1_1.png";
    bitenTectures[1].fileName = "Carrot/CarrotBiten/hlb1_2.png";
    bitenTectures[2].fileName = "Carrot/CarrotBiten/hlb1_3.png";
    bitenTectures[3].fileName = "Carrot/CarrotBiten/hlb1_4.png";
    bitenTectures[4].fileName = "Carrot/CarrotBiten/hlb1_5.png";
    bitenTectures[5].fileName = "Carrot/CarrotBiten/hlb1_6.png";
    bitenTectures[6].fileName = "Carrot/CarrotBiten/hlb1_7.png";
    bitenTectures[7].fileName = "Carrot/CarrotBiten/hlb1_8.png";
    bitenTectures[8].fileName = "Carrot/CarrotBiten/hlb1_9.png";
    bitenTectures[9].fileName = "Carrot/CarrotBiten/hlb1_10.png";
    //设置扭动
    Vector<SpriteFrame*> twistFrames(12);
    for (int i = 0; i < 12; i++)
    {
        SpriteFrame* frame2 = SpriteFrame::create(CCString::createWithFormat("Carrot/CarrotTwist/hlb1_%d.png", i + 1)->getCString(), Rect(1000, 485, 100, 126));
        twistFrames.pushBack(frame2);
    }
    twistAnimation = Animation::createWithSpriteFrames(twistFrames, float(6.0 / 12.0));
    this->setTwistAction(CCRepeatForever::create(CCAnimate::create(twistAnimation)));
   // this->scheduleOnce(schedule_selector(Carrot::beBiten), 10.0f);
   // this->schedule(schedule_selector(Carrot::beBiten),5.0f);
    return true;
}
void Carrot::setLocation(Point mapDest) {
    location = mapDest;
    int myHeight = 50;
    location.add(Vec2(0, myHeight));
    this->setPosition(location);
}
void Carrot::updateCarrot(float delta) {
    if (_biten) {
        this->setTexture(bitenTectures[int(_hp - 1)].fileName);
        _biten = false;
    }
    // 根据_hp的值来更改代表萝卜血量的图片
   // 这里假设有一组血量图片帧，你可以根据实际情况修改
   // 比如设置显示第 _hp 个血量图片帧
  /*  std::string hpFrameName = StringUtils::format("hp_frame_%d.png", static_cast<int>(_hp));
    setSpriteFrame(hpFrameName);*/
    if (isCarrotClicked) {
        // 执行萝卜抖动效果的动作
        this->twist();
        isCarrotClicked = false; // 重置点击状态
    }
}
void Carrot::onMouseDown(EventMouse* event) {
    // 鼠标点击后的处理逻辑，可以根据需要修改精灵动作等
    if (!isCarrotClicked) {
        // 如果萝卜还没有被点击过，执行相应的处理逻辑
        isCarrotClicked = true;
        // 根据需要处理其他逻辑
    }
}
void Carrot::beBiten(float dt) {
    _hp--;
    if (_hp <= 0)
        _hp = 1;
    _biten = true;
    this->setTexture(bitenTectures[int(_hp-1)].fileName);
    //this->setPosition(location);
}
bool Carrot::GameOver() {
    if (_hp <= 0)
        this->death();
    return _hp <= 0;
 }