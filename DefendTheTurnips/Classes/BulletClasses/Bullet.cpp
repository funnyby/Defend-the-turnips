#include "../Classes/BulletClasses/Bullet.h"

bool Bullet:: init() {
    if (!Node::init()) {
        return false;
    }
    // ��ʼ��������Ա����
    attackDamage = 0;
    attackRange = 0;
    bulletType = BulletType::Normal;
    // ��ʼ���ӵ�����
    bulletSprite = Sprite::create();
    this->addChild(bulletSprite);
    return true;
}
void Bullet::attack(Node* target) {
    // �Ƴ��ӵ�
    this->removeFromParent();

    // ����˺�
   // target->takeDamage(attackDamage);
}
void Bullet::upgradeAttackDamage(int increase) {
    attackDamage += increase;
}