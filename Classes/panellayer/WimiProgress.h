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
	//*fileName csb文件路径，progName 进度条资源的名字
	static WimiProgress* create(const char* fileName,const char* progName);
	static WimiProgress* create(Sprite* sp1,Sprite* sp2);
	CC_SYNTHESIZE(float,_speed,Speed);
	Sprite* getSpriteProg();
	Sprite* getSpritBg();
	ProgressTimer* getProgressTimer();
	//普通状态下的动作
	Action* createNomalAction();
	//激活状态下的动作
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
