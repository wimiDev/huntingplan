
#ifndef __PROP_H_
#define __PROP_H_
#include "cocos2d.h"

using namespace cocos2d;
/*
*��ʱ��Ч
*/
class Prop :
	public Ref
{
public:
	Prop();
	~Prop();

	/*
	*�����־
	*/
	CC_SYNTHESIZE(int,_kindId,KindId);

	/*
	*����
	*/
	CC_SYNTHESIZE(int,_count,Count);
};

#endif