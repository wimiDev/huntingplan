
#ifndef __FREEDOMTARGET_H_
#define __FREEDOMTARGET_H_
#include "target.h"
#include"bulletlayer/bullet/Meterbullet.h"

/*
*放荡不羁的敌人
*/
class FreedomTarget :
	public target
{
public:
	FreedomTarget();
	~FreedomTarget();
	static FreedomTarget*create(const char path[50]);
	static FreedomTarget*create(const char path[50], int id, int kind, int blood, float velocity);
	void setBlood(int blood, bool isAddCombo);
	void bombAnimation();
	CC_SYNTHESIZE(float,_cvelocity,cvelocity);
	 virtual void runtoNext(Vec2 point); 
	
};
#endif
