
#ifndef _METERBULLET_H_
#define _METERBULLET_H_
#include "bullet.h"

/*
*普通的炮弹类，继承自bullet类
*包含炮弹的创建，发射
*create by wimidev
*/

class MeterBullet :
	public Bullet
{
public:
	MeterBullet();
	~MeterBullet();
	//*创建炮弹
	static MeterBullet*create(const char path[50]);
	//*创建炮弹
	static MeterBullet*create(const char path[50], int id, int kind, int blood, int kill,float velocity, float w_Rotation);
	//*发射炮弹
	void shootIt();
};
#endif
