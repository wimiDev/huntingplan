
#ifndef _METERBULLET_H_
#define _METERBULLET_H_
#include "bullet.h"

/*
*��ͨ���ڵ��࣬�̳���bullet��
*�����ڵ��Ĵ���������
*create by wimidev
*/

class MeterBullet :
	public Bullet
{
public:
	MeterBullet();
	~MeterBullet();
	//*�����ڵ�
	static MeterBullet*create(const char path[50]);
	//*�����ڵ�
	static MeterBullet*create(const char path[50], int id, int kind, int blood, int kill,float velocity, float w_Rotation);
	//*�����ڵ�
	void shootIt();
};
#endif
