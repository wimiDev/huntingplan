#ifndef __BULLET_BOMB_H_
#define __BULLET_BOMB_H_

#include"DataOfGame.h"
#include"enemylayer/enemy/target.h"
#include"panellayer/PanelLayer.h"
/*
*��ը�߼�������
*�漰��ը������߼���������
*create by wimidev
*/
class Bomb
{
public:
	//*��ը�뾶����ը�壬������
	static void BeginBomb(float radius, bool isAddCombo,Node*bombBody, Node*playScene);
};
#endif