#ifndef __BULLETLAYER_BULLETLAYER_H_
#define __BULLETLAYER_BULLETLAYER_H_
#include"cocos2d.h"
#include"bullet/MeterBullet.h"
#include"panellayer/PanelLayer.h"
#include"particle/bombparticle.h"

using namespace cocos2d;
/*
*��������ڵ���
*�����ڵ��㴴����ʼ��
*create by wimidev
*/
class BulletLayer
	:public Layer
{
public:
	//*�����ڵ���
	static BulletLayer*create();
	//*�ڵ����ʼ��
	bool init();
	//*����ڵ�
	void addBullet();
	//*׼������
	void readyShoot(Vec2 point);
	//0��0����ת����ʮ������
	Vec2 ConverPoint(float x, float y);
private:
	//*������ת��λ
	void turretRotateFinish(Ref*sender);
	//*��Ӵ�����Ч
	void addAimCircle(Vec2 point);
};

#endif
