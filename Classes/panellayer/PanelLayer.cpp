#include"PanelLayer.h"

PanelLayer::PanelLayer()
{

}
PanelLayer::~PanelLayer()
{

}
Score* PanelLayer::score = new Score();
SpaceBombView* PanelLayer::spacebombView = new SpaceBombView();
std::vector<BulletView*> PanelLayer::bulletViewList = std::vector<BulletView*>();
//TaskCard* PanelLayer::taskCard = nullptr;
Gold* PanelLayer::gold = new Gold();
ui::Button* PanelLayer::setingButton = nullptr;

bool PanelLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto listener = EventListenerTouchOneByOne::create();
	//listener->setSwallowTouches(true);
	_touchenable = true;
	listener->setEnabled(true);
	listener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event*e)->bool
	{
		return _touchenable;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}
PanelLayer* PanelLayer::create()
{
	PanelLayer* panelLayer = new PanelLayer();
	panelLayer->init();
	return panelLayer;
}

bool PanelLayer::isDanger()
{
	bool isdanger = false;
	int bloodTotle = 0;
	for (int i = 0; i < DataOfGame::getInstance()->targetsVector.size(); ++i)
	{
		target* enemy = static_cast<target*>(DataOfGame::getInstance()->targetsVector.at(i));
		if (enemy->getKind() == 7)
			continue;
		bloodTotle += enemy->getBlood();
	}
	if (DataOfGame::getInstance()->_bulletTotle < bloodTotle)
	{
		isdanger = true;
		enemyNum->getSpriteProg()->setTexture("panellayer/sprite_process_r.png");
	}
		enemyNum->getSpriteProg()->setTexture("panellayer/sprite_process_g.png");
	return isdanger;
}

void PanelLayer::addAllToLayer()
{
	Node* _panelnode = CSLoader::createNode("panellayer/layer_panellayer.csb");
	_panelnode->setPosition(DataOfGame::getInstance()->LayerGetRealPosition(-540, -360));
	this->addChild(_panelnode);
	ariship = static_cast<Sprite*>(DataOfGame::getInstance()->seekNodebyName(_panelnode, "sprite_plan"));
	Size winsize = Director::getInstance()->getWinSize();
	Size visiablesize = Director::getInstance()->getVisibleSize();
	Vec2 _org = Director::getInstance()->getVisibleOrigin();
	////∑÷??
	score = Score::create();
	score->_nodescore->setAnchorPoint(Vec2(1.0f, 0.5f));
	this->addChild(score->_nodescore);
	score->_nodescore->setPosition(
		winsize.width / 2 - _org.x - score->_spritebg->getContentSize().width / 2,
		winsize.height / 2 - score->_spritebg->getContentSize().height / 2 - _org.y);
	////Ω?±“
	gold = Gold::create();
	gold->setAnchorPoint(Vec2(1.0f, 0.5f));
	gold->setPosition(
		winsize.width / 2 - gold->_sprite_bg->getContentSize().width / 2 - _org.x,
		winsize.height / 2 - gold->_sprite_bg->getContentSize().height * 2 - _org.y);
	this->addChild(gold);
	gold->showGold(DataOfGame::getInstance()->getGold());
	//≈??
	_connonPool = Sprite::create("panellayer/connon_2.png");
	_connonPool->setPosition(visiablesize.width / 2, _connonPool->getContentSize().height / 5 );
	//_connonPool->setVisible(false);
	_panelnode->addChild(_connonPool);
	//≈????????‘????
	_bulletview = BulletView::create(_panelnode);
	_bulletview->setlock(false);
	////*∞?÷˙∞?≈?
	//_buttonhelp = static_cast<ui::Button*>
	//	(DataOfGame::getInstance()->seekNodebyName(_panelnode, "button_help"));
	//_buttonhelp->addTouchEventListener(CC_CALLBACK_2(PanelLayer::buttonhelpCallback, this));
	//float _phx = visiablesize.width - 3 * _buttonhelp->getContentSize().width;
	//float _phy = visiablesize.height - (_buttonhelp->getContentSize().height / 2);
	//_buttonhelp->setPosition(DataOfGame::getInstance()->getrealposition(Vec2(_phx, _phy)));
	//FadeIn* _hfadein = FadeIn::create(0.5f);
	//FadeOut* _hfadeout = FadeOut::create(0.5f);
	//_buttonhelp->runAction(RepeatForever::create(Sequence::create(_hfadein, _hfadeout, nullptr)));
	////…?÷√∞?≈?
	setingButton = static_cast<ui::Button*>
		(DataOfGame::getInstance()->seekNodebyName(_panelnode, "setingButton"));
	setingButton->addTouchEventListener(CC_CALLBACK_2(PanelLayer::setingboxcallback, this));
	PlayScene*playScene = static_cast<PlayScene*>(this->getParent());
	_enemyprocess = EnemyProcess::create();
	_enemyprocess->_nodeenemyprocess->setAnchorPoint(Vec2(0.0f, 0.0f));
		_enemyprocess->_nodeenemyprocess->setPosition(
			-visiablesize.width / 2 + _enemyprocess->_enmeynumbg->getContentSize().width / 2,
			visiablesize.height / 2 - _enemyprocess->_enmeynumbg->getContentSize().height / 2);
	this->addChild(_enemyprocess->_nodeenemyprocess);
	_enemyprocess->_nodeenemyprocess->setVisible(false);
	//*?–??Ω?????
	if (playScene->_gameModule == 3)
	{
		_enemyprocess->_nodeenemyprocess->setVisible(true);
	}
	else if (playScene->_gameModule == 2)
	{

	}
	else if (playScene->_gameModule == 4)
	{

		_nodemiss = CSLoader::createNode("panellayer/nodemiss.csb");
		this->addChild(_nodemiss);
		loadmissicon(_nodemiss);
		_bulletview->_bulletnum->setString("XX");
		_bulletview->setlock(true);
	}
	////*?¨??Ω?????
	Sprite* powerpool = Sprite::createWithSpriteFrameName(ImgPath::path_powerpoolbg_nomal);
	Sprite* spriteprocess = Sprite::createWithSpriteFrameName("texture_img/texture_button/combopowebuttonproess_1.png");
	comboPower = WimiProgress::create(powerpool, spriteprocess);

	float cb_X = visiablesize.width - powerpool->getContentSize().width / 2;
	float cb_Y = 0 + powerpool->getContentSize().height / 2;//Director::getInstance()->getVisibleOrigin().y 
	Vec2 realPoint = (Vec2(cb_X, cb_Y));
	comboPower->setPosition(realPoint.x, realPoint.y);//
	comboPower->setSpeed(10);
	comboPower->setNum(99, 99);
	_panelnode->addChild(comboPower);

	//????÷?≥÷∞?≈?
	button_fireSupport = ui::Button::create("panellayer/button_firesupport.png");
	button_fireSupport->setAnchorPoint(Vec2(0.5f, 0.5f));
	button_fireSupport->setPosition(Vec2(comboPower->getContentSize().width / 2, comboPower->getContentSize().height / 2));
	button_fireSupport->addTouchEventListener(CC_CALLBACK_2(PanelLayer::buttonFireSupportCallback, this));
	comboPower->addChild(button_fireSupport);

	turret = Turret::create("panellayer/connonf1.png");
	turret->setAnchorPoint(Vec2(0.49f, 0.18f));
	turret->setPosition(_connonPool->getContentSize().width / 2, _connonPool->getContentSize().height / 2);
	_connonPool->addChild(turret);
	_shade = nullptr;
	loadspriteframe();
}
void PanelLayer::addCombo(int _addnum)
{
	PlayScene*playScene = static_cast<PlayScene*>(this->getParent());
	Size winSize = Director::getInstance()->getWinSize();
	if (playScene->combo>=7)
		return;
	playScene->combo += _addnum;
	if (playScene->combo >= 2)
	{
		//展示combo
		char str_combo[10];
		sprintf(str_combo, "COMBO:%d", playScene->combo);
		GameInfoText* _addcombolabel = GameInfoText::create(str_combo, "font/fangzhengzongyijianti.ttf", 72);

		float p_X =0; //winSize.width/2 - _addcombolabel->getContentSize().width/2

		float p_Y = 0;//-winSize.height/2 +ariship->getPosition().y+ariship->getContentSize().height
			//+ _addcombolabel->getContentSize().height;

		_addcombolabel->setPosition(DataOfGame::getInstance()->LayerGetRealPosition(p_X,p_Y));
		_addcombolabel->setScale(0.1f);
		PanelLayer* panelLayer = static_cast<PanelLayer*>(playScene->getChildByName("panelLayer"));
		panelLayer->addChild(_addcombolabel, 5);
		CCCallFuncN* scaleFinish = CCCallFuncN::create([](Ref*sender) {
			Label* l_combo = static_cast<Label*>(sender);
			l_combo->removeFromParent();
		});
		_addcombolabel->showInfoText(scaleFinish);
		Audio::getInstance()->playeffectbykey("combo",true);
	}
}

void PanelLayer::resetCombo()
{
	//分数加成
	//先展示combo
	PlayScene*playScene = static_cast<PlayScene*>(this->getParent());	
	//PanelLayer* panelLayer = this;
	Size winSize = Director::getInstance()->getWinSize();
	if (playScene->combo < 2|| resetComboing)
	{
		playScene->combo = 0;
		return;
	}
	resetComboing = 1;
	int score = playScene->combo * 50;
	playScene->combo = 0;
	resetComboing = 0;
	playScene->reward_num += score;
	GameInfoText* _combofialtext = GameInfoText::create("FAILE!", "font/fangzhengzongyijianti.ttf", 48);
	_combofialtext->setAnchorPoint(Vec2(0.5f,0.5f));

	float p_X = winSize.width / 2 - _combofialtext->getContentSize().width / 2;

	float p_Y = -winSize.height / 2 + ariship->getPosition().y + ariship->getContentSize().height
		+ _combofialtext->getContentSize().height;

	_combofialtext->setPosition(DataOfGame::getInstance()->getrealposition(Vec2(p_X,p_Y)));
	_combofialtext->setScale(0.001f);

	this->addChild(_combofialtext,5);
	CCCallFuncN* scaleFinish = CCCallFuncN::create([=](Ref*sender){
			this->resetComboing = 0;
		});
	_combofialtext->showInfoText(scaleFinish);
	Audio::getInstance()->playeffectbykey("combofial");
}

void PanelLayer::addShade()
{
	if (_shade != nullptr)
	{
		return;
	}
	_shade = Sprite::create("setinglayer/shade_1.png");
	_shade->setName("shade");
	_shade->setPosition(DataOfGame::getInstance()->LayerGetRealPosition(0,0));
	this->addChild(_shade,5);
}

void PanelLayer::addshade_text(bool issuffule, std::string _str)
{
	Sprite* _gvshade = nullptr;
	_gvshade = static_cast<Sprite*>(this->getChildByName("shadetext"));
	if (_gvshade)
	{
		_gvshade->removeFromParentAndCleanup(true);
		_gvshade = nullptr;
		return;
	}
	_touchenable = false;
	_gvshade= Sprite::create("setinglayer/shade_1.png");
	_gvshade->setName("shadetext");
	_gvshade->setPosition(DataOfGame::getInstance()->LayerGetRealPosition(0, 0));
	this->addChild(_gvshade);
	ui::Text* _textgv = nullptr;
	_textgv =ui::Text::create(_str.c_str(), "font/fangzhengzongyijianti.ttf", 48);
	_textgv->setPosition(Vec2(_gvshade->getContentSize().width/2,_gvshade->getContentSize().height/2));
	_gvshade->addChild(_textgv);
	Audio::getInstance()->PlayEffect(Audio::getInstance()->geteffectbykey("messagepush"));
}
void PanelLayer::removeshade_text()
{
	Sprite* _gvshade = nullptr;
	_gvshade = static_cast<Sprite*>(this->getChildByName("shadetext"));
	_touchenable = true;
	if (_gvshade)
	{
		_gvshade->removeFromParentAndCleanup(true);
	}
}
void PanelLayer::setMissState(int _miss)
{
	if (_nodemiss == nullptr)
	{
		return;
	}
	int _index = 0;
	for (_index = 1; _index <= DataOfGame::getInstance()->_missnum; _index++)
	{
		char _strmissname[20];
		sprintf(_strmissname,"button_miss%d",_index);
		ui::Button* _buttonmiss = 
		static_cast<ui::Button*>(DataOfGame::getInstance()->seekNodebyName(_nodemiss,_strmissname));
		if(_index <= _miss)
		{ 
			_buttonmiss->setBrightStyle(ui::Widget::BrightStyle::HIGHLIGHT);
		}
		else
		{
			_buttonmiss->setBrightStyle(ui::Widget::BrightStyle::NORMAL);
		}
	}
}

void PanelLayer::loadmissicon(Node* _missnode)
{
	if (_missnode == nullptr)
	{
		return;
	}
	_missnode->setPosition(DataOfGame::getInstance()->LayerGetRealPosition(-285, 314));
	for (int _index =1 ; _index <= 5; _index++)
	{
		char _strbutton[20];
		sprintf(_strbutton, "button_miss%d", _index);
		ui::Button* _missbutton =
			static_cast<ui::Button*>(DataOfGame::getInstance()->seekNodebyName(_missnode, _strbutton));
		if(_index<DataOfGame::getInstance()->_missnum + 1)
		{
			_missbutton->setVisible(true);
		}
		else
		{
		 _missbutton->setVisible(false);
		}
	}
}

void PanelLayer::showrount(int _rount)
{
	PlayScene* _playscene = static_cast<PlayScene*>(this->getParent());
	Layer* _layershade = Layer::create();
	_layershade->setName("layershade");
	_layershade->init();
	this->addChild(_layershade);
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->setEnabled(true);
	listener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event*e)->bool 
	{
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,_layershade);
	Sprite* _rountshade = Sprite::create("setinglayer/shade_1.png");
	_rountshade->setName("rountshade");
	_rountshade->setPosition(DataOfGame::getInstance()->LayerGetRealPosition(0,0));
	_layershade->addChild(_rountshade);
	char _strrount[10];
	std::string _strdi = GameStringValue::getStringByKey("di")->c_str();
	std::string _strlun = GameStringValue::getStringByKey("lun")->c_str();
	sprintf(_strrount,"%s%d%s",_strdi.c_str(),DataOfGame::getInstance()->_round,_strlun.c_str());
	ui::Text* _trount = ui::Text::create(_strrount,"font/fangzhengzongyijianti.ttf",62);
	_trount->setPosition(Vec2(_rountshade->getContentSize().width/2,
		_rountshade->getContentSize().height/2));
	_rountshade->addChild(_trount);
	_playscene->isGameover = 2;
	this->scheduleOnce(schedule_selector(PanelLayer::removerount), 2.0f);
}

void PanelLayer::removerount(float dt)
{
	Layer* _layershade = nullptr;
	_layershade = static_cast<Layer*>(this->getChildByName("layershade"));
	if (_layershade)
	{	PlayScene* _playscene = static_cast<PlayScene*>(this->getParent());
		DataOfGame::getInstance()->recycle_bin.pushBack(_layershade);
		_playscene->isGameover = 0;
	}
}

Vec2 PanelLayer::getmidPos()
{
	Size visiSize = Director::getInstance()->getVisibleSize();
	Vec2 Org = Director::getInstance()->getVisibleOrigin();
	float _px = (-visiSize.width / 2) - (Org.x);
	float _py = (-visiSize.height / 2) - (Org.y);
	Vec2 _midpos = Vec2(_px,_py);
	return _midpos;
}

void PanelLayer::loadspriteframe()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture_img/conontexture/conontexture.plist");
}

void PanelLayer::showcourse(int _gamemodule)
{
	PlayScene* _playscene = static_cast<PlayScene*>(this->getParent());
	WellComeLayer* _wellcomlayer = WellComeLayer::create(_gamemodule);
	_wellcomlayer->setPosition(getmidPos());
	_wellcomlayer->setName("wellcomelayer");
	_wellcomlayer->_gamestate = &_playscene->isGameover;
	*_wellcomlayer->_gamestate = 2;
	this->addChild(_wellcomlayer);
	_wellcomlayer->loadpagedata();
}

void PanelLayer::removecourse()
{
	WellComeLayer* _wellcomlayer = nullptr;
	_wellcomlayer =static_cast<WellComeLayer*>(this->getChildByName("wellcomelayer"));
	if (_wellcomlayer == nullptr)
	{
		return;
	}
	DataOfGame::getInstance()->recycle_bin.pushBack(_wellcomlayer);
}

bool PanelLayer::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * e)
{
	return false;//_touchenable
}

void PanelLayer::showtextmessage(const char * _str)
{
	Size winSize = Director::getInstance()->getWinSize();
	ui::Text* _tmessage = ui::Text::create(_str, "font/fangzhengzongyijianti.ttf",48);
	_tmessage->setTextColor(Color4B::ORANGE);
	float _px = winSize.width/2 + _tmessage->getContentSize().width;//
	float _py = 200;
	_tmessage->setPosition(DataOfGame::getInstance()->LayerGetRealPosition(_px, _py));
	_tmessage->setScale(0.1f);
	MoveBy* _moveby = MoveBy::create(0.3f, Vec2(-_tmessage->getContentSize().width/2, 0));
	ScaleTo* _scaleto = ScaleTo::create(0.3f, 1.0f);
	FadeOut* _fadeout = FadeOut::create(1.0f);
	
	_tmessage->runAction(Sequence::create(Spawn::create(_moveby,_scaleto,nullptr),_fadeout,nullptr));
	this->addChild(_tmessage);
}

Vec2 * PanelLayer::getRealPosition(float x, float y)
{	
	Vec2* _realPoint =new Vec2();
	return _realPoint;
}

void PanelLayer::buttonFireSupportCallback(Ref*sender, ui::Widget::TouchEventType type)
{
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		Audio::getInstance()->playeffectbykey("click");
	}
	else if (type == ui::Widget::TouchEventType::ENDED)
	{
		PlayScene* playscene = static_cast<PlayScene*>(this->getParent());
		if (playscene->combo < 7)
		{
			return;
		}
		CCLOG("FireSupport");
		//button_fireSupport->setEnabled(false);
		Size visiableSize = Director::getInstance()->getVisibleSize();
		resetCombo();
		BulletLayer* bulletLayer = playscene->bulletLayer;
		for (int i = 0; i < DataOfGame::getInstance()->targetsVector.size(); ++i)
		{
			target* enemy = static_cast<target*>(DataOfGame::getInstance()->targetsVector.at(i));
			if (enemy->getKind() == 7)
				continue;
			FireBomb* fireBomb = FireBomb::create();
			fireBomb->setPhysicsBody(fireBomb->createRect(fireBomb->getContentSize()));
			float p_X = 0;
			p_X = random(-(int)(visiableSize.width / 2), (int)(visiableSize.width / 5));
			fireBomb->setPosition(p_X, -303);
			bulletLayer->addChild(fireBomb, 5);
		}
		Audio::getInstance()->playeffectbykey("firebomb");
	}
}

void PanelLayer::setingboxcallback(Ref * sender, ui::Widget::TouchEventType type)
{
	ui::Button* _button = static_cast<ui::Button*>(sender);
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		Audio::getInstance()->playeffectbykey("click");
		_button->setScale(0.8f);
	}
	else if (type == ui::Widget::TouchEventType::ENDED)
	{
		//auto button = static_cast<ui::Button*>(sender);
		_button->setScale(1.0f);
		SetingBox*setingBox = SetingBox::create();
		setingBox->setAnchorPoint(Vec2(0.5f, 0.5f));
		Vec2 _pos = getmidPos();
		setingBox->setPosition(_pos);							 
		this->addChild(setingBox);
		setingBox->_bg->setScale(0);
		setingBox->_bg->runAction(UiAction::getInstance()->pushin(0.2f,
			*CCCallFuncN::create([=](Ref*sender) {
			Director::getInstance()->pause();
		})));
		
	}
	else if (type == ui::Widget::TouchEventType::CANCELED)
	{
		_button->setScale(1.0f);
	}
}

void PanelLayer::buttonhelpCallback(Ref * sender, ui::Widget::TouchEventType type)
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
		PlayScene* playscene = static_cast<PlayScene*>(this->getParent());
		showcourse(playscene->_gameModule);
	}
	else if (type == ui::Widget::TouchEventType::CANCELED)
	{
		_button->setScale(1.0f);
	}
}


