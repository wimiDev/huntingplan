#ifndef __BGLAYER_BGLAYER_H_
#define __BG_LAYER_BGLAYER_H_

#include"cocos2d.h"
#include"particle/bombparticle.h"

using namespace cocos2d;
/*
*这个类是背景类
*包含背景创建初始化以及动作的播放
*create by wimidev
*/
class BgLayer 
	:public Layer
{
public:
	static BgLayer* create(const char* path);
	bool init();
	//*击落敌人时的动作
	void killAction();
private:
	Sprite* bgSprite;
};
#endif