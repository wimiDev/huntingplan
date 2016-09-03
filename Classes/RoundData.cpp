#include"RoundData.h"



bool RoundData::Load_RoundData(int _lrount)
{
	ssize_t file_size = 0;
	char roundStr[100];
	sprintf(roundStr, "rounddata/round_data%d.json", _lrount);
	unsigned char* pBytes = cocos2d::FileUtils::sharedFileUtils()->getFileData(roundStr, "r", &file_size);
	if (pBytes == nullptr || strcmp((char*)pBytes, "") == 0)
	{
		log("file is empy or read error!");
		//TODO:严重数据错误，应该终止游戏
		return false;
	}
	std::string dataByTarget((const char*)pBytes, file_size);
	RoundData::ReadRoundData_Json(dataByTarget.c_str());
	RoundData::enemyResidue = RoundData::totleEnemy;
	return true;
}
void RoundData::ReadRoundData_Json(const char*jsonString)
{
	rapidjson::Document d;
	d.Parse<0>(jsonString);
	if (d.HasParseError())
	{
		log("jsonData Error");
		return;
	}
	if (!d.HasMember("round"))
	{
		log("dataError!");
		return;
	}

	//读取第几关
	int j_round = d["round"].GetInt();
	if (j_round != _round)
	{
		log("round value has error");
		return;
	}
	if (!d.HasMember("bullet") || !d["bullet"].IsInt())
	{
		log("not bullet or bullet not int");
		return;
	}
	//读取炮弹数量
	v_Bullet[0] = d["bullet"].GetInt();

	//读取敌人数据
	if (!d.HasMember("Enemy") || !d["Enemy"].IsArray())
	{
		log("d not has Enemy or Enemy not Array");
		return;
	}
	rapidjson::Value& j_enemy = d["Enemy"];
	enemyData.clear();//清理容器
	RoundData::totleEnemy = 0;
	for (int i = 0; i < j_enemy.Size(); ++i)
	{
		rapidjson::Value& j_enemyObj = j_enemy[i];
		if (!j_enemyObj.IsObject())
		{
			log("j_enemyObj not a obj!");
			return;
		}
		enemystruct enemyStruct = enemystruct();
		enemyStruct.kind = j_enemyObj["kind"].GetInt();
		enemyStruct.num = j_enemyObj["num"].GetInt();
		RoundData::totleEnemy += enemyStruct.num;
		enemyData.push_back(enemyStruct);
	}
	//读取屏幕上敌人数量极限数据
	if (!d.HasMember("EnemyNum"))
	{
		log("not EnemyNum");
		return;
	}
	rapidjson::Value& j_enemyOnLayer = d["EnemyNum"];
	for (int j = 0; j < j_enemyOnLayer.Size(); ++j)
	{
		if (!j_enemyOnLayer[j].IsInt())
		{
			log("EnemyNum not int");
			return;
		}
		_enemyOnLayer[j] = j_enemyOnLayer[j].GetInt();
	}
}