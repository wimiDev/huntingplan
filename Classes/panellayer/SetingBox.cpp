#include "SetingBox.h"

bool SetingBox::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * e)
{
	return true;
}

void SetingBox::ButtonExitCallback(Ref * sender, ui::Widget::TouchEventType type)
{
	ui::Button* _button = static_cast<ui::Button*>(sender);
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		Audio::getInstance()->playeffectbykey("click");
		_button->setScale(0.8f);
	}
	else if (type == ui::Widget::TouchEventType::ENDED)
	{
		Director::getInstance()->resume();

		_button->setScale(1.0f);
		Sprite* bg = static_cast<Sprite*>(exitButton->getParent());
		SetingBox* _setingboxlayer = static_cast<SetingBox*>(bg->getParent()->getParent()->getParent());
		CCCallFuncN* _callback = CCCallFuncN::create([=](Ref*sender) {
			bg->removeFromParent();
			_setingboxlayer->removeFromParent();
		});
		bg->runAction(UiAction::getInstance()->pushout(0.3f, *_callback));

	}
	else if (type == ui::Widget::TouchEventType::CANCELED)
	{
		_button->setScale(1.0f);
	}
}


void SetingBox::ButtonMusicCallback(Ref*sender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		auto button = static_cast<ui::Button*>(sender);
		if (Audio::getInstance()->isPlayBgMusic)
		{
			Audio::getInstance()->isPlayBgMusic = false;
			Audio::getInstance()->setIsPlayBgMusic(Audio::getInstance()->isPlayBgMusic);
			button_Music->setBrightStyle(ui::Widget::BrightStyle::HIGHLIGHT);
		}
		else
		{
			Audio::getInstance()->isPlayBgMusic = true;
			Audio::getInstance()->setIsPlayBgMusic(Audio::getInstance()->isPlayBgMusic);
			PlayScene* playScene = static_cast<PlayScene*>(button->getParent()->getParent()->getParent());//????
			if (playScene->_gameModule == 3)
			{
				Audio::getInstance()->playbmgbykey("gamemodule3bgm");
			}
			else if (playScene->_gameModule == 2)
			{
				Audio::getInstance()->playbmgbykey("gamemodule2bgm");
			}
			button_Music->setBrightStyle(ui::Widget::BrightStyle::NORMAL);
		}
		 DataOfGame::getInstance()->setMusicState(Audio::getInstance()->isPlayBgMusic);
	}
	else if (type == ui::Widget::TouchEventType::BEGAN)
	{
		Audio::getInstance()->playeffectbykey("click");
	}
}
void SetingBox::ButtonEffectCallback(Ref*sender, ui::Widget::TouchEventType type)
{

	if (type == ui::Widget::TouchEventType::ENDED)
	{
		auto button = static_cast<ui::Button*>(sender);
		if (Audio::getInstance()->isPlayEffect)
		{
			Audio::getInstance()->setIsPlayEffect(false);
			button_Effect->setBrightStyle(ui::Widget::BrightStyle::HIGHLIGHT);
		}
		else
		{
			Audio::getInstance()->setIsPlayEffect(true);
			button_Effect->setBrightStyle(ui::Widget::BrightStyle::NORMAL);
		}
	}
	else if (type == ui::Widget::TouchEventType::BEGAN)
	{
		Audio::getInstance()->playeffectbykey("click");
	}
	DataOfGame::getInstance()->setEffectState(Audio::getInstance()->isPlayEffect);
}
void SetingBox::ButtonReplayCallback(Ref * sender, ui::Widget::TouchEventType type)
{
	auto _button = static_cast<ui::Button*>(sender);
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		Audio::getInstance()->playeffectbykey("click");
		_button->setScale(0.8f);
	}
	else if (type == ui::Widget::TouchEventType::ENDED)
	{	
		_button->setScale(1.0f);
		auto bg = static_cast<Sprite*>(_button->getParent());
		
		bg->runAction(UiAction::getInstance()->pushout(0.3f,
			*CCCallFuncN::create([=](Ref*sender) {
		SetingBox* _setingbox = static_cast<SetingBox*>(bg->getParent()->getParent()->getParent());
		PlayScene* playScene = static_cast<PlayScene*>(_setingbox->getParent()->getParent());
		PanelLayer* panelLayer = static_cast<PanelLayer*>(playScene->getChildByName("panelLayer"));
		playScene->Replay();
	
		ui::Button* setingButton = static_cast<ui::Button*>(panelLayer->getChildByName("setingButton"));
		if (setingButton != nullptr)
			setingButton->setEnabled(true);
		_setingbox->removeFromParent();
		})));
	}
	else if (type == ui::Widget::TouchEventType::CANCELED)
	{
		_button->setScale(1.0f);
	}
	Director::getInstance()->resume();
}
void SetingBox::ButtonMenuCallback(Ref * sender, ui::Widget::TouchEventType type)
{
	auto _button = static_cast<ui::Button*>(sender);
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		Audio::getInstance()->playeffectbykey("click");
		_button->setScale(0.8f);
	}
	else if (type == ui::Widget::TouchEventType::ENDED)
	{
		_button->setScale(1.0f);
		Director::getInstance()->resume();
		auto scene = MainScene::createScene();
		if (scene != nullptr)
			Director::getInstance()->replaceScene(CCTransitionFade::create(1.0f, scene));
		Sprite* bg = static_cast<Sprite*>(_button->getParent()->getParent());
		ui::Button* setingButton = static_cast<ui::Button*>(bg->getParent()->getChildByName("setingButton"));
		if (setingButton != nullptr)
			setingButton->setEnabled(true);
		_button->getParent()->removeFromParent();
	}
	else if (type == ui::Widget::TouchEventType::CANCELED)
	{
		_button->setScale(1.0f);
	}
}
void SetingBox::ButtonHelpCallback(Ref * sender, ui::Widget::TouchEventType type)
{
	auto _button = static_cast<ui::Button*>(sender);
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		Audio::getInstance()->playeffectbykey("click");
		_button->setScale(0.8f);
	}
	else if (type == ui::Widget::TouchEventType::ENDED)
	{
		_button->setScale(1.0f);
		//*新手教程
		auto bg = static_cast<Sprite*>(_button->getParent());
		SetingBox* _setingbox = static_cast<SetingBox*>(bg->getParent()->getParent()->getParent());
		PlayScene* playScene = static_cast<PlayScene*>(_setingbox->getParent()->getParent());
		PanelLayer* panelLayer = static_cast<PanelLayer*>(playScene->getChildByName("panelLayer"));
		panelLayer->showcourse(playScene->_gameModule);
		ui::Button* setingButton = static_cast<ui::Button*>(panelLayer->getChildByName("setingButton"));
		if (setingButton != nullptr)
			setingButton->setEnabled(true);
		_setingbox->removeFromParent();
	}
	else if (type == ui::Widget::TouchEventType::CANCELED)
	{
		_button->setScale(1.0f);
	}
}
SetingBox * SetingBox::create(bool _ishavebutton)
{
	SetingBox* _setingBox = new SetingBox();
	_setingBox->init();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->setEnabled(true);
	listener->onTouchBegan = CC_CALLBACK_2(SetingBox::onTouchBegan,_setingBox);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, _setingBox);
	Layer* _setinglayer = 
		static_cast<Layer*>(CSLoader::createNode("setinglayer/setinglayer.csb"));
	_setingBox->addChild(_setinglayer);
	_setingBox->_shade = 
		static_cast<Sprite*>(DataOfGame::getInstance()->seekNodebyName(_setinglayer,"sprite_shade"));
	//背景
	_setingBox->_bg = 
		static_cast<Sprite*>(DataOfGame::getInstance()->seekNodebyName(_setinglayer, "sprite_bg"));
	//帮助按钮
	_setingBox->_buttonhelp = 
		static_cast<ui::Button*>(DataOfGame::getInstance()->seekNodebyName(_setinglayer, "buttonhelp"));
	_setingBox->_buttonhelp->addTouchEventListener(CC_CALLBACK_2(SetingBox::ButtonHelpCallback,_setingBox));
	//退出按钮
	_setingBox->exitButton =
		static_cast<ui::Button*>(DataOfGame::getInstance()->seekNodebyName(_setinglayer, "button_exit"));
	_setingBox->exitButton->addTouchEventListener(CC_CALLBACK_2(SetingBox::ButtonExitCallback, _setingBox));
	_setingBox->label_Music = 
		static_cast<ui::Text*>(DataOfGame::getInstance()->seekNodebyName(_setinglayer, "text_music"));
	_setingBox->label_Effect = 
		static_cast<ui::Text*>(DataOfGame::getInstance()->seekNodebyName(_setinglayer, "text_effect"));
	_setingBox->button_RePlay = 
			static_cast<ui::Button*>(DataOfGame::getInstance()->seekNodebyName(_setinglayer, "button_replay"));
	_setingBox->button_RePlay->addTouchEventListener(CC_CALLBACK_2(SetingBox::ButtonReplayCallback, _setingBox));
	_setingBox->button_Menu = 
			static_cast<ui::Button*>(DataOfGame::getInstance()->seekNodebyName(_setinglayer, "button_menu"));
		_setingBox->button_Menu->addTouchEventListener(CC_CALLBACK_2(SetingBox::ButtonMenuCallback, _setingBox));
	if (!_ishavebutton)
	{
		_setingBox->button_Menu->setVisible(false);
		_setingBox->button_RePlay->setVisible(false);
		_setingBox->_buttonhelp->setVisible(false);
	}
	_setingBox->button_Music = 
		static_cast<ui::Button*>(DataOfGame::getInstance()->seekNodebyName(_setinglayer,"button_music")); 

	if (Audio::getInstance()->isPlayBgMusic)
	{
		_setingBox->button_Music->setBrightStyle(ui::Widget::BrightStyle::NORMAL);
	}
	else
	{
		_setingBox->button_Music->setBrightStyle(ui::Widget::BrightStyle::HIGHLIGHT);
	}
	_setingBox->button_Music->addTouchEventListener(CC_CALLBACK_2(SetingBox::ButtonMusicCallback, _setingBox));

	_setingBox->button_Effect = static_cast<ui::Button*>(DataOfGame::getInstance()->seekNodebyName(_setinglayer, "button_effect"));
	if (Audio::getInstance()->isPlayEffect)
	{
		_setingBox->button_Effect->setBrightStyle(ui::Widget::BrightStyle::NORMAL);
	}
	else
	{
		_setingBox->button_Effect->setBrightStyle(ui::Widget::BrightStyle::HIGHLIGHT);
	}
	_setingBox->button_Effect->addTouchEventListener(CC_CALLBACK_2(SetingBox::ButtonEffectCallback, _setingBox));
	return _setingBox;
}
void SetingBox::setMusic(bool _isPlayMusic)
{
	Audio::getInstance()->setIsPlayBgMusic(_isPlayMusic);
	if (Audio::getInstance()->isPlayBgMusic)//设置按钮状态
	{

	}
	else
	{

	}
}
void SetingBox::setEffect(bool _isPlayEffect)
{
	Audio::getInstance()->setIsPlayEffect(_isPlayEffect);
	if (Audio::getInstance()->isPlayEffect)//设置按钮状态
	{

	}
	else
	{

	}
}
void SetingBox::ShowSetingBox(Node*scene)
{
	float p_X = 0;
	float p_Y = 0;
	setPosition(p_X, p_Y);
	scene->addChild(this, 5);

}

bool SetingBox::init()
{
	if(!Layer::init())
	{
		return false;
	}
	return false;
}

