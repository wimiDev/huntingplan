
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
	*��ը���˺��ķ�Χ
	*/
	CC_SYNTHESIZE(int, _r_Bomb, r_Bomb);

	/*
	*v�ٶ�
	*r_bomb,��ըɱ��Χ
	*/
	static BombTarget* create(const char path[50],int id,int kind,int blood,float v,int r_bomb);

	/*
	*���˱�ը���˺���Χ�ڵ���
	*/
	void BeginBomb(Ref*sender);
	void setBlood(int blood,bool isAddCombo);
	void bombAnimation();
};
#endif
