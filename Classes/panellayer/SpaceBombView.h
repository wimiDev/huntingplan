#ifndef __PANELLAYER_BOMBBULLETVIEW_H_
#define __PANELLAYER_BOMBBULLETVIEW_H_
#include"cocostudio/CocoStudio.h"
#include"cocostudio/CocoLoader.h"
#include"cocos2d.h"
#include"DataOfGame.h"
#include"ui/UIButton.h"
#include"ui/UITextAtlas.h"
#include"BulletView.h"
#include"bulletlayer/bullet/FireBomb.h"
#include"panellayer/PanelLayer.h"

using namespace cocos2d;
//class PanelLayer;
class SpaceBombView//∫ÀµØµ¿æﬂ¿‡
{
public:
	static SpaceBombView* createSpaceBombView();
	void selectCallback(Ref*sender,ui::Widget::TouchEventType type);
	void setBulletNum(int num);
	Node* BulletViewNode;
	void setIsRotate(bool isRotate);
private:
	Sprite* sprite_SpaceBombView;
	ui::Button* button_bombBullet;
	ui::TextAtlas* ta_bulletNum;
};
#endif