
#ifndef _TARGET_H_
#define _TARGET_H_
#include"cocos2d.h"
#include"DataOfGame.h"
#include"panellayer/Score.h"
#include"gameui/GameUi.h"
#include"particle/bombparticle.h"

#define _ENEMYRUN_TAG_ 266
using  namespace cocos2d;

class target
	:public Sprite
{
public :
	target();	
	//随机的贝塞尔坐标，和起始结束坐标
	Vec2 brSePoint[2];
	Vec2 sePoint[2];	
	//0，0坐标转化成十字坐标
	Vec2 ConverPoint(float x, float y);
	Vec2 ConverPointTo_0_0(float x, float y);
	Animate* _runingAction;
	Animate* createRuningAnimate(const char* _frame1,const char* _frame2);
public:
	static int targetHitRule[7]; 
	static int targetKillRule[7];
protected:
	//*ID
	CC_SYNTHESIZE(int, _id, Id);
	
	//*标记敌人所属的种类
	CC_SYNTHESIZE(int, _kind, Kind);
	
	//*获取血量
	int getBlood();
	//*设置移动速度
	CC_SYNTHESIZE(float, _velocity, Velocity);
	//*被击中的分值
	CC_SYNTHESIZE(int,_hitScore,HitScore);
	//*击杀得分
	CC_SYNTHESIZE(int,_killScore,KillScore);
	//*拥有的分数
	CC_SYNTHESIZE(int,_haveScore,HaveScore);
	//*运动的方向
	CC_SYNTHESIZE(int,_direction,Direction);
	//*是否被跟踪
	CC_SYNTHESIZE(bool,_isFlo,isFlo);
	//*是否运行贝塞尔曲线
	CC_SYNTHESIZE(bool,_isBezier,IsBezier);
	//*根据方向获取起点
	Vec2 getStartPoint();
	//*根据方向获取下一点
	Vec2 getNextPoint();
	//*根据方向判断是否是边界
	bool isBorder();
	//*运动下一点
	void animation_callback(Ref*sender);
	//*设置血量，可以由子类覆盖
	virtual void setBlood(int blood,bool isAddCombo);
	virtual void bombAnimation();
	void moveFinish(Ref*sender);
	float getRotate(Vec2 nextPoint);
	virtual void runtoNext(Vec2 point);
protected:
	int _blood;
	
private:
	
};
#endif