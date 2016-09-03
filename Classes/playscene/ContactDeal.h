
#ifndef __CONTACTDEAL_H_
#define __CONTACTDEAL_H_
#include"cocos2d.h"
#include"DataOfGame.h"
#include"gameui/GameUi.h"

#include"enemylayer/enemy/MeterTarget.h"
#include"enemylayer/enemy/FreedomTarget.h"
#include"enemylayer/enemy/PropTarget.h"
#include"enemylayer/enemy/BombTarget.h"

#include"bulletlayer/bullet/Meterbullet.h"
#include"bulletlayer/bullet/DoubleBullet.h"
#include"bulletlayer/bullet/NBombBullet.h"
#include"prop/FireSupport.h"
#include"prop/PowrSupport.h"

#include"bulletlayer/bullet/Bomb.h"

using namespace cocos2d;

class ContactDeal
{
public:
	ContactDeal();
	~ContactDeal();
	/*
	*��ײ��������������Ѫ��������
	*/

	static void bulletContact(Node*A,Node*B,Node*scene);
	static void targetContact(Node*A,Node*B,Node*scene);
	static void AddProp(int _propId, Node*target);
	//static void taskDeal(int missionKind,int maxKind);
	/*��ը�뾶����������������ը�壬������*/
	static void bomb(float radius,int maxSize,Node*bombBody,Node*playScene);
	static void AddpropAction(int kind,Node*target,Node*playScene);
	
};
#endif
