#pragma once
#ifndef __GAMEMAP2_H__
#define __GAMEMAP2_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string.h>
#include"..\Classes\Tower\Tower.h"
#include"..\Classes\Tower\BottleTower.h"
#include"..\Classes\Tower\ShitTower.h"
#include"..\Classes\Tower\SunTower.h"

#define i_max 6
#define j_max 12
#define x_min 90
#define x_max 1050
#define y_min 40
#define y_max 520

class GameMap2 :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameMap2);

	enum { EMPTY, PATH, PLACED, BARRIER };

	int map[i_max][j_max] = {
	0,0,0,0,0,0,0,0,0,0,1,0,
	0,1,1,1,1,0,0,0,0,0,1,0,
	0,1,0,0,1,1,1,1,1,0,1,0,
	0,1,0,0,0,0,0,0,1,0,1,0,
	0,1,1,0,0,0,0,0,1,1,1,0,
	0,0,1,1,1,1,1,0,0,0,0,0
	};

	//�ؿ�ѡ��
	int if_speed_up;//�Ƿ����
	bool isGamePaused = false;//�Ƿ���ͣ
	//��Ϸ������
	int game_money;//��Ǯ
	int current_wave;//��ǰ����

	int max_waves;//�ܲ���
	int carrot_hp;//��¼�ܲ�Ѫ��
	//pos carrot_position;//��¼�ܲ�λ��
	//Enemy* destination;
	//vector<Enemy*> barrier;
	//vector<Enemy*> monster;
	//��Ϸͳ������
	int money_total;//��ɱ��ý�Ǯ����
	int monster_total;//��ɱ��������
	int boss_total;//��ɱboss����
	int barrier_total;//�ݻ��ϰ�����

private:
	cocos2d::ui::Button* pausebtn;
	cocos2d::ui::Button* menubtn;
	cocos2d::Sprite* setTower;
	cocos2d::Sprite* range;
	cocos2d::ui::Button* bottlebtn;
	cocos2d::ui::Button* shitbtn;
	cocos2d::ui::Button* sunbtn;
	cocos2d::ui::Button* upgradebtn;
	cocos2d::ui::Button* cancelbtn;
	cocos2d::ui::Button* maxbtn;
	cocos2d::Vec2 selectedPosition; // ѡ�е�λ��
	void InitUI();
	void InitBackground();      // ��ʼ������
	void InitEvent();


	// ����������
	cocos2d::Vector<BottleTower*> bottletowers;
	cocos2d::Vector<ShitTower*> shittowers;
	cocos2d::Vector<SunTower*> suntowers;

	// ����¼��ص�����
	bool onTouchBegan(Touch* touch, Event* event);
	int getStatus(int x, int y);
	bool is_out_of_range(int x, int y);
	void transform_ij_to_xy(const int i, const int j, int& x, int& y);
	void transform_xy_to_ij(int& i, int& j, const int x, const int y);
	void bottlebuttonClickCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type, int i, int j, int placex, int placey);
	void shitbuttonClickCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type, int i, int j, int placex, int placey);
	void sunbuttonClickCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type, int i, int j, int placex, int placey);

	void hideButton();
	void upgradeBottle(BottleTower* bt);
	void upgradeShit(ShitTower* st);
	void upgradeSun(SunTower* st);

	void upgradebuttonClickCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type, const std::string& towerImage, BottleTower* bt, ShitTower* st, SunTower* sunt);
	void cancelbuttonClickCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type, BottleTower* bt, ShitTower* st,SunTower*sunt);

	void setUpgradeButton(const std::string& btnImage, const std::string& towerImage, int pos_x, int pos_y, bool can_be_clicked, BottleTower* bt, ShitTower* st, SunTower* sunt);
	void setRange(float scale, int pos_x, int pos_y);
	void setCancelButton(const std::string& btnImage, int pos_x, int pos_y, BottleTower* bt, ShitTower* st, SunTower* sunt);
	void setPauseButton(cocos2d::Layer* layerUI);
	void setMenuButton(cocos2d::Layer* layerUI);


	//��������������й�
	int boshu;
	void init_m1(float delta);

	void init_m2(float delta);

	void init_m3(float delta);

	void bo(float a);

	void next_bo(float a);

	//����ʱ
	void countDown();
};
#endif  __GAMEMAP2_H__
