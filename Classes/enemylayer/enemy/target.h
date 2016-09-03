
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
	//����ı��������꣬����ʼ��������
	Vec2 brSePoint[2];
	Vec2 sePoint[2];	
	//0��0����ת����ʮ������
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
	
	//*��ǵ�������������
	CC_SYNTHESIZE(int, _kind, Kind);
	
	//*��ȡѪ��
	int getBlood();
	//*�����ƶ��ٶ�
	CC_SYNTHESIZE(float, _velocity, Velocity);
	//*�����еķ�ֵ
	CC_SYNTHESIZE(int,_hitScore,HitScore);
	//*��ɱ�÷�
	CC_SYNTHESIZE(int,_killScore,KillScore);
	//*ӵ�еķ���
	CC_SYNTHESIZE(int,_haveScore,HaveScore);
	//*�˶��ķ���
	CC_SYNTHESIZE(int,_direction,Direction);
	//*�Ƿ񱻸���
	CC_SYNTHESIZE(bool,_isFlo,isFlo);
	//*�Ƿ����б���������
	CC_SYNTHESIZE(bool,_isBezier,IsBezier);
	//*���ݷ����ȡ���
	Vec2 getStartPoint();
	//*���ݷ����ȡ��һ��
	Vec2 getNextPoint();
	//*���ݷ����ж��Ƿ��Ǳ߽�
	bool isBorder();
	//*�˶���һ��
	void animation_callback(Ref*sender);
	//*����Ѫ�������������า��
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