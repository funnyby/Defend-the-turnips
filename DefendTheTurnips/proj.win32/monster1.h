#include "cocos2d.h"
#include "ActionSprite.h"

class monster1 : public ActionSprite
{
public:
    //DaShu(void);
    //~DaShu(void);

    CREATE_FUNC(monster1);
    //��ʼ������
    bool init();
    //���ù⻷��ӵ�й⻷��ɫ������ֵ�ӱ�
    void setHalo(bool halo);
};