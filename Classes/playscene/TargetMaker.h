
#ifndef __TARGETMAKER_H_
#define __TARGETMAKER_H_
#include"cocos2d.h"
#include"DataOfGame.h"
#include"enemylayer/enemy/MeterTarget.h"
#include"enemylayer/enemy/FreedomTarget.h"
#include"enemylayer/enemy/PropTarget.h"
#include"bulletlayer/bullet/Meterbullet.h"
#include"enemylayer/enemy/BombTarget.h"
#include"enemylayer/enemy/TimidTarget.h"
#include"enemylayer/enemy/spyenemy.h"
#include"enemylayer/enemy/RepairEnemy.h"

class TargetMaker
{
public:
	TargetMaker();
	~TargetMaker();
	static TargetMaker* getinstance();
	 target* Make_Target(int kind);
	/*
	*�����������˶�
	*kind��int�� ����
	*dire��int�� ���� 1��->�ң� 0��->��
	*end_Y �յ�Y����
	*/
	static ccBezierConfig* Maker_bezier(Vec2 point[2], Vec2 endPoint);
	static PhysicsBody* createPcircle(float r);
	float getEnemyAttribute(int kind,char* Attribute,std::string _jsonString);
	void loadenemytexture();
	void unloadenemytexture();
	Sprite* loadenemyformainscene(int kind);
private:
	static TargetMaker* _instance;
};
#endif