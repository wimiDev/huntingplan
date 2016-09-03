#ifndef __ROUNDDATA_H_
#define __ROUNDDATA_H_
#include"cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include"enemystruct/enemystruct.h"

using namespace cocos2d;
class RoundData
{
public:

	static RoundData* getInstance();
	bool Load_RoundData(int _lrount);
	//解析关卡数据
	void ReadRoundData_Json(const char*);
	int totleEnemy;
	int enemyResidue;
	int _round;
	std::vector<enemystruct>enemyData;
	int v_Bullet[3];
	int _enemyOnLayer[3];
private:
	RoundData();
};

#endif