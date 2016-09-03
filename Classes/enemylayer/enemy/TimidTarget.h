#ifndef __TARGET_TIMIDTARGET_H_
#define __TARGET_TIMIDTARGET_H_

#include"cocos2d.h"
#include"DataOfGame.h"
#include"target.h"
using namespace cocos2d;

class TimidTarget
	:public target
{
public:
	TimidTarget();
	~TimidTarget();
	static TimidTarget* create(const char path[50]);
	static TimidTarget* create(const char path[50], int id, int kind, int blood, float velocity);
	void setBlood(int _blood,bool isAddCombo);
	void moveFast();
	void moveFinish(Ref*sender);
	void addBlood(Ref*sender);
	void bombAnimation();
private:
	Sprite* addBloodLogo;
};

#endif