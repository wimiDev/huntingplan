#include "GameShop.h"

GameShop * GameShop::create()
{
	GameShop* _gameshop = new GameShop();
	_gameshop->init();
	return _gameshop;
}

bool GameShop::init()
{
	if(!Layer::init())
	{ 
		return false;
	}
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->setEnabled(true);
	listener->onTouchBegan =[=](cocos2d::Touch* touch, cocos2d::Event*e) {return true; };
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	itemlist = Vector<ShopItem*>();
	_exitcallback = nullptr;
	_buycallback = nullptr;
	Layer* _shoplayer =static_cast<Layer*> (CSLoader::createNode("shoplayer/shoplayer.csb"));
	this->addChild(_shoplayer);
	_shade = static_cast<Sprite*>(DataOfGame::getInstance()->seekNodebyName(_shoplayer,"sprite_shade"));
	_bg = static_cast<Sprite*>(DataOfGame::getInstance()->seekNodebyName(_shoplayer, "sprite_bg"));
	_scrollview_panel = static_cast<ui::ScrollView*>
		(DataOfGame::getInstance()->seekNodebyName(_shoplayer, "scrollview_panel"));
	_exit = static_cast<ui::Button*>(DataOfGame::getInstance()->seekNodebyName(_shoplayer,"button_exit"));
	_exit->addTouchEventListener(CC_CALLBACK_2(GameShop::exitcallback,this));
	_textshop= static_cast<ui::Text*>(DataOfGame::getInstance()->seekNodebyName(_shoplayer,"text_shop"));
	_textshop->setSkewX(10);
	_ps = static_cast<ui::Text*>(DataOfGame::getInstance()->seekNodebyName(_shoplayer,"text_ps"));
	_ps->setSkewX(10);
	_goldtitle= static_cast<ui::Text*>(DataOfGame::getInstance()->seekNodebyName(_shoplayer, "text_mygold"));
	_goldtitle->setSkewX(10);
	_textgold = static_cast<ui::Text*>(DataOfGame::getInstance()->seekNodebyName(_shoplayer, "text_gold"));
	_textgold->setSkewX(10);
	char _strgold[20];
	sprintf(_strgold,"%d",DataOfGame::getInstance()->gold);
	_textgold->setString(_strgold);
	_attributename = static_cast<ui::Text*>(DataOfGame::getInstance()->seekNodebyName(_shoplayer,"text_mybullet"));
	_attributename->setSkewX(10);
	_textattribute = static_cast<ui::Text*>(DataOfGame::getInstance()->seekNodebyName(_shoplayer,"text_bulletnum"));
	_attributeicon = static_cast<Sprite*>(DataOfGame::getInstance()->seekNodebyName(_shoplayer,"sprite_bullet"));
	Audio::getInstance()->playeffectbykey("messagepush");
	_bg->setScale(0);
	_bg->runAction(UiAction::getInstance()->pushin(0.2f,*CCCallFuncN::create(nullptr)));
	return true;
}

void GameShop::bulletshop(int _module)
{
	ShopItem* _item = ShopItem::create();
	addshopitem(_item);
	_scrollview_panel->addChild(_item);
	if (_module == 2||_module==3)
	{
		_item->fullitem("shoplayer/bulletitem.png", 
		GameStringValue::getStringByKey("youzhipaodan")->c_str(), 2, 250);
		_item->_attribute = &DataOfGame::getInstance()->_bulletTotle;
	}
	else if(_module==4)
	{
		_item->fullitem("shoplayer/missitem.png",
		GameStringValue::getStringByKey("shiwugeshu")->c_str(),1, 250);
		_item->_attribute = &DataOfGame::getInstance()->_missnum;
		
	}
	_item->_buycallback = this->_buycallback;
	_item->_updateatt = std::bind(&GameShop::updateatt, this);

	ShopItem* _item1 = ShopItem::create();
	addshopitem(_item1);
	_scrollview_panel->addChild(_item1);
	if (_module == 2 || _module == 3)
	{ 
	_item1->fullitem("shoplayer/bulletitem.png",
		GameStringValue::getStringByKey("youzhipaodan")->c_str(),5,500);	
	_item1->_attribute = &DataOfGame::getInstance()->_bulletTotle;
	}
	else if (_module==4)
	{
		_item1->fullitem("shoplayer/missitem.png",
		GameStringValue::getStringByKey("shiwugeshu")->c_str(), 2, 500);
		_item1->_attribute = &DataOfGame::getInstance()->_missnum;
	}
	_item1->_buycallback = this->_buycallback;
	_item1->_updateatt = std::bind(&GameShop::updateatt, this);

	ShopItem* _item2 = ShopItem::create();
	addshopitem(_item2);
	_scrollview_panel->addChild(_item2);
	if (_module == 2 || _module == 3)
	{
		_item2->fullitem("shoplayer/bulletitem.png",
			GameStringValue::getStringByKey("youzhipaodan")->c_str(), 10,998);
		_item2->_attribute = &DataOfGame::getInstance()->_bulletTotle;
	}
	else if (_module==4)
	{
		_item2->fullitem("shoplayer/missitem.png",
			GameStringValue::getStringByKey("shiwugeshu")->c_str(),3,750);
		_item2->_attribute = &DataOfGame::getInstance()->_missnum;
	}
	_item2->_buycallback = this->_buycallback;
	_item2->_updateatt = std::bind(&GameShop::updateatt, this);
}

void GameShop::addshopitem(ShopItem * _item)
{
	float _py = 188.0f;
	if (itemlist.size() <= 0)
	{
		_item->setPosition(_item->_bg->getContentSize().width/2,_py);
		itemlist.pushBack(_item);
		return;
	}
	_item->setPosition((itemlist.at(itemlist.size()-1)->getPosition().x+_item->_bg->getContentSize().width)+20, _py);
	itemlist.pushBack(_item);
}

void GameShop::setattribute(int*_num)
{
	if (_textattribute == nullptr)
	return;
	_attribute = _num;
	char _strbulletnum[10];
	sprintf(_strbulletnum, "%d", *_num);
	_textattribute->setString(_strbulletnum);
}

void GameShop::setattributeicon(const char * _iconpath)
{
	if (_attributeicon == nullptr)
		return;
	_attributeicon->setTexture(_iconpath);
}

void GameShop::setattributename(const char *_name)
{
	if (_attributename)
	{
		_attributename->setString(_name+std::string(":"));
	}
}

void GameShop::setpsstring(const char *_psstring)
{
	if (_ps)
	{
		_ps->setString(_psstring);
	}
}

void GameShop::settextgold(int _gold)
{
	char _strgold[10];
	sprintf(_strgold, "%d", _gold);
	_textgold->setString(_strgold);
}


void GameShop::exitcallback(Ref * sender, ui::Widget::TouchEventType type)
{
	ui::Button* _button = static_cast<ui::Button*>(sender);
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		Audio::getInstance()->playeffectbykey("click");
		_button->setScale(0.8f);
	}
	else if (type == ui::Widget::TouchEventType::ENDED)
	{
		_button->setScale(1.0f);
		CCCallFuncN* _callback = CCCallFuncN::create([=](Ref*sender) {this->removeFromParent();});
		if(!_exitcallback)
		{ 
			this->runAction(_callback);
		}
		else
		{
			_exitcallback();
			this->runAction(Sequence::create(_callback, nullptr));
		}
	}
	else if (type == ui::Widget::TouchEventType::CANCELED)
	{
		_button->setScale(1.0f);
	}
}

void GameShop::updateatt()
{
	setattribute(_attribute);
	settextgold(DataOfGame::getInstance()->gold);
}
