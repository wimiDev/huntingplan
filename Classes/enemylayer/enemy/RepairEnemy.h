
#ifndef __RepairEnemy_H_
#define __RepairEnemy_H_
#pragma once
#include "enemylayer/enemy/target.h"
#include"DataOfGame.h"
#include"GameResource.h"
class RepairEnemy :
	public target
{
public:
	RepairEnemy();
	~RepairEnemy();
	static RepairEnemy* create();
	void setBlood(int val,bool isAddCombo);
	void bombAnimation();
	void RepairTimer(float dt);
	void Repair(Ref*sender);
private:
	CC_SYNTHESIZE(float, _w_rotation, w_Rotation);
	float _repairTime;
	int _oldBlood;
};
#endif