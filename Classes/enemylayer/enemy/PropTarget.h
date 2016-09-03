
#ifndef __PROPTARGET_H_
#define __PROPTARGET_H_
#include "target.h"
#include"prop/FireSupport.h"
#include"prop/PowrSupport.h"
#include"panellayer/SetingBox.h"
/*
*道具敌人，携带一个增益道具
*/
class PropTarget :
	public target
{
public:

	PropTarget();
	~PropTarget();	
	static PropTarget*create(const char path[50]);
	static PropTarget*create(const char path[50], int id, int kind, int blood, float velocity);
	void bombAnimation();
	void setBlood(int blood, bool isAddCombo);
	void AddpropAction(int propId,Node* scene);
	void randProp(Ref*sender);
	void AddProp(int PropId,Node*scene);
	void propSpriteMovefinish(Ref*sender);
};

#endif