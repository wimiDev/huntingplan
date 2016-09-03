#include "wellcomelayer.h"

bool WellComeLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	_pageview = nullptr;
	_gamestate = nullptr;
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [=](cocos2d::Touch * touch, cocos2d::Event * e)->bool { return true; };
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->setSwallowsTouches(false);
	Layer* _wellcomelayer =static_cast<Layer*>(CSLoader::createNode("wellcomelayer/wellcomelayer.csb"));
	this->addChild(_wellcomelayer);
	_pageview = static_cast<ui::PageView*>(DataOfGame::getInstance()->seekNodebyName(_wellcomelayer,"PageView_1"));
	_shade = static_cast<Sprite*>(DataOfGame::getInstance()->seekNodebyName(_wellcomelayer, "sprite_shade"));
	_bg= static_cast<Sprite*>(DataOfGame::getInstance()->seekNodebyName(_wellcomelayer, "sprite_bg"));
	return true;
}

WellComeLayer * WellComeLayer::create(int _imodule)
{
	WellComeLayer* _wellcomelayer = new WellComeLayer();
	_wellcomelayer->_module = _imodule;
	_wellcomelayer->_page = 1;
	_wellcomelayer->init();
	if (_imodule == 4)
	{
		//模式4的时候清掉屏幕上所有敌人
		DataOfGame::getInstance()->clearvector(DataOfGame::getInstance()->targetsVector);
	}
	return _wellcomelayer;
}

std::string WellComeLayer::getatt(int _module, int _page, int _attribute)
{
	std::string _json = "";
	std::string _strattribute = "";
	_json = DataOfGame::getInstance()->getJsonString("wellcomelayer/coursedata.json");
	char _strmodule[10];
	sprintf(_strmodule,"module%d",_module);
	char _strpage[10];
	sprintf(_strpage,"page%d",_page);

	rapidjson::Document d;
	d.Parse<0>(_json.c_str());
	if (d.HasParseError())
	{
		log("jsonData Error");
		return _strattribute;
	}
	if (!d.HasMember(_strmodule))
	{
		CCLOG("not %s!",_strmodule);
		return _strattribute;
	}
	rapidjson::Value& _jmodule = d[_strmodule];
	if (!_jmodule.HasMember(_strpage))
	{
		CCLOG("not %s!",_strpage);
		return _strattribute;
	}
	rapidjson::Value& _jpage = _jmodule[_strpage];
	switch (_attribute)
	{
		case 1:
		{
			if (!_jpage.HasMember("img"))
				{
					CCLOG("not img!");
					return _strattribute;
				}
				_strattribute = _jpage["img"].GetString();
		}break;
		case 2:
		{
			if (!_jpage.HasMember("text"))
			{
				CCLOG("not text!");
				return _strattribute;
			}
			_strattribute = _jpage["text"].GetString();
		}break;
		case 3:
		{
			if (!_jpage.HasMember("end"))
			{
				CCLOG("not end!");
				return _strattribute;
			}
			_strattribute = _jpage["end"].GetString();
		}break;
		default:
			break;
	}
	
	return _strattribute;
}

std::string WellComeLayer::getcoursetext(int _module, int _page)
{
	return std::string();
}

void WellComeLayer::loadpagedata()
{
	if (_pageview == nullptr)
	{
		return;
	}
	PanelLayer* _panellayer = static_cast<PanelLayer*>(this->getParent());
	PlayScene* _playscene = static_cast<PlayScene*>(_panellayer->getParent());
	Director::getInstance()->resume();
	_playscene->isGameover = 2;//游戏未就绪
	_pageview->removeAllPages();
	while (_page<100)
	{
		//开始装载数据
		ui::Layout* _panel = ui::Layout::create();
		_panel->setContentSize(_pageview->getContentSize());
		ui::Text* _newcourse = ui::Text::create(GameStringValue::getStringByKey("xsjc")->c_str(),
			"font/fangzhengzongyijianti.ttf",56);
		_newcourse->setPosition(Vec2(247,417));
		_newcourse->enableOutline(Color4B::BLACK,3);
		_newcourse->setTextColor(Color4B::YELLOW);
		_newcourse->setSkewX(10);
		_panel->addChild(_newcourse);

		std::string _strimg = getatt(_module, _page, 1);
		Sprite* _courseimg = Sprite::create(_strimg);
		_courseimg->setPosition(Vec2(226,289));
		_courseimg->setAnchorPoint(Vec2(0.0f,0.5f));
		_panel->addChild(_courseimg);

		std::string _strinfo = getatt(_module,_page,2);
		ui::Text* _textinfo = ui::Text::create(_strinfo, "font/fangzhengzongyijianti.ttf", 28);
		_textinfo->setAnchorPoint(Vec2(0.0f,1.0f));
		_textinfo->setPosition(Vec2(162,212));
		_textinfo->ignoreContentAdaptWithSize(false);
		_textinfo->setSize(Size(507,102));
		_textinfo->enableOutline(Color4B::BLACK);
		_textinfo->setTextColor(Color4B::YELLOW);
		_panel->addChild(_textinfo);

		std::string _strend = getatt(_module,_page,3);
		if (_strend == "Y")
		{
			ui::Button* _nextbutton = ui::Button::create("texture_img/texture_button/next_round_2.png",
														"texture_img/texture_button/next_round_2.png",
														"texture_img/texture_button/next_round_2.png",
														ui::Widget::TextureResType::PLIST);
			_nextbutton->setPosition(Vec2(565,41));
			_nextbutton->addTouchEventListener(CC_CALLBACK_2(WellComeLayer::buttonskipcallback,this));
			_panel->addChild(_nextbutton);
			_pageview->addPage(_panel);
			break;
		}
		_pageview->addPage(_panel);
		_page++;
	}
}

void WellComeLayer::buttonskipcallback(Ref * sender, ui::Widget::TouchEventType type)
{
	ui::Button* _button = static_cast<ui::Button*>(sender);
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		Audio::getInstance()->playeffectbykey("click");
		_button->setScale(0.8f);
	}
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		_button->setScale(1.0f);
		if (_gamestate != nullptr)
		{
			*_gamestate = 0;
		}	
		//Director::getInstance()->resume();
		PanelLayer* _panellayer = static_cast<PanelLayer*>(this->getParent());
		PlayScene* _playscene = static_cast<PlayScene*>(_panellayer->getParent());
		Director::getInstance()->resume();
		_playscene->isGameover = 0;//游戏就绪
		_bg->runAction(UiAction::getInstance()->pushout(0.3f, 
			*CCCallFuncN::create([=](Ref*sender) {
		this->removeFromParentAndCleanup(true);
		})));

	}
	else if (type == ui::Widget::TouchEventType::CANCELED)
	{
		_button->setScale(1.0f);
	}
}
