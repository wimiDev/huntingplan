
#ifndef __TURRET_H_
#define __TURRET_H_
#include"cocos2d.h"

using namespace cocos2d;
class Turret
	:public Sprite
{
public:
	Turret();
	~Turret();
	static Turret*create(const char path[50]);
	static Turret*create(Sprite* _sp2);
	static float _velocity;
	static float _fireVel;
	static int _total;
	static bool isFire;
	static int _velocityList[4];
	Sprite* _cannon2;
public:
	float GetRotate(Vec2 _point1, Vec2 _point2);
	void Rotate(float rotate,CCCallFuncN* fire);
	void Fire();
};

#endif
