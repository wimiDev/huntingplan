
#ifndef __BOMBTARGET_H_
#define __BOMBTARGET_H_
#include "target.h"
#include"bulletlayer/bullet/Bomb.h"

class BombTarget :
	public target
{
public:
	BombTarget();
	~BombTarget();

	/*
	*±¨’®∫Û…À∫¶µƒ∑∂Œß
	*/
	CC_SYNTHESIZE(int, _r_Bomb, r_Bomb);

	/*
	*vÀŸ∂»
	*r_bomb,±¨’®…±∑∂Œß
	*/
	static BombTarget* create(const char path[50],int id,int kind,int blood,float v,int r_bomb);

	/*
	*µ–»À±¨’®°£…À∫¶∑∂Œßƒ⁄µ–»À
	*/
	void BeginBomb(Ref*sender);
	void setBlood(int blood,bool isAddCombo);
	void bombAnimation();
};
#endif
