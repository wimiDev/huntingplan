
#include "bulletlayer/bullet/bullet.h"

class DoubleBullet :
	public Bullet
{
public:
	DoubleBullet();
	~DoubleBullet();
	static DoubleBullet*create(const char path[50], int id, int kind, int blood, int kill, float velocity, float w_Rotation);
	void shootIt();
	/*
	*��С��ɱ�������
	*/
	void ScaleSmall(float scale);
};

