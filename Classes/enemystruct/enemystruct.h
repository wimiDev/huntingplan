#ifndef _ENEMYSTRUCT_ENEMYSTRUCT_H_
#define _ENEMYSTRUCT_ENEMYSTRUCT_H_
#include"cocos2d.h"
using namespace cocos2d;
/*
*���˼������ݵĽṹ
*create by wimidev
*/
class enemystruct
	:public Ref
{
public:
	enemystruct();
	~enemystruct();
	//*��������
	int kind;
	//*��������
	int num;
};

#endif
