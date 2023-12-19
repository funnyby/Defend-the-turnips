#include "cocos2d.h"
#include "ActionSprite.h"

class monster1 : public ActionSprite
{
public:
    //DaShu(void);
    //~DaShu(void);

    CREATE_FUNC(monster1);
    //初始化方法
    bool init();
    //设置光环，拥有光环的色狼生命值加倍
    void setHalo(bool halo);
};