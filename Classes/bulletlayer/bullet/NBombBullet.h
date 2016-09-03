
#include "bulletlayer/bullet/bullet.h"

class NBombBullet :
	public Bullet
{
public:
	NBombBullet();
	~NBombBullet();
	CC_SYNTHESIZE(float,_r_bomb,R_Bomb);
	static NBombBullet* create(const char path[50], 
		int id, 
		int kind, 
		int blood, 
		int kill,
		float velocity,
		float w_Rotation,
		float rBomb);
	void shootIt();

};

