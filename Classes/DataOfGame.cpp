#include "DataOfGame.h"


DataOfGame::DataOfGame()
{
	this->init();
}

DataOfGame::~DataOfGame()
{
}
DataOfGame* DataOfGame::_instance = nullptr;
DataOfGame* DataOfGame::getInstance()
{
	if(_instance==nullptr)
	_instance = new DataOfGame();
	return _instance;
}
cocos2d::Node* DataOfGame::seekNodebyName(cocos2d::Node*root, std::string name)
{
	if (!root)
		return nullptr;
	if (root->getName() == name)
		return root;
	const auto& arrayNode = root->getChildren();
	for (auto& child : arrayNode)
	{
		cocos2d::Node*pNode = static_cast<cocos2d::Node*>(child);
		if (pNode)
		{
			cocos2d::Node* res = seekNodebyName(pNode, name);
			if (res)
				return res;
		}
	}
	return nullptr;
}
//*
//*获取精灵真实位置，仅适用于NO_BORDER分辨率适配模式
//*
Vec2 DataOfGame::getrealposition(Vec2 point)//获取真实位置
{
	Vec2 _realPoint = point;
	Size visiableSize = Director::getInstance()->getVisibleSize();
	Size DisSize = Director::getInstance()->getWinSize();
	Vec2 Org = Director::getInstance()->getVisibleOrigin();
	float scaleX = 1.0* point.x / DisSize.width;
	float scaleY = 1.0* point.y / DisSize.height;
	float virtualX = scaleX*visiableSize.width;
	float virtualY = scaleY*visiableSize.height;
	if (std::abs(virtualX)> visiableSize.width )
	{
		if (virtualX>0)
			virtualX = visiableSize.width ;
		else
			virtualX = -visiableSize.width ;
	}
	else
	{
		virtualX += Org.x;
	}
	if (std::abs(virtualY) > visiableSize.height )
	{
		if (virtualY > 0)
			virtualY = visiableSize.height ;
		else
			virtualY = -visiableSize.height ;
	}
	else
	{
		virtualY += Org.y;
	}
	_realPoint.x = virtualX;
	_realPoint.y = virtualY;
	return _realPoint;
}
Vec2 DataOfGame::LayerGetRealPosition(float x, float y)
{
	Size visiableSize = Director::getInstance()->getVisibleSize();
	Size DisSize = Director::getInstance()->getWinSize();
	Vec2 Org = Director::getInstance()->getVisibleOrigin();
	Vec2 _realPoint =  Vec2();
	float scaleX = 1.0* x / DisSize.width;
	float scaleY = 1.0* y / DisSize.height;
	float virtualX = scaleX*visiableSize.width;
	float virtualY = scaleY*visiableSize.height;
	if (std::abs(virtualX)> visiableSize.width / 2)
	{
		if (virtualX>0)
			virtualX = visiableSize.width / 2;
		else
			virtualX = -visiableSize.width / 2;
	}
	if (std::abs(virtualY) > visiableSize.height / 2)
	{
		if (virtualY > 0)
			virtualY = visiableSize.height / 2;
		else
			virtualY = -visiableSize.height / 2;
	}
	_realPoint.x = virtualX;
	_realPoint.y = virtualY;
	return _realPoint;
}
void DataOfGame::clearRecycle_bin()
{
	for (int i = 0; i < recycle_bin.size();i++)
	{
		auto recycle=recycle_bin.at(i);
			bulletsVector.eraseObject(recycle,true);
			targetsVector.eraseObject(recycle,true);
			recycle->removeFromParentAndCleanup(true);
		//	delete(recycle);
	}
	recycle_bin.clear();
}
//*清空容器，并移出场景
void DataOfGame::clearvector(Vector<Node*> _vector)
{
	for (int _index = 0; _index < _vector.size(); _index++)
	{
		Node* _item = _vector.at(_index);
		this->recycle_bin.pushBack(_item);
	}
}
std::string DataOfGame::getJsonString(const char* path)
{
	ssize_t file_size = 0;
	unsigned char* pBytes = cocos2d::FileUtils::sharedFileUtils()->getFileData(path, "r", &file_size);
	if (pBytes == nullptr || strcmp((char*)pBytes, "") == 0)
	{
		log("file is empy or read error!");
		//TODO:严重数据错误，应该终止游戏
		return nullptr;
	}
	std::string dataByTarget((const char*)pBytes, file_size);
	return dataByTarget;
}
bool DataOfGame::Load_RoundData(int _lrount)
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
	DataOfGame::ReadRoundData_Json(dataByTarget.c_str());
	DataOfGame::enemyResidue = DataOfGame::totleEnemy;
	return true;
}
void DataOfGame::ReadRoundData_Json(const char*jsonString)
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
	_bulletTotle = d["bullet"].GetInt();

	//读取敌人数据
	if (!d.HasMember("Enemy") || !d["Enemy"].IsArray())
	{
		log("d not has Enemy or Enemy not Array");
		return;
	}
	rapidjson::Value& j_enemy = d["Enemy"];
	enemyData.clear();//清理容器
	DataOfGame::totleEnemy = 0;
	for (int i = 0; i < j_enemy.Size(); ++i)
	{
		rapidjson::Value& j_enemyObj = j_enemy[i];
		if (!j_enemyObj.IsObject())
		{
			log("j_enemyObj not a obj!");
			return;
		}
		enemystruct enemyStruct = enemystruct();
		enemyStruct.kind=j_enemyObj["kind"].GetInt();
		enemyStruct.num = j_enemyObj["num"].GetInt();
		DataOfGame::totleEnemy += enemyStruct.num;
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
void DataOfGame::loadmodule4dat(int _index, int & _nexttime)
{
	std::string _json = getJsonString("rounddata/addbytime.json");
	rapidjson::Document d;
	d.Parse<0>(_json.c_str());
	if (d.HasParseError())
	{
		log("jsonData Error");
		return;
	}
	if (!d.HasMember("enemy"))
	{
		CCLOG("not member enemy");
		return;
	}
	rapidjson::Value& _list = d["enemy"];
	if (!_list.IsArray())
	{
		log("jsonData Error");
		return;
	}	
	if (_index >= _list.Size())
	{
		CCLOG("_index too biger");
		return;
	}
	rapidjson::Value& _enemynum = _list[_index];
	if (!_enemynum.HasMember("num"))
	{
		CCLOG("_enemynum not 'num'");
		return;
	}
	totleEnemy = _enemynum["num"].GetInt();
	if (!_enemynum.HasMember("nexttime"))
	{
		CCLOG("_enemynum not 'nexttime'");
		return;
	}
	_nexttime = _enemynum["nexttime"].GetInt();
}
void DataOfGame::setGameModule2HeihtScore(int _score)
{
	if(_score<=0||_score>999999)
	UserDefault::getInstance()->setIntegerForKey("gamemodule2heihtscore",0);
	UserDefault::getInstance()->setIntegerForKey("gamemodule2heihtscore",_score);
}
void DataOfGame::setGameModule3HeihtScore(int _score)
{
	if (_score <= 0 || _score>999999)
		UserDefault::getInstance()->setIntegerForKey("gamemodule3heihtscore", 0);
	UserDefault::getInstance()->setIntegerForKey("gamemodule3heihtscore", _score);
}
void DataOfGame::setGameModule4HeihtScore(int _score)
{
	if (_score <= 0 || _score>999999)
		UserDefault::getInstance()->setIntegerForKey("gamemodule4heihtscore", 0);
	UserDefault::getInstance()->setIntegerForKey("gamemodule4heihtscore", _score);
}
int DataOfGame::getGameModule2HeihtScore()
{
	int score = UserDefault::getInstance()->getIntegerForKey("gamemodule2heihtscore");
	if (score < 0)
		score=0;
	if (score > 999999)
		score = 999999;
	_gameModule2HeihtScore = score;
	return score;
}
int DataOfGame::getGameModule3HeihtScore()
{
	int score = UserDefault::getInstance()->getIntegerForKey("gamemodule3heihtscore");
	if (score < 0)
		score = 0;
	if (score > 999999)
		score = 999999;
	_gameModule3HeihtScore = score;
	return score;
}
int DataOfGame::getGameModule4HeihtScore()
{
	int score = UserDefault::getInstance()->getIntegerForKey("gamemodule4heihtscore");
	if (score < 0)
		score = 0;
	if (score > 999999)
		score = 999999;
	_gameModule4HeihtScore = score;
	return score;
}
void DataOfGame::setGold(int num)
{
	//TODO:
	//向服务器请求写入数据
	int dgold = 0;
	if (num < 0 || num>99999999)
	{
		dgold = 99999999;
	}
	else
	{
		dgold = num;
	}
	DataOfGame::gold = dgold;
	UserDefault::getInstance()->setIntegerForKey("Gold",dgold);
}
int DataOfGame::getGold()
{
	//TODO:
	//向服务器请求数据
	int dgold = UserDefault::getInstance()->getIntegerForKey("Gold");
	if (dgold < 0 || dgold>99999999)
	{
		dgold = 99999999;
		UserDefault::getInstance()->setIntegerForKey("Gold", dgold);
	}
	DataOfGame::gold = dgold;
	return dgold;
}
//*用户名
std::string DataOfGame::getUsername()
{
	std::string _username = UserDefault::getInstance()->getStringForKey("UserName");
	return _username;
}
void DataOfGame::setUsername(const char* _strname)
{
	std::string _username = _strname;
	UserDefault::getInstance()->setStringForKey("UserName", _username);
}
//*音乐音效
bool DataOfGame::getMusicState()
{
	bool _isplay = false;
	_isplay = UserDefault::getInstance()->getBoolForKey("Music",true);
	return _isplay;
}
void DataOfGame::setMusicState(bool _isplay)
{
	UserDefault::getInstance()->setBoolForKey("Music", _isplay);
}
bool DataOfGame::getEffectState()
{
	bool _isplay = false;
	_isplay = UserDefault::getInstance()->getBoolForKey("Effect",true);
	return _isplay;
}
void DataOfGame::setEffectState(bool _isplay)
{
	UserDefault::getInstance()->setBoolForKey("Effect", _isplay);
}
bool DataOfGame::getm2new()
{
	bool _isnew = true;
	_isnew = UserDefault::getInstance()->getBoolForKey("module2new",true);
	return _isnew;
}
void DataOfGame::setm2new(bool _isnew)
{
	UserDefault::getInstance()->setBoolForKey("module2new",_isnew);
}
bool DataOfGame::getm3new()
{
	bool _isnew = true;
	_isnew = UserDefault::getInstance()->getBoolForKey("module3new", true);
	return _isnew;
}
void DataOfGame::setm3new(bool _isnew)
{
	UserDefault::getInstance()->setBoolForKey("module3new", _isnew);
}
bool DataOfGame::getm4new()
{
	bool _isnew = true;
	_isnew = UserDefault::getInstance()->getBoolForKey("module4new", true);
	return _isnew;
}
void DataOfGame::setm4new(bool _isnew)
{
	UserDefault::getInstance()->setBoolForKey("module4new", _isnew);
}
void DataOfGame::setround(int _round)
{
	this->_round = _round;
	UserDefault::getInstance()->setIntegerForKey("round",_round);
}
int DataOfGame::getround()
{
	int _roundnum = 1;
	_roundnum = UserDefault::getInstance()->getIntegerForKey("round",1);
	this->_round = _roundnum;
	return _roundnum;
}
bool DataOfGame::init()
{
	bulletsVector = cocos2d::Vector<Node*>();
	targetsVector = cocos2d::Vector<Node*>();
	recycle_bin = cocos2d::Vector<Node*>();
	countVector = std::vector<int>();
	enemyData = std::vector<enemystruct>();
	totleEnemy = 0;
	enemyResidue = 0;
	enemyOnScene = 0;
	gold = 0;
	_gameScore = 0;
	//PropId = -1;
	powerTimer = 0;
	_round = 0;
	multiplying_power = 1;
	_gameModule2HeihtScore = 0;
	_gameModule3HeihtScore = 0;
	_gameModule4HeihtScore = 0;
	getGameModule2HeihtScore();
	getGameModule3HeihtScore();
	getGameModule4HeihtScore();
	_sqliteManager =new SqliteManager();
	//*本轮分数，只用于模式3
	_scorenow=0;
	_missnum = 0;
	return true;
}

