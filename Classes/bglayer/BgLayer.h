#ifndef __BGLAYER_BGLAYER_H_
#define __BG_LAYER_BGLAYER_H_

#include"cocos2d.h"
#include"particle/bombparticle.h"

using namespace cocos2d;
/*
*������Ǳ�����
*��������������ʼ���Լ������Ĳ���
*create by wimidev
*/
class BgLayer 
	:public Layer
{
public:
	static BgLayer* create(const char* path);
	bool init();
	//*�������ʱ�Ķ���
	void killAction();
private:
	Sprite* bgSprite;
};
#endif