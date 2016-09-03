#ifndef _PANELLAYER_WIMIPROGRESS_H_
#define _PANELLAYER_WIMIPROGRESS_H_

#include"cocos2d.h"
#include"cocostudio/CocoStudio.h"
#include"cocostudio/CocoLoader.h"
#include"ui/UIText.h"
#include"ui/UIButton.h"
#include"DataOfGame.h"
using namespace cocos2d;

class WimiProgress
	:public Node
{
public:
	void setNum(int _val,float percent);
	int getNum();
	//*fileName csb�ļ�·����progName ��������Դ������
	static WimiProgress* create(const char* fileName,const char* progName);
	static WimiProgress* create(Sprite* sp1,Sprite* sp2);
	CC_SYNTHESIZE(float,_speed,Speed);
	Sprite* getSpriteProg();
	Sprite* getSpritBg();
	ProgressTimer* getProgressTimer();
	//��ͨ״̬�µĶ���
	Action* createNomalAction();
	//����״̬�µĶ���
	Action* createLightAction();
	ui::Text*  l_number;
private:
	int _num;
	ProgressTimer* progressTimer;
	Sprite* progess_bg;
	Sprite* sprite_prog;
	void ChangeNomal(Ref*sender);
	void ChangeLight(Ref*sender);
};

#endif
