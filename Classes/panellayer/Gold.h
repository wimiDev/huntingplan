#ifndef __GOLD_H_
#define __GOLD_H_

#include"cocos2d.h"
#include"ui/UIText.h"
#include"GameResource.h"
#include"DataOfGame.h"
#include"cocostudio/CocoStudio.h"
#include"cocostudio/CocoLoader.h"

using namespace cocos2d;
//���
class Gold
	:public Node
{
public:
	static Gold* create();
	//*���ý��
	void setGlodNum(int _num);
	//*��ʾ���
	void showGold(int _num);
	
	Sprite* _sprite_bg;
	Sprite* _spritelogo;
	ui::Text* _textgold;
private:

};
#endif