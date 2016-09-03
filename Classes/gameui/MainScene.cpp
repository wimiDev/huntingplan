#include "MainScene.h"

MainScene::MainScene()
{
}


MainScene::~MainScene()
{
}
Scene* MainScene::createScene()
{
	Scene* scene = Scene::create();
	Layer* layer = MainScene::create();
	scene->addChild(layer);
	return scene;
}
bool MainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->setName("mainscene");
	initUi();
	return true;
}

void MainScene::initUi()
{
	_flytime = 1.0f;
	Size winSize = Director::getInstance()->getWinSize();
	Vec2 _orgpoint = Director::getInstance()->getVisibleOrigin();
	Node* mainLayerNode = CSLoader::createNode("mainscenelayer/mainlayer.csb");
	this->addChild(mainLayerNode);
	std::string str_bgSprite = "sprite_bg";
	bg_sprite= static_cast<Sprite*>(DataOfGame::getInstance()->seekNodebyName(mainLayerNode, str_bgSprite));
	std::string _strshade = "sprite_shade";
	sprite_shade= static_cast<Sprite*>(DataOfGame::getInstance()->seekNodebyName(mainLayerNode,_strshade));
	std::string _strbuttonpanel = "sprite_buttonpanel";
	sprite_shade->removeFromParent();
	bg_sprite->addChild(sprite_shade,10);
	//sprite_buttonpanel= static_cast<Sprite*>(DataOfGame::getInstance()->seekNodebyName(mainLayerNode, _strbuttonpanel));
	//sprite_buttonpanel->setPosition(DataOfGame::getInstance()->getrealposition(sprite_buttonpanel->getPosition()));
	std::string str_playbutton = "button_play";
	playButton = static_cast<ui::Button*>(DataOfGame::getInstance()->seekNodebyName(mainLayerNode,str_playbutton));
	playButton->addTouchEventListener(CC_CALLBACK_2(MainScene::play_Callback,this));
	playButton->setPosition(DataOfGame::getInstance()->getrealposition(playButton->getPosition()));
	FadeIn* _pfadein = FadeIn::create(0.3f);
	FadeOut* _pfadeout = FadeOut::create(0.7f);
	playButton->runAction(RepeatForever::create(Sequence::create(_pfadein,_pfadeout,nullptr)));
	std::string str_aboutbutton = "button_about";
	_aboutButton= static_cast<ui::Button*>(DataOfGame::getInstance()->seekNodebyName(mainLayerNode, str_aboutbutton));
	_aboutButton->addTouchEventListener(CC_CALLBACK_2(MainScene::about_Callback,this));
	_aboutButton->setPosition(DataOfGame::getInstance()->getrealposition(_aboutButton->getPosition()));
	std::string str_setButton = "setingButton";
	setButton = static_cast<ui::Button*>(DataOfGame::getInstance()->seekNodebyName(mainLayerNode, str_setButton));
	setButton->addTouchEventListener(CC_CALLBACK_2(MainScene::set_Callback,this));
	setButton->setPosition(DataOfGame::getInstance()->getrealposition(setButton->getPosition()));
	DataOfGame::getInstance()->getGold();
	DataOfGame::getInstance()->_sqliteManager->createSqliteDatebase("DATABASE");
	DataOfGame::getInstance()->_sqliteManager->createTable("Module2");
	DataOfGame::getInstance()->_sqliteManager->createTable("Module3");
	DataOfGame::getInstance()->_sqliteManager->createTable("Module4");
	
	this->schedule(schedule_selector(MainScene::addenemycallback),_flytime, kRepeatForever, 0);
	_flytime = random(0.5f, 3.0f);
	bool _isplaymusic = DataOfGame::getInstance()->getMusicState();
	if (_isplaymusic != false)
	{
		_isplaymusic = true;
		DataOfGame::getInstance()->setMusicState(_isplaymusic);
	}
	Audio::getInstance()->setIsPlayBgMusic(_isplaymusic);
	bool _isplayeffect = DataOfGame::getInstance()->getEffectState();
	if (_isplayeffect != false)
	{
		_isplayeffect = true;
		DataOfGame::getInstance()->setEffectState(_isplayeffect);
	}
	Audio::getInstance()->setIsPlayEffect(_isplayeffect);
	Audio::getInstance()->playbmgbykey("mainscenebgm");
	//新玩家赠送金币1000
	if (DataOfGame::getInstance()->getm2new() &&
		DataOfGame::getInstance()->getm3new() &&
		DataOfGame::getInstance()->getm4new() 
		)
	{
		DataOfGame::getInstance()->setGold(1000);
	}
	//*加载敌人纹理
	TargetMaker::getinstance()->loadenemytexture();
}
void MainScene::exit_Callback(Ref * sender)
{

}
void MainScene::play_Callback(Ref*sender, ui::Widget::TouchEventType type)
{
	ui::Button* _button = static_cast<ui::Button*>(sender);
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		std::string _path = Audio::getInstance()->geteffectbykey("click");
		Audio::getInstance()->PlayEffect(_path);
		_button->setScale(0.8f);
	}
	else if (type == ui::Widget::TouchEventType::ENDED)
	{
		playButton->setEnabled(false);
		//SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();	//清理缓存
		Scene* scene = ModuleSelectScene::createScene();
		Director::getInstance()->replaceScene(CCTransitionFade::create(1.0f,scene));
		_button->setScale(1.0f);

	}
	else if (type == ui::Widget::TouchEventType::CANCELED)
	{
		_button->setScale(1.0f);
	}
}
void MainScene::about_Callback(Ref*sender, ui::Widget::TouchEventType type)
{
	ui::Button* _button = static_cast<ui::Button*>(sender);
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		Audio::getInstance()->PlayEffect(Audio::getInstance()->geteffectbykey("click"));
		_button->setScale(0.8f);
	}
	else if (type == ui::Widget::TouchEventType::ENDED)
	{
		_aboutlayer=static_cast<Layer*>(CSLoader::createNode("aboutlayer/aboutlayer.csb"));
		bg_sprite->addChild(_aboutlayer,10);
		ui::Button* _button_aboutexit = 
			static_cast<ui::Button*>(DataOfGame::getInstance()->seekNodebyName(_aboutlayer,"button_exit"));
		Sprite* _aboutlayerbg = static_cast<Sprite*>
			(DataOfGame::getInstance()->seekNodebyName(_aboutlayer, "sprite_panel"));
		_aboutlayerbg->runAction(UiAction::getInstance()->pushin(0.3f, *CCCallFuncN::create(nullptr)));
		_aboutlayerbg->setScale(0);
		_button_aboutexit->addTouchEventListener([=](Ref*sender, ui::Widget::TouchEventType type) 
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
				CCCallFuncN* _callback = CCCallFuncN::create([=](Ref*sender) {
					_aboutlayer->removeFromParent();
				});
				_aboutlayerbg->runAction(UiAction::getInstance()->pushout(0.3f,*_callback));
			}
			else if (type == ui::Widget::TouchEventType::CANCELED)
			{
				_button->setScale(1.0f);
			}
		});
		_button->setScale(1.0f);
	}
	else if (type == ui::Widget::TouchEventType::CANCELED)
	{
		_button->setScale(1.0f);
	}
}

void MainScene::set_Callback(Ref * sender, ui::Widget::TouchEventType type)
{
	ui::Button* _button = static_cast<ui::Button*>(sender);
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		Audio::getInstance()->PlayEffect(Audio::getInstance()->geteffectbykey("click"));
		_button->setScale(0.8f);
	}
	else if (type == ui::Widget::TouchEventType::ENDED)
	{
		_button->setScale(1.0f);
		SetingBox* setbox = SetingBox::create(false);
		setbox->setAnchorPoint(Vec2(0.5f, 0.5f));
		bg_sprite->addChild(setbox, 10);
		setbox->_bg->setScale(0);
		setbox->_bg->runAction(UiAction::getInstance()->pushin(0.2, *CCCallFuncN::create(nullptr)));
		//AdViewToolX_1::loadAdInstl();
	}
	else if (type == ui::Widget::TouchEventType::CANCELED)
	{
		_button->setScale(1.0f);
	}
}


void MainScene::addenemycallback(float dt)
{
	Size winSize = Director::getInstance()->getWinSize();
	float _sX = 0.0f;
	float _sY = 0.0f;
	int _kind = 0;
	_kind = random(1,8);
	Sprite* _enemy1 = TargetMaker::getinstance()->loadenemyformainscene(_kind);
	//_enemy1->setPhysicsBody(nullptr);
	_sX = -_enemy1->getContentSize().width;
	_sY = random(200.0f,450.0f);
	_enemy1->setPosition(DataOfGame::getInstance()->getrealposition(Vec2(_sX, _sY)));
	float _eX = 0.0f;
	float _eY = 0.0f;
	_eX = winSize.width + _enemy1->getContentSize().width;
	_eY = random(200.0f, 450.0f);
	float _rX = std::abs(_eX - _sX);
	float _rY = std::abs(_eY - _sY);
	float _rotate1 = CC_RADIANS_TO_DEGREES(std::atan2(_rX,_rY));
	float _rotate2 = -90.0f;
	if (_sY > _eY)
	{
		_rotate2 = 90 - _rotate1;
	}
	else
	{
		_rotate2 = -90 + _rotate1;
	}
	MoveTo* _moveto = MoveTo::create(5.0f, Vec2(_eX,_eY));
	RotateTo* _rotateto = RotateTo::create(3.0f,_rotate2);
	CCCallFuncN* _movedone = CCCallFuncN::create([=](Ref*sender) {
		_enemy1->removeFromParent();
	});
	_enemy1->runAction(Sequence::create(Spawn::create(_moveto, _rotateto,nullptr),_movedone, nullptr));
	bg_sprite->addChild(_enemy1,0);
}
