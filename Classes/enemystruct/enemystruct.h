#ifndef _ENEMYSTRUCT_ENEMYSTRUCT_H_
#define _ENEMYSTRUCT_ENEMYSTRUCT_H_
#include"cocos2d.h"
using namespace cocos2d;
/*
*敌人加载数据的结构
*create by wimidev
*/
class enemystruct
	:public Ref
{
public:
	enemystruct();
	~enemystruct();
	//*敌人种类
	int kind;
	//*敌人数量
	int num;
};

#endif
