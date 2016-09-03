#ifndef __BULLETLAYER_BULLET_FIREBOMB_H_
#define __BULLETLAYER_BULLET_FIREBOMB_H_
#include"cocos2d.h"
#include"bullet.h"
#include"GameResource.h"
#include"DataOfGame.h"
#include"enemylayer/enemy/target.h"
#include"particle/bombparticle.h"
using namespace cocos2d;

/*
*导弹类，继承自bullet类
*导弹会跟踪除了间谍之外的所有敌人
*create by wimidev
*/
class FireBomb
	:public Bullet
{
public:
	//*创建弹道，返回新建导弹实例
	static FireBomb* create();
	//*设置血量
	void setBlood(int _blood);
	//*获得血量
	int getBlood();
	//*导弹移动到下一个点
	void runNextPoint(const Vec2 nextPoint);
	//*导弹扫描定时器，用于导弹锁定目标
	void timerCallback(float dt);
	//*扫描目标
	target* scanEnemy();
	//*获取杯锁定的敌人
	target* getFloEnemy();
private:	
	//*当前血量
	int _blood;
	//*初始血量
	int _cblood;
	//*刷新时间
	float flushTime;
	//*被锁定的敌人
	target* floEnemy;
};

#endif
