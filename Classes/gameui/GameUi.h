
#ifndef __GAMEUI_GAMEUI_H_
#define __GAMEUI_GAMEUI_H_

#include"cocos2d.h"
#include"DataOfGame.h"
#include"ui/UIButton.h"
#include"ui/UITextAtlas.h"
#include"ui/UIText.h"
#include"panellayer/Score.h"
#include"panellayer/Gold.h"
#include"cocostudio/CocoLoader.h"
#include"cocostudio/CocoStudio.h"

using namespace cocos2d;

/*
*��Ϸui�࣬�����������ڼӷֵ�Ч��
*create by wimidev
*/

class GameUi
{
public:
	GameUi();
	~GameUi();
	//����
	Sprite*mainUi;
	//����
	static Score*score;
	//���
	static Gold*gold;
};
/*
*��Ϸui�����࣬������
*create by wimidev
*/
class UiAction
{
public:
	//*��ȡʵ��
	static UiAction* getInstance();
	//*��ʼ��
	bool  init();
	//*��������
	Action* pushin(float dt, CCCallFuncN& _callback);
	//*������
	Action* pushout(float dt, CCCallFuncN& _callback);
	//*��ť����Ч��
	Action* buttonsacle(float _scale);
private:
	//*ʵ��
	static UiAction* _instance;
};

#endif