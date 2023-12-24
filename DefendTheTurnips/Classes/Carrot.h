#ifndef __CARROT_H_
#define __CARROT_H_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
//#include "ActionSprite.h"
#include <vector>
using namespace cocos2d;
struct filesName {
    std::string fileName = { "\0" };
};

typedef enum _ActionState {
    kActionStateNone = 0, //无状态
    kActionStateIdle, //静止状态
    kActionStateWalk, //行走状态
    kActionStateDeath //死亡状态
}ActionState;


class Carrot :public Sprite
{
public:
	bool init();
    //void whenTouched();
    void beBiten(float dt);
    bool GameOver();
    void setLocation(Point mapDest);
    void updateCarrot(float delta);
    bool isCarrotClicked = false;
    void onMouseDown(EventMouse* event);
    //设置精灵为静止状态
    void Carrot::idle()
    {
        if (_actionState != kActionStateIdle)
        {
            //先停止所有动作
            this->stopAllActions();
            //运行静止动作
            this->runAction(_idleAction);
            _actionState = kActionStateIdle;
        }
    }

    //设置精灵为行走状态
    void Carrot::twist()
    {
        if (_actionState != kActionStateWalk)
        {
            //先停止所有动作
            this->stopAllActions();
            //运行行走动作
            this->runAction(_twistAction);
            _actionState = kActionStateWalk;
        }

    }

    //设置精灵为死亡状态
    void Carrot::death()
    {
        //先停止所有动作
        this->stopAllActions();
        this->runAction(_deathAction);
        _actionState = kActionStateDeath;
    }
private:
    Point location;
    filesName bitenTectures[10];
    //生命值
    CC_SYNTHESIZE(float, _hp, HP);
    //被咬了一口
    CC_SYNTHESIZE(bool, _biten, biten);
    //静止状态动作
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _idleAction, IdleAction);
    //死亡状态动作
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _deathAction, DeathAction);
    //扭动状态动作
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _twistAction, TwistAction);
    //当前动作状态
    CC_SYNTHESIZE(ActionState, _actionState, ActionState);

    Animation* twistAnimation;

    CREATE_FUNC(Carrot);
};
#endif // __CHOOSE_LEVEL_H__