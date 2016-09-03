
#ifndef __PROP_H_
#define __PROP_H_
#include "cocos2d.h"

using namespace cocos2d;
/*
*即时特效
*/
class Prop :
	public Ref
{
public:
	Prop();
	~Prop();

	/*
	*种类标志
	*/
	CC_SYNTHESIZE(int,_kindId,KindId);

	/*
	*数量
	*/
	CC_SYNTHESIZE(int,_count,Count);
};

#endif