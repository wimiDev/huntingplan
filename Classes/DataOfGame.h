
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

#define PLAYER_MASK 1//��̨��������
#define BULLET_MASK 3//�ӵ���������
#define TARGET_MASK 4//���˷�������
#define BOX_MASK    7

#define BULLET_CATE_MASK TARGET_MASK//�ӵ��Ӵ�������������
#define TARGET_CATE_MASK BULLET_MASK//���˽Ӵ���������
#define BOX_CATE_MASK    BULLET_MASK

#define BULLET_COLL_MASK TARGET_MASK//�ӵ���ײ����
#define TARGET_COLL_MASK 0x3//������ײ����
#define BOX_COLL_MASK    0xffffffff

#define _MAXROUND 50

class DataOfGame
{
public:
	static DataOfGame* getInstance();
	bool init();
	cocos2d::Node* seekNodebyName(cocos2d::Node*root, std::string name);
	//�����ֱ�������
	Vec2 getrealposition(Vec2 point);
	//��ֱ�������
	Vec2 LayerGetRealPosition(float x,float y);
	//��ȡjson��
	std::string getJsonString(const char* path);	
	//���������վ
	void clearRecycle_bin();
	//���عؿ�����
	bool Load_RoundData(int _lrount);
	//�����ؿ�����
	void ReadRoundData_Json(const char*);
	void setGold(int num);
	int getGold();
	//�������ݵķ���
	//*��������
	void setGameModule2HeihtScore(int _score);
	void setGameModule3HeihtScore(int _score);
	void setGameModule4HeihtScore(int _score);
	int getGameModule2HeihtScore();
	int getGameModule3HeihtScore();
	int getGameModule4HeihtScore();
	//*�û���
	std::string getUsername();
	void setUsername(const char* _strname);
	//*������Ч
	bool getMusicState();
	void setMusicState(bool _isplay);
	bool getEffectState();
	void setEffectState(bool _isplay);
	//*�״�ʹ��
	bool getm2new();
	void setm2new(bool _isnew);
	bool getm3new();
	void setm3new(bool _isnew);
	bool getm4new();
	void setm4new(bool _isnew);
	//*�ؿ�����
	void setround(int _round);
	int getround();
	//*������������Ƴ�����
	void clearvector(Vector<Node*> _vector);
	//*��ȡmodule4���˵�����
	//*_index Ҫ��ȡ�����
	//*_nextime �õ��´ζ�ȡ��ʱ��
	void loadmodule4dat(int _index,int & _nexttime);
public:
	 //*�ڵ�����
	cocos2d::Vector<Node*> bulletsVector;
	 //*��������
	cocos2d::Vector<Node*>targetsVector;
	 //*����վ����
	cocos2d::Vector<Node*> recycle_bin;
	 //*������������
	std::vector<int>countVector;

	//*���
	int gold;
	//�ڵ�����
	int _bulletTotle;
	//����miss�ĸ���
	int _missnum;
	//����
	int _gameScore;

	int powerTimer;
	//��Ϸģʽ
	std::vector<enemystruct>enemyData;
	//��Ļ�ϳ��ֵ�������
	int _enemyOnLayer[3];
	//���˵�����
	int totleEnemy;//��ǰ��������
	int enemyResidue;//ʣ��ĵ���
	int enemyOnScene;//����Ļ�ϵ��˵�����
	//��Ϸģʽ3��߷�
	int _gameModule3HeihtScore;
	//�ڼ���
	int _round;
	//��Ϸģʽ2��߷�
	int _gameModule2HeihtScore;
	//��Ϸģʽ4��߷�
	int _gameModule4HeihtScore;
	/*
	*������ײ�������,���ֹ���
	*/
	int ProtRule[6];

	int multiplying_power;
	//���ݿ�
	SqliteManager* _sqliteManager;
	//*���ַ�����ֻ����ģʽ3
	int _scorenow;
private:
	DataOfGame();
	~DataOfGame();
private:
	static DataOfGame* _instance;
};
#endif