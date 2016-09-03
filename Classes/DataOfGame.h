
#ifndef __DATAOFGAME_H_
#define __DATAOFGAME_H_
#include"cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include"GameResource.h"
#include"enemystruct/enemystruct.h"
#include"sqlite/SqliteManager.h"
#include"2d/CCParticleSystem.h"

using namespace cocos2d;

#define PLAYER_MASK 1//炮台分类掩码
#define BULLET_MASK 3//子弹分类掩码
#define TARGET_MASK 4//敌人分类掩码
#define BOX_MASK    7

#define BULLET_CATE_MASK TARGET_MASK//子弹接触测试掩码掩码
#define TARGET_CATE_MASK BULLET_MASK//敌人接触测试掩码
#define BOX_CATE_MASK    BULLET_MASK

#define BULLET_COLL_MASK TARGET_MASK//子弹碰撞掩码
#define TARGET_COLL_MASK 0x3//敌人碰撞掩码
#define BOX_COLL_MASK    0xffffffff

#define _MAXROUND 50

class DataOfGame
{
public:
	static DataOfGame* getInstance();
	bool init();
	cocos2d::Node* seekNodebyName(cocos2d::Node*root, std::string name);
	//场景分辨率适配
	Vec2 getrealposition(Vec2 point);
	//层分辨率适配
	Vec2 LayerGetRealPosition(float x,float y);
	//获取json串
	std::string getJsonString(const char* path);	
	//清理精灵回收站
	void clearRecycle_bin();
	//加载关卡数据
	bool Load_RoundData(int _lrount);
	//解析关卡数据
	void ReadRoundData_Json(const char*);
	void setGold(int num);
	int getGold();
	//配置数据的方法
	//*分数部分
	void setGameModule2HeihtScore(int _score);
	void setGameModule3HeihtScore(int _score);
	void setGameModule4HeihtScore(int _score);
	int getGameModule2HeihtScore();
	int getGameModule3HeihtScore();
	int getGameModule4HeihtScore();
	//*用户名
	std::string getUsername();
	void setUsername(const char* _strname);
	//*音乐音效
	bool getMusicState();
	void setMusicState(bool _isplay);
	bool getEffectState();
	void setEffectState(bool _isplay);
	//*首次使用
	bool getm2new();
	void setm2new(bool _isnew);
	bool getm3new();
	void setm3new(bool _isnew);
	bool getm4new();
	void setm4new(bool _isnew);
	//*关卡数据
	void setround(int _round);
	int getround();
	//*清空容器，并移出场景
	void clearvector(Vector<Node*> _vector);
	//*读取module4敌人的数据
	//*_index 要读取的序号
	//*_nextime 得到下次读取的时间
	void loadmodule4dat(int _index,int & _nexttime);
public:
	 //*炮弹容器
	cocos2d::Vector<Node*> bulletsVector;
	 //*敌人容器
	cocos2d::Vector<Node*>targetsVector;
	 //*回收站容器
	cocos2d::Vector<Node*> recycle_bin;
	 //*触摸计数容器
	std::vector<int>countVector;

	//*金币
	int gold;
	//炮弹数量
	int _bulletTotle;
	//允许miss的个数
	int _missnum;
	//分数
	int _gameScore;

	int powerTimer;
	//游戏模式
	std::vector<enemystruct>enemyData;
	//屏幕上出现敌人限制
	int _enemyOnLayer[3];
	//敌人的总数
	int totleEnemy;//当前敌人总数
	int enemyResidue;//剩余的敌人
	int enemyOnScene;//在屏幕上敌人的总数
	//游戏模式3最高分
	int _gameModule3HeihtScore;
	//第几轮
	int _round;
	//游戏模式2最高分
	int _gameModule2HeihtScore;
	//游戏模式4最高分
	int _gameModule4HeihtScore;
	/*
	*敌人碰撞处理规则,评分规则
	*/
	int ProtRule[6];

	int multiplying_power;
	//数据库
	SqliteManager* _sqliteManager;
	//*本轮分数，只用于模式3
	int _scorenow;
private:
	DataOfGame();
	~DataOfGame();
private:
	static DataOfGame* _instance;
};
#endif