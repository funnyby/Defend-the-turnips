#include "monster1.h"

bool monster1::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!ActionSprite::initWithFile("dashu_2.png"));

        /*//���þ�ֹ״̬����
        Vector<SpriteFrame*> idleFrames(1);
        SpriteFrame* frame1 = SpriteFrame::create("dashu_2.png", Rect(0, 0, 60, 83));
        idleFrames.pushBack(frame1);
        Animation* idleAnimation = Animation::createWithSpriteFrames(idleFrames, float(6.0 / 12.0));
        this->setIdleAction(CCRepeatForever::create(CCAnimate::create(idleAnimation)));

        int i = 0;
        //��������״̬����
        Vector<SpriteFrame*> walkFrames(2);
        for (i = 0; i < 2; i++)
        {
            SpriteFrame* frame2 = SpriteFrame::create(CCString::createWithFormat("dashu_%d.png", i + 1)->getCString(), Rect(0, 0, 60, 83));
            walkFrames.pushBack(frame2);
        }
        Animation* walkAnimation = Animation::createWithSpriteFrames(walkFrames, float(6.0 / 12.0));
        this->setWalkAction(CCRepeatForever::create(CCAnimate::create(walkAnimation)));

        //��������״̬����
        Vector<SpriteFrame*> deathFrames(1);
        SpriteFrame* frame3 = SpriteFrame::create("dashu_2.png", Rect(0, 0, 60, 83));
        deathFrames.pushBack(frame3);
        Animation* deathAnimation = Animation::createWithSpriteFrames(deathFrames, float(6.0 / 12.0));
        this->setDeathAction(Animate::create(deathAnimation));*/
        //���ù���ֵ
        this->setDamage(1);
        //���������ٶ�
        this->setWalkSpeed(0.4f);
        //��������ֵ
        this->setHP(18);
        //���ý�Ǯ��
        this->setMoney(1.0f / 10.0f);
        bRet = true;
    } while (0);

    return bRet;
}

//���ù⻷
void  monster1::setHalo(bool halo)
{
    if (halo)
    {
        //ӵ�й⻷������ֵ��4��
        float h = this->getHP() * 4.0f;
        this->setHP(h);
    }

}