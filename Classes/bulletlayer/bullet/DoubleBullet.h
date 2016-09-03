
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
	*变小，杀伤力变大
	*/
	void ScaleSmall(float scale);
};

