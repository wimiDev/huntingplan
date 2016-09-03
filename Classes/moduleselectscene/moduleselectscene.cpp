#include "moduleselectscene.h"

cocos2d::Scene * ModuleSelectScene::createScene()
{
	Scene* scene = Scene::create();
	Layer* layer = ModuleSelectScene::create();
	scene->addChild(layer);
	return scene;
}

bool ModuleSelectScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	initUi();
	//TargetMaker::getinstance()->unloadenemytexture();
	return true;
}

void ModuleSelectScene::initUi()
{
	Size winSize = Director::getInstance()->getWinSize();
	this->addChild(static_cast<Layer*>(CSLoader::createNode("modulescelectlayer/moduleselectlayer.csb")));
	_bgsprite =static_cast<Sprite*>(DataOfGame::getInstance()->seekNodebyName(this,"sprite_bg"));
	_module1button = static_cast<ui::Button*>(DataOfGame::getInstance()->seekNodebyName(this, "button_module1"));
	_module1button->addTouchEventListener(CC_CALLBACK_2(ModuleSelectScene::pbModule1_Callback,this));
	_module2button = static_cast<ui::Button*>(DataOfGame::getInstance()->seekNodebyName(this, "button_module2"));
	_module2button->addTouchEventListener(CC_CALLBACK_2(ModuleSelectScene::pbModule2_Callback,this));
	_module3button = static_cast<ui::Button*>(DataOfGame::getInstance()->seekNodebyName(this, "button_module3"));
	_module3button->addTouchEventListener(CC_CALLBACK_2(ModuleSelectScene::pbModule3_Callback,this));
	_buttonback = static_cast<ui::Button*>(DataOfGame::getInstance()->seekNodebyName(this, "button_back"));
	_buttonback->addTouchEventListener(CC_CALLBACK_2(ModuleSelectScene::back_Callback, this));
	_textround = static_cast<ui::Text*>(DataOfGame::getInstance()->seekNodebyName(this, "text_round"));
	char _strround[10];
	sprintf(_strround,"%d--%d",DataOfGame::getInstance()->getround(),_MAXROUND);
	_textround->setString(_strround);
	_gamemodle = 0;
	Audio::getInstance()->loadBgMusic();
	Audio::getInstance()->loadEffect();
	Audio::getInstance()->playbmgbykey("mainscenebgm");
}

void ModuleSelectScene::pbModule1_Callback(Ref * sender, ui::Widget::TouchEventType type)
{
	ui::Button* _button = static_cast<ui::Button*>(sender);
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		Audio::getInstance()->playeffectbykey("click");
		_button->setScale(0.8f);
	}
	else if (type == ui::Widget::TouchEventType::ENDED)
	{
		//DataOfGame::getInstance()->gameModule = 3;
		_gamemodle = 3;
		auto scene = PlayScene::createScene(3);
		_button->setScale(1.0f);
		Director::getInstance()->replaceScene(CCTransitionFade::create(1.0f, scene));
	}
	else if (type == ui::Widget::TouchEventType::CANCELED)
	{
		_button->setScale(1.0f);
	}
}

void ModuleSelectScene::pbModule2_Callback(Ref * sender, ui::Widget::TouchEventType type)
{
	ui::Button* _button = static_cast<ui::Button*>(sender);
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		Audio::getInstance()->playeffectbykey("click");
		_button->setScale(0.8f);
	}
	else if (type == ui::Widget::TouchEventType::ENDED)
	{
		//DataOfGame::getInstance()->gameModule = 2;
		_button->setScale(1.0f);
		_gamemodle = 2;
		DataOfGame::getInstance()->_bulletTotle = 35;//设定初始的炮弹的量
		GameShop* _gameshop = GameShop::create();
		_gameshop->setattribute(&DataOfGame::getInstance()->_bulletTotle);
		_gameshop->_buycallback = std::bind(&ModuleSelectScene::buycallback, this);
		_gameshop->_exitcallback = _gameshop->_buycallback;
		_gameshop->bulletshop(_gamemodle);
		this->addChild(_gameshop);
	}
	else if (type == ui::Widget::TouchEventType::CANCELED)
	{
		_button->setScale(1.0f);
	}
}

void ModuleSelectScene::pbModule3_Callback(Ref * sender, ui::Widget::TouchEventType type)
{
	ui::Button* _button = static_cast<ui::Button*>(sender);
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		Audio::getInstance()->playeffectbykey("click");
		_button->setScale(0.8f);
	}
	else if (type == ui::Widget::TouchEventType::ENDED)
	{
		//DataOfGame::getInstance()->gameModule = 4;
		_gamemodle = 4;
		_button->setScale(1.0f);
		DataOfGame::getInstance()->_missnum = 2;
		GameShop* _gameshop = GameShop::create();
		_gameshop->setattributeicon("shoplayer/missicon.png");
		_gameshop->setattribute(&DataOfGame::getInstance()->_missnum);
		_gameshop->setattributename(GameStringValue::getStringByKey("shiwugeshu")->c_str());
		_gameshop->_buycallback = std::bind(&ModuleSelectScene::buycallback, this);
		_gameshop->_exitcallback = _gameshop->_buycallback;
		_gameshop->bulletshop(_gamemodle);
		this->addChild(_gameshop);
	}
	else if (type == ui::Widget::TouchEventType::CANCELED)
	{
		_button->setScale(1.0f);
	}
}

void ModuleSelectScene::back_Callback(Ref * sender, ui::Widget::TouchEventType type)
{
	ui::Button* _button = static_cast<ui::Button*>(sender);
		
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		Audio::getInstance()->playeffectbykey("click");
		_button->setScale(0.8f);
	}
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		//DataOfGame::getInstance()->gameModule = 4;
		_button->setScale(1.0f);
		auto scene = MainScene::createScene();
		Director::getInstance()->replaceScene(CCTransitionFade::create(1.0f, scene));
	}
	else if (type == ui::Widget::TouchEventType::CANCELED)
	{
		_button->setScale(1.0f);
	}
}

void ModuleSelectScene::buycallback()
{
	auto scene = PlayScene::createScene(_gamemodle);
	Director::getInstance()->replaceScene(CCTransitionFade::create(1.0f, scene));

}
