
#ifndef __BULLET_H_
#define __BULLET_H_
#include "cocos2d.h"
#include"DataOfGame.h"

using namespace cocos2d;
/*
*�����ڵ��ĸ���
*create by wimidev
*/
class Bullet :
	public Sprite
{
public:
	Bullet();
	~Bullet();
	//* ����Բ���������
	static PhysicsBody* createPcircle(float r);
	//*���������������
	static PhysicsBody*createRect(Size size);
public:
	//*�ڵ���id
	CC_SYNTHESIZE(int, _id, ID);
	//*�ڵ�������
	CC_SYNTHESIZE(int, _kind, Kind);
	//*�ڵ���ǰ��Ѫ��
	CC_SYNTHESIZE(int, _blood, Blood);
	//*�ڵ���ʼѪ��
	CC_SYNTHESIZE(int,_cblood,CBlood);
	//*�ڵ���ɱ����
	CC_SYNTHESIZE(int,_killability,Killability);
	//*�ڵ����ٶ�
	CC_SYNTHESIZE(float, _velocity, Velocity);
	//*�ڵ���ɱ�˷�Χ��δʹ�����ԣ�
	CC_SYNTHESIZE(float,_w_rotation,w_Rotation);

};
#endif