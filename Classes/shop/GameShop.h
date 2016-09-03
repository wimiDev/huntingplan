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
	//����
	Sprite*_shade;
	//����
	Sprite*_bg;
	//��Ʒ����
	ui::ScrollView* _scrollview_panel;
	//�̵����
	ui::Text* _textshop;
	//��ʾ
	ui::Text* _ps;
	//�˳���ť
	ui::Button* _exit;
	//��ұ���
	ui::Text* _goldtitle;
	//�ҵĽ��
	ui::Text* _textgold;
	//��������
	ui::Text* _attributename;
	//����ֵ
	int* _attribute;
	//����ͼ��
	Sprite* _attributeicon;
	//����ֵ
	ui::Text* _textattribute;
	//�˳��ص�
	std::function<void()> _exitcallback;
	//����ص�
	std::function< void()> _buycallback;
private:
	Vector<ShopItem*> itemlist;
	void exitcallback(Ref * sender, ui::Widget::TouchEventType type);
	void updateatt();
};

#endif