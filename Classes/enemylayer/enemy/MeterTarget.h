
#ifndef __METERTARGET_H_
#define __METERTARGET_H_
#include "target.h"

/*
*@最普通的敌人
*/
class MeterTarget :
	public target
{
public:
	MeterTarget();
	~MeterTarget();
	static MeterTarget* create(const char path[50]);
	static MeterTarget* create(const char path[50], int id, int kind, int blood, float velocity);
	void setBlood(int blood, bool isAddCombo);
	void bombAnimation();
	void moveFinish(Ref*sender);
	void runtoNext(Vec2 point);
	CCCallFuncN* moveCallback;
};

#endif