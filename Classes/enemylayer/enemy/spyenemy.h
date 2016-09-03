#ifndef __ENEMYLAYER_ENEMY_SPYENEMY_H_
#define __ENEMYLAYER_ENEMY_SPYENEMY_H_
#include"cocos2d.h"
#include"target.h"
#include"GameResource.h"
//#include"MeterTarget.h"
#include"playscene/TargetMaker.h"

using namespace cocos2d;
class SpyEnemy
	:public target
{
public:
	SpyEnemy();
	~SpyEnemy();
	static SpyEnemy* create();
	void setBlood(int val,bool _addcombo=true);
	int  getBlood();
	void bombAnimation();
	void createEnemy(int num);
	void boomCallback(Ref*sender);
	void followEnemy(float dt);
private:
	Sprite* spyLogo;
	float followTime;
};
#endif