
#ifndef __BULLET_H_
#define __BULLET_H_
#include "cocos2d.h"
#include"DataOfGame.h"

using namespace cocos2d;
/*
*所有炮弹的父类
*create by wimidev
*/
class Bullet :
	public Sprite
{
public:
	Bullet();
	~Bullet();
	//* 创建圆形物理刚体
	static PhysicsBody* createPcircle(float r);
	//*创建矩形物理刚体
	static PhysicsBody*createRect(Size size);
public:
	//*炮弹的id
	CC_SYNTHESIZE(int, _id, ID);
	//*炮弹的种类
	CC_SYNTHESIZE(int, _kind, Kind);
	//*炮弹当前的血量
	CC_SYNTHESIZE(int, _blood, Blood);
	//*炮弹初始血量
	CC_SYNTHESIZE(int,_cblood,CBlood);
	//*炮弹的杀伤力
	CC_SYNTHESIZE(int,_killability,Killability);
	//*炮弹的速度
	CC_SYNTHESIZE(float, _velocity, Velocity);
	//*炮弹的杀伤范围（未使用属性）
	CC_SYNTHESIZE(float,_w_rotation,w_Rotation);

};
#endif