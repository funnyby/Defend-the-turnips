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
    kActionStateNone = 0, //��״̬
    kActionStateIdle, //��ֹ״̬
    kActionStateWalk, //����״̬
    kActionStateDeath //����״̬
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
    //���þ���Ϊ��ֹ״̬
    void Carrot::idle()
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
    void Carrot::twist()
    {
        if (_actionState != kActionStateWalk)
        {
            //��ֹͣ���ж���
            this->stopAllActions();
            //�������߶���
            this->runAction(_twistAction);
            _actionState = kActionStateWalk;
        }

    }

    //���þ���Ϊ����״̬
    void Carrot::death()
    {
        //��ֹͣ���ж���
        this->stopAllActions();
        this->runAction(_deathAction);
        _actionState = kActionStateDeath;
    }
private:
    Point location;
    filesName bitenTectures[10];
    //����ֵ
    CC_SYNTHESIZE(float, _hp, HP);
    //��ҧ��һ��
    CC_SYNTHESIZE(bool, _biten, biten);
    //��ֹ״̬����
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _idleAction, IdleAction);
    //����״̬����
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _deathAction, DeathAction);
    //Ť��״̬����
    CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _twistAction, TwistAction);
    //��ǰ����״̬
    CC_SYNTHESIZE(ActionState, _actionState, ActionState);

    Animation* twistAnimation;

    CREATE_FUNC(Carrot);
};
#endif // __CHOOSE_LEVEL_H__