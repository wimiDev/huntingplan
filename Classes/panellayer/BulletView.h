#ifndef __PANELLAYER_BULLETVIEW_H_
#define __PANELLAYER_BULLETVIEW_H_
#include"cocostudio/CocoStudio.h"
#include"cocostudio/CocoLoader.h"
#include"ui/UIText.h"
#include"DataOfGame.h"

class BulletView
	:public Sprite
{
public:
	static BulletView* create(const char*);
	static BulletView* create(Node* _rootnode);
	static BulletView* create(SpriteFrame* _spriteFrame);
	//*显示炮弹数量
	void SetBulletNum(int num);
	//*加锁效果
	void setlock(bool _isloock);
public:
	Sprite* _spritebg;
	//*用于显示炮弹数量的文本
	ui::Text* _bulletnum;
	Sprite* _slock;
private:
	int _num;
};
#endif