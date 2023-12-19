#include "cocos2d.h"
#include "ActionSprite.h"

ActionSprite::ActionSprite(void)
{
    _price = 0;
    _idleAction = NULL;
    _walkAction = NULL;
    _deathAction = NULL;
}

ActionSprite::~ActionSprite(void)
{
    //释放内存
    CC_SAFE_RELEASE_NULL(_idleAction);
    CC_SAFE_RELEASE_NULL(_deathAction);
    CC_SAFE_RELEASE_NULL(_walkAction);
}

//设置精灵为静止状态
void ActionSprite::idle()
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
void ActionSprite::walk()
{
    if (_actionState != kActionStateWalk)
    {
        //先停止所有动作
        this->stopAllActions();
        //运行行走动作
        this->runAction(_walkAction);
        _actionState = kActionStateWalk;
    }

}

//设置精灵为死亡状态
void ActionSprite::death()
{
    //先停止所有动作
    this->stopAllActions();
    this->runAction(_deathAction);
    _actionState = kActionStateDeath;
}