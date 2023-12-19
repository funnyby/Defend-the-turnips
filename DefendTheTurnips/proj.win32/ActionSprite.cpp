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
    //�ͷ��ڴ�
    CC_SAFE_RELEASE_NULL(_idleAction);
    CC_SAFE_RELEASE_NULL(_deathAction);
    CC_SAFE_RELEASE_NULL(_walkAction);
}

//���þ���Ϊ��ֹ״̬
void ActionSprite::idle()
{
    if (_actionState != kActionStateIdle)
    {
        //��ֹͣ���ж���
        this->stopAllActions();
        //���о�ֹ����
        this->runAction(_idleAction);
        _actionState = kActionStateIdle;
    }
}

//���þ���Ϊ����״̬
void ActionSprite::walk()
{
    if (_actionState != kActionStateWalk)
    {
        //��ֹͣ���ж���
        this->stopAllActions();
        //�������߶���
        this->runAction(_walkAction);
        _actionState = kActionStateWalk;
    }

}

//���þ���Ϊ����״̬
void ActionSprite::death()
{
    //��ֹͣ���ж���
    this->stopAllActions();
    this->runAction(_deathAction);
    _actionState = kActionStateDeath;
}