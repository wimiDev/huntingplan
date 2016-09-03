#ifndef __BULLETLAYER_BULLET_FIREBOMB_H_
#define __BULLETLAYER_BULLET_FIREBOMB_H_
#include"cocos2d.h"
#include"bullet.h"
#include"GameResource.h"
#include"DataOfGame.h"
#include"enemylayer/enemy/target.h"
#include"particle/bombparticle.h"
using namespace cocos2d;

/*
*�����࣬�̳���bullet��
*��������ٳ��˼��֮������е���
*create by wimidev
*/
class FireBomb
	:public Bullet
{
public:
	//*���������������½�����ʵ��
	static FireBomb* create();
	//*����Ѫ��
	void setBlood(int _blood);
	//*���Ѫ��
	int getBlood();
	//*�����ƶ�����һ����
	void runNextPoint(const Vec2 nextPoint);
	//*����ɨ�趨ʱ�������ڵ�������Ŀ��
	void timerCallback(float dt);
	//*ɨ��Ŀ��
	target* scanEnemy();
	//*��ȡ�������ĵ���
	target* getFloEnemy();
private:	
	//*��ǰѪ��
	int _blood;
	//*��ʼѪ��
	int _cblood;
	//*ˢ��ʱ��
	float flushTime;
	//*�������ĵ���
	target* floEnemy;
};

#endif
