#ifndef __ENEMYLAYER_ENEMYLAYER_H_
#define __ENEMYLAYER_ENEMYLAYER_H_
#include"cocos2d.h"
#include"playscene/TargetMaker.h"
#include"playscene/PlayScene.h"

using namespace cocos2d;
/*
*敌人层，所有敌人会被加载到这个层
*create by wimidev
*/
class EnemyLayer
	:public Layer
{
public:
	//*创建敌人层
	static EnemyLayer* create();
	//*敌人层初始化
	bool init();
	//*各游戏模式添加敌人，由playscene驱动
	void GameModule_4AddEnemy();
	void GameModule_2AddEnemy();
	void GameModule_3AddEnemy();
	//*击中间谍消息
	void killspy();
	/*当前要添加到屏幕一组敌人的总数*/
	int targetTotle;
	/*当前要添加到屏幕一组敌人的剩余数量*/
	int enemyResidue;
	//*屏幕上的敌人数量
	int enemyInScene;
	//*批量添加敌人
	void addbitenemy(int _kind,int _num,int _dir,Vec2 _pos);
	
private:
	EnemyLayer();
	~EnemyLayer();
	//敌人移动完之后的处理
	void Target_Movefinish(Ref*sender);
	void GameModule4_enemyFinsh(Ref*sender);
	//贝塞尔坐标，和起始终止坐标随机抽取
	void rand_br_start_end_point(int f);

	//*随机敌人的种类
	//*返回敌人种类
	int rand_enemyKind();

	/*当前组数据临时存放空间*/
	int* tempTargetGropData;

	/*抽到某一组*/
	int F_grop;

	//是否任务完成
	int isComplete;

	//随机的贝塞尔坐标，和起始结束坐标
	Vec2 brSePoint[2];
	Vec2 sePoint[2];

	//敌人运动方向
	int direction;
};
#endif