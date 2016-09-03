#include "ShopItem.h"



ShopItem::ShopItem()
{

}


ShopItem::~ShopItem()
{
}
ShopItem * ShopItem::create()
{
	ShopItem* _shopitem = new ShopItem();
	_shopitem->init();
	return _shopitem;
}

bool ShopItem::init()
{
	if (!Node::init())
	{
		return false;
	}
	_buycallback = nullptr;
	_attribute = nullptr;
	_updateatt = nullptr;
	Node* _shopitem = CSLoader::createNode("shoplayer/node_shopitem.csb");
	this->addChild(_shopitem);
	_bg = static_cast<Sprite*>(DataOfGame::getInstance()->seekNodebyName(_shopitem,"sprite_bg"));
	_itemimg = static_cast<Sprite*>(DataOfGame::getInstance()->seekNodebyName(_shopitem,"sprite_shopitem"));
	_itemname = static_cast<ui::Text*>(DataOfGame::getInstance()->seekNodebyName(_shopitem,"text_shopname"));
	_itemname->setSkewX(10);
	_textnum = static_cast<ui::Text*>(DataOfGame::getInstance()->seekNodebyName(_shopitem,"text_num"));
	_textnum->setSkewX(10);
	_textprice = static_cast<ui::Text*>(DataOfGame::getInstance()->seekNodebyName(_shopitem,"text_price"));
	_buy = static_cast<ui::Button*>(DataOfGame::getInstance()->seekNodebyName(_shopitem,"button_buy"));
	_buy->addTouchEventListener(CC_CALLBACK_2(ShopItem::buycallback,this));
	_textbuy= static_cast<ui::Text*>(DataOfGame::getInstance()->seekNodebyName(_shopitem, "text_buy"));
	_textbuy->setSkewX(10);
	return true;
}

void ShopItem::fullitem(const char * _bgpath, const char * _name, int _num, int _price)
{
	if (_itemimg)
	{
		_itemimg->setTexture(_bgpath);
	}
	if (_itemname)
	{
		_itemname->setString(_name);
		_strname = _name;
	}
	if (_textnum)
	{
		char _strnum[5];
		sprintf(_strnum, "X %d", _num);
		_textnum->setString(_strnum);
		this->_num = _num;
	}
	if (_textprice)
	{
		char _strprice[10];
		sprintf(_strprice,"%d",_price);
		_textprice->setString(_strprice);
		this->_price = _price;
		if (_price > DataOfGame::getInstance()->gold)
		{
			_textbuy->setString(GameStringValue::getStringByKey("jinbibuzu")->c_str());
			_textbuy->setFontSize(30);
			_buy->setEnabled(false);
		}
		else
		{
			_textbuy->setString(GameStringValue::getStringByKey("goumai")->c_str());
			_textbuy->setFontSize(36);
			_buy->setEnabled(true);
		}
	}
}

void ShopItem::buycallback(Ref * sender, ui::Widget::TouchEventType type)
{
	ui::Button* _button = static_cast<ui::Button*>(sender);
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		Audio::getInstance()->playeffectbykey("click");
		_button->setScale(0.8f);
	}
	else if (type==ui::Widget::TouchEventType::ENDED)
	{
		_button->setScale(1.0f);
		if (DataOfGame::getInstance()->gold > _price)
		{
			DataOfGame::getInstance()->setGold(DataOfGame::getInstance()->gold - _price);
			if (_attribute)
			{
				*_attribute += _num;
			}
		}
		if(_buycallback)
		{
			_buycallback();
		}
		if(_updateatt)
		{
			_updateatt();
		}
		
	}
	else if (type == ui::Widget::TouchEventType::CANCELED)
	{
		_button->setScale(1.0f);
	}
}
