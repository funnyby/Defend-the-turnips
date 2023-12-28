#ifndef __CARROT_H_
#define __CARROT_H_
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "EnterScene.h"

#define CREATE_FUNC(__TYPE__) \
static __TYPE__* create() \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
    if (pRet && pRet->init()) \
    { \
        pRet->autorelease(); \
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}

USING_NS_CC;
using namespace cocos2d::ui;
struct filesName {
    std::string fileName = { "\0" };
};
class Carrot :public Sprite
{
public:
    bool initCarrot();//init carrot state

    void setBitenAttack(float a=1.0);

    void beBiten();//used outside,hp--,change tecctures

    void setLocation(Point mapDest);//set carrot location according to different map
    
    void runTwistAnimation();
    void set_beBiten(bool set) { _beBiten = set; }
    void beTouched();   //when touched twist

    virtual void update(float dt);//update carrot state
private:

    Point CarrotPos;    //different maps'destination
    filesName bitenTectures[10];    //be biten then change
    Sprite* CarrotBloodBox;     //Carrot's blood
    Sprite* BloodNum;   //blood number
    bool _beBiten;  //true==_biten
    bool isAlive;
    float bitenDamage=1.0f;//set by monster grade


    CC_SYNTHESIZE(float, _hp, HP);    //to create a variable"_hp"and functions: setHP\ getHP

    void createBloodBox();  //create carrot's blood box basically without heart or number

    void changeBloodBox();  //change blood box with _hp changes

    void changeCarrotAppearance();

    bool isDie();

    CREATE_FUNC(Carrot);

};

extern Vector<Carrot*> myCarrot;
#endif // __CARROT_H__