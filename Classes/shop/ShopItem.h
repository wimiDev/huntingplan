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
	//����
	Sprite* _bg;
	//��Ʒ��ͼƬ
	Sprite* _itemimg;
	//��Ʒ������
	ui::Text* _itemname;
	//��Ʒ������
	ui::Text* _textnum;
	//����ť
	ui::Button* _buy;
	//�۸��ǩ
	ui::Text* _textprice;
	//����
	std::string _strname;
	//����ť�ϵı�ǩ
	ui::Text* _textbuy;
	//����
	int _num;
	//�۸�
	int _price;
	//Ҫ���������
	int *_attribute;
	//����ص�
	std::function<void()> _buycallback;
	std::function<void()> _updateatt;
private:
	void buycallback(Ref*sender,ui::Widget::TouchEventType type);
};
#endif
