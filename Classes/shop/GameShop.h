#ifndef __SHOP_GAMESHOP_H_
#define __SHOP_GAMESHOP_H_
#include"cocos2d.h"
#include"cocostudio/CocoStudio.h"
#include"cocostudio/CocoLoader.h"
#include"ui/UIScrollView.h"
#include"ui/UIText.h"
#include"shop/ShopItem.h"
#include"DataOfGame.h"
#include"gameui/GameUi.h"
using namespace cocos2d;

class GameShop
	:public Layer
{
public:
	static GameShop* create();
	bool init();
	void bulletshop(int _module=2);
	void addshopitem(ShopItem* _item);
	void setattribute(int* _num);
	void setattributeicon(const char*);
	void setattributename(const char*);
	void setpsstring(const char*_strps);
	void settextgold(int _gold);
public:
	//遮罩
	Sprite*_shade;
	//背景
	Sprite*_bg;
	//商品容器
	ui::ScrollView* _scrollview_panel;
	//商店标题
	ui::Text* _textshop;
	//提示
	ui::Text* _ps;
	//退出按钮
	ui::Button* _exit;
	//金币标题
	ui::Text* _goldtitle;
	//我的金币
	ui::Text* _textgold;
	//属性名字
	ui::Text* _attributename;
	//属性值
	int* _attribute;
	//属性图标
	Sprite* _attributeicon;
	//属性值
	ui::Text* _textattribute;
	//退出回调
	std::function<void()> _exitcallback;
	//购买回调
	std::function< void()> _buycallback;
private:
	Vector<ShopItem*> itemlist;
	void exitcallback(Ref * sender, ui::Widget::TouchEventType type);
	void updateatt();
};

#endif