#ifndef __SHOP_SHOPITEM_H_
#define __SHOP_SHOPITEM_H_
#include"cocos2d.h"
#include"ui/UIText.h"
#include"ui/UIButton.h"
#include"GameResource.h"
#include"cocostudio/CocoLoader.h"
#include"cocostudio/CocoStudio.h"

#include"DataOfGame.h"
using namespace cocos2d;

class ShopItem
	:public Node
{
public:
	ShopItem();
	~ShopItem();
	static ShopItem* create();
	bool init();
	void fullitem(const char* _bgpath,const char* _name,int _num,int _price);
public:
	//背景
	Sprite* _bg;
	//商品的图片
	Sprite* _itemimg;
	//商品的名字
	ui::Text* _itemname;
	//商品的数量
	ui::Text* _textnum;
	//购买按钮
	ui::Button* _buy;
	//价格标签
	ui::Text* _textprice;
	//属性
	std::string _strname;
	//购买按钮上的标签
	ui::Text* _textbuy;
	//数量
	int _num;
	//价格
	int _price;
	//要购买的属性
	int *_attribute;
	//购买回调
	std::function<void()> _buycallback;
	std::function<void()> _updateatt;
private:
	void buycallback(Ref*sender,ui::Widget::TouchEventType type);
};
#endif
