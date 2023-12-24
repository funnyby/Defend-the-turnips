#ifndef __BULLET_H_
#define __BULLET_H_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../Classes/Monster/My_monster.h"
USING_NS_CC;
using namespace cocos2d::ui;
enum class BulletType {
    Normal,
    // �����ӵ�����
};
class Bullet : public Node {
public:
    CREATE_FUNC(Bullet);

    virtual bool init();

    // �����ӵ��ķ��ж���
    virtual void setBulletAnimation(Animate* animation);

    // �ӵ�����Ŀ��
    virtual void attack(Node* target);

    // �ӵ���������������
    void upgradeAttackDamage(int increase);

private:
    CC_SYNTHESIZE(int, attackDamage, AttackDamage);
    CC_SYNTHESIZE(int, attackRange, AttackRange);
    CC_SYNTHESIZE(Spawn*, bulletAction, BulletAction);
    CC_SYNTHESIZE(BulletType, bulletType, BulletType);
    Sprite* bulletSprite;
};
#endif //__BULLET_H_