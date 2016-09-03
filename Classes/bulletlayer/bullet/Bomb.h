#ifndef __BULLET_BOMB_H_
#define __BULLET_BOMB_H_

#include"DataOfGame.h"
#include"enemylayer/enemy/target.h"
#include"panellayer/PanelLayer.h"
/*
*爆炸逻辑处理类
*涉及爆炸处理的逻辑都在这里
*create by wimidev
*/
class Bomb
{
public:
	//*爆炸半径，爆炸体，主场景
	static void BeginBomb(float radius, bool isAddCombo,Node*bombBody, Node*playScene);
};
#endif