#include "GameoverLayer.h"

bool GameOverLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameOverLayer::onTouchBegan, this);
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	TargetMaker::getinstance()->unloadenemytexture();
	AdviewAd::showInstl();
	return true;
}

GameOverLayer * GameOverLayer::create()
{
	GameOverLayer *gameoverLayer = new GameOverLayer();
	gameoverLayer->init();
	return gameoverLayer;
}

void GameOverLayer::accoutHeightScore()
{
	//记录最高分
	FullLeaderboardFromDataBase();
}

void GameOverLayer::accountScore()
{
	PlayScene* _playscene = static_cast<PlayScene*>(this->getParent());
	char str_score[20];
	//char _strmodule[10];
	int _score = 0;
	_score = DataOfGame::getInstance()->_gameScore +
		DataOfGame::getInstance()->_scorenow + _playscene->reward_num;
	_playscene->reward_num = 0;//奖励分数清零
	//sprintf(_strmodule, "Module%d", _playscene->_gameModule);
	sprintf(str_score, "%d", _score);
	if (_playscene->_gameModule == 3)
	{
		scoreAccountLayer = this;
	}
	else
	{
		scoreAccountLayer = static_cast<Layer*>(CSLoader::createNode("gameoverlayer/gameoveraccountlayer.csb"));
		this->addChild(scoreAccountLayer);
		auto callback = [](Touch *, Event *)
		{
			return true;
		};
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = callback;
		listener->setSwallowTouches(true);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, scoreAccountLayer);
	}
	_sprite_accountbg = static_cast<Sprite*>
		(DataOfGame::getInstance()->seekNodebyName(scoreAccountLayer, "sprite_accountbg"));
	if (_playscene->_gameModule != 3)
	{
		_sprite_accountbg->setScale(0);
		_sprite_accountbg->runAction(UiAction::getInstance()->pushin(0.2f, *CCCallFuncN::create(nullptr)));
	}
	_gameovertitle= static_cast<ui::Text*>
		(DataOfGame::getInstance()->seekNodebyName(scoreAccountLayer, "text_gameover"));
	_gameovertitle->setSkewX(10);
	 _textScoreLabel = static_cast<ui::Text*>
		(DataOfGame::getInstance()->seekNodebyName(scoreAccountLayer,"text_scorelabel"));
	 _textScoreLabel->setSkewX(10);
	 _textscore= static_cast<ui::Text*>
		(DataOfGame::getInstance()->seekNodebyName(scoreAccountLayer, "text_score"));
	_textscore->setString(str_score);
	_textgoldlabel= static_cast<ui::Text*>
		(DataOfGame::getInstance()->seekNodebyName(scoreAccountLayer, "text_goldlabel"));
	_textgoldlabel->setSkewX(10);
	_textgold= static_cast<ui::Text*>
		(DataOfGame::getInstance()->seekNodebyName(scoreAccountLayer, "text_gold"));
	int _addgold = accountgold((int)(_score));
	char _strgold[10];
	sprintf(_strgold,"%d",DataOfGame::getInstance()->gold);
	_textgold->setString(_strgold);

	_buttonok= static_cast<ui::Button*>
		(DataOfGame::getInstance()->seekNodebyName(scoreAccountLayer, "button_ok"));
	_buttonok->addTouchEventListener(CC_CALLBACK_2(GameOverLayer::buttonokcallck,this));
	_buttonok->runAction(UiAction::getInstance()->buttonsacle(0.1f));
	_buttonok->setEnabled(false);
	if (_playscene->_gameModule == 3)
	{
		_buttonok->setVisible(false);
	}
	char _straddgold[10];
	sprintf(_straddgold,"+ %d", _addgold);
	ui::Text* _textaddgold = ui::Text::create(_straddgold,"font/fangzhengzongyijianti.ttf",56);
	_textaddgold->setPosition(
		Vec2(_textgold->getPosition().x+_textgold->getContentSize().width+20,_textgold->getPosition().y));
	_textaddgold->setTextColor(Color4B::YELLOW);
	_textaddgold->setAnchorPoint(Vec2(0,0.5));
	_sprite_accountbg->addChild(_textaddgold);
	ScaleTo* _scalebig = ScaleTo::create(0.3f,1.2f);
	MoveBy* _moveup = MoveBy::create(0.3f, Vec2(0, 50));
	CCCallFuncN* _faddgold = CCCallFuncN::create([=](Ref*sender) 
	{	
		int _goldnow = _addgold + DataOfGame::getInstance()->gold;
		DataOfGame::getInstance()->setGold(_goldnow);//修改金币的值
		char _strgold[10];
		sprintf(_strgold,"%d",_goldnow);
		_textgold->setString(_strgold);
	});
	CCCallFuncN* _addfinish = CCCallFuncN::create([=](Ref*sender) 
	{
		_buttonok->setEnabled(true);
		Audio::getInstance()->playeffectbykey("ding");
		DataOfGame::getInstance()->recycle_bin.pushBack(_textaddgold);
		//if (_playscene->_gameModule == 3)
		//{
		//	PushInputBox();
		//}
		
	});
	DelayTime* _delay1s = DelayTime::create(1.0f);
	_textaddgold->runAction(Sequence::create(Spawn::create(_scalebig,_moveup,nullptr),  _faddgold,_delay1s, _addfinish,nullptr));
}

void GameOverLayer::freedspriteframe()
{
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("gameoverlayer/rank_icon.plist");
}

void GameOverLayer::loadui()
{
	PlayScene* _playscene = static_cast<PlayScene*>(this->getParent());
	Node* _gameovernode = CSLoader::createNode("gameoverlayer/gameoverlayer.csb");
	this->addChild(_gameovernode);
	sprite_bg = static_cast<Sprite*>(DataOfGame::getInstance()->seekNodebyName(_gameovernode, "sprite_bg"));
	_replaybutton = static_cast<ui::Button*>(DataOfGame::getInstance()->seekNodebyName(_gameovernode, "button_replay"));
	_replaybutton->addTouchEventListener(CC_CALLBACK_2(GameOverLayer::ReplayCallback, this));
	_replaybutton->runAction(UiAction::getInstance()->buttonsacle(0.1f));
	_menubutton = static_cast<ui::Button*>(DataOfGame::getInstance()->seekNodebyName(_gameovernode, "button_menu"));
	_menubutton->addTouchEventListener(CC_CALLBACK_2(GameOverLayer::MenuCallback, this));
	_menubutton->runAction(UiAction::getInstance()->buttonsacle(0.1f));
	_sharebutton = static_cast<ui::Button*>(DataOfGame::getInstance()->seekNodebyName(_gameovernode, "buttonshare"));
	_sharebutton->addTouchEventListener(CC_CALLBACK_2(GameOverLayer::ShareCallback, this));
	_sharebutton->setEnabled(false);
	Sprite* _rankbg = static_cast<Sprite*>(DataOfGame::getInstance()->seekNodebyName(_gameovernode, "sprite_rankbg"));

	//*œ˙ªŸ
	_listview1 = static_cast<ui::ListView*>(DataOfGame::getInstance()->seekNodebyName(_gameovernode, "listview_rank"));
	if (_playscene->_gameModule == 3)
	{
		_listview1->setVisible(false);
		_listview1->removeFromParentAndCleanup(true);
		_rankbg->setVisible(false);
		_rankbg->removeFromParentAndCleanup(true);
	}

	_sprite_accountbg = static_cast<Sprite*>(DataOfGame::getInstance()->seekNodebyName(_gameovernode, "sprite_accountbg"));
	if (_playscene->_gameModule == 2 || _playscene->_gameModule == 4)
	{
		_listview1->removeAllItems();
		_listview1->setVisible(true);
		_sprite_accountbg->setVisible(false);
		_sprite_accountbg->removeFromParentAndCleanup(true);
	}

	//
}


void GameOverLayer::accountBullet()
{

}

void GameOverLayer::rankList()
{

}
void GameOverLayer::ReplayCallback(Ref * sender, ui::Widget::TouchEventType type)
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
		freedspriteframe();
		PlayScene* playScene = static_cast<PlayScene*>(this->getParent());
		playScene->Replay();
		this->removeFromParentAndCleanup(true);
	}
	else if (type == ui::Widget::TouchEventType::CANCELED)
	{
		_button->setScale(1.0f);
	}
}

void GameOverLayer::MenuCallback(Ref * sender, ui::Widget::TouchEventType type)
{
	ui::Button* _button = static_cast<ui::Button*>(sender);
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		Audio::getInstance()->playeffectbykey("click");
		_button->setScale(0.8f);
	}
	else if (type == ui::Widget::TouchEventType::ENDED)
	{
		PlayScene* playScene = static_cast<PlayScene*>(this->getParent());
		PanelLayer* panelLayer = static_cast<PanelLayer*>(playScene->getChildByName("panelLayer"));
		freedspriteframe();
		Scene* mainScene = MainScene::createScene();
		panelLayer->resetComboing = 0;
		playScene->_gameState = 0;
		Director::getInstance()->replaceScene(CCTransitionFade::create(3.0f, mainScene));
		_button->setScale(1.0f);
	}
	else if (type == ui::Widget::TouchEventType::CANCELED)
	{
		_button->setScale(1.0f);
	}
}

bool GameOverLayer::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * e)
{
	return true;
}

void GameOverLayer::ShareCallback(Ref * sender, ui::Widget::TouchEventType type)
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
		//分享按钮
	}
	else if (type == ui::Widget::TouchEventType::CANCELED)
	{
		_button->setScale(1.0f);
	}
}

void GameOverLayer::GameModule3ResateData()
{
	/*PlayScene* playScene = static_cast<PlayScene*>(this->getParent());
	PanelLayer* panelLayer = static_cast<PanelLayer*>(playScene->getChildByName("panelLayer"));
	DataOfGame::getInstance()->totleEnemy = 0;
	DataOfGame::getInstance()->enemyResidue = 0;
	DataOfGame::getInstance()->enemyOnScene = 0;
	playScene->_propList[2] = 0;
	DataOfGame::getInstance()->Load_RoundData(DataOfGame::getInstance()->_round);
	panelLayer->resetComboing = 0;
	playScene->combo = 0;
	playScene->isGameover = 0;*/
}

void GameOverLayer::GameModule2ResateData()
{
	//PlayScene* playScene = static_cast<PlayScene*>(this->getParent());
	//PanelLayer* panelLayer = static_cast<PanelLayer*>(playScene->getChildByName("panelLayer"));
	//DataOfGame::getInstance()->_bulletTotle = 35;
	////TODO:保存最高分
	//DataOfGame::getInstance()->_gameScore = 0;
	//panelLayer->resetComboing = 0;
}

void GameOverLayer::FullLeaderboardFromDataBase()
{
	PlayScene* playScene = static_cast<PlayScene*>(this->getParent());
	char _strmodule[10];
	sprintf(_strmodule, "Module%d", playScene->_gameModule);
	_listview1->removeAllItems();
	for (int index = 1; index <= _LEADERBOARDSIZE; index++)
	{
		std::string _strname = DataOfGame::getInstance()->_sqliteManager->getName(index, _strmodule);
		std::string _strscore = DataOfGame::getInstance()->_sqliteManager->getScore(index, _strmodule);
		if (_strscore == " ")
		{
			break;
		}
		RankItem* _rankitem = RankItem::create(index, _strname, atoi(_strscore.c_str()));
		_listview1->pushBackCustomItem(_rankitem);
	}
}

void GameOverLayer::AddHightToDataBase(char* _module, char * _username, int _score)
{
	//先找到要插入的位置
	int _maxrank = 5;
	int _posrank = 1;
	int _ranksize = 5;
	for (int index = 6; index > 0; --index)
	{
		int _tscore = 0;
		string _strscore=DataOfGame::getInstance()->_sqliteManager->getScore(index,_module);
		_tscore = std::atoi(_strscore.c_str());
		if (_tscore == 0)
		{
			_ranksize = index-1;
		}
		if (_tscore > _score)
		{
			_posrank = index+1;
			break;
		}
	}
	CCLOG("_posrank=%d,_ranksizek=%d",_posrank, _ranksize);
	char _strrank[20];
		sprintf(_strrank,"%d",_posrank);
		char _strscore[20];
		sprintf(_strscore,"%d",_score);
	if (_posrank > _ranksize)
	{
		//直接插入数据
		if(_posrank<_maxrank)
		{ 
		 DataOfGame::getInstance()->_sqliteManager->insertData(_module, _strrank, _username, _strscore);
		}
		else
		{
			//未上榜
			CCLOG("no in bord!");
		}
	}
	else
	{
		//插入前移动数据
		//先查找posrank下一个记录，
		//这条记录是否存在
		string _strscore = DataOfGame::getInstance()->_sqliteManager->getScore(_posrank + 1, _module);
		if (_strscore > "0")
		{
			//如果存在就用上一条记录覆盖这条记录
			for (int index = _ranksize; index >_posrank;index--)
			{
				string _strscore_1 = DataOfGame::getInstance()->_sqliteManager->getScore(index - 1, _module);
				string _strname_1 = DataOfGame::getInstance()->_sqliteManager->getName(index-1,_module);
				char _strrank[20];
				sprintf(_strrank,"%d",index);
				DataOfGame::getInstance()->_sqliteManager->updateData(_module, _strrank, _strname_1.c_str(), _strscore_1.c_str());
			}
			char _strposrank[20];
			sprintf(_strposrank,"%d",_posrank);
			char _strnscore[20];
			sprintf(_strnscore,"%d",_score);
			DataOfGame::getInstance()->_sqliteManager->updateData(_module, _strposrank, _username, _strnscore);
		}
		else
		{
			//如果不存在就创建一条记录并且用上一条记录填充该记录
			string _strlscore= DataOfGame::getInstance()->_sqliteManager->getScore(_posrank, _module);
			string _strlname=DataOfGame::getInstance()->_sqliteManager->getName(_posrank, _module);
			char _strrank_1[20];
			sprintf(_strrank_1,"%d",_posrank+1);
			DataOfGame::getInstance()->_sqliteManager->insertData(_module, _strrank_1, _strlname.c_str(), _strlscore.c_str());
			char _strscore_1[20];
			sprintf(_strscore_1,"%d",_score);
			DataOfGame::getInstance()->_sqliteManager->updateData(_module, _strrank, _username, _strscore_1);
		}
	}
}

void GameOverLayer::PushInputBox()
{
	_inputLayer =static_cast<Layer*>(CSLoader::createNode("gameoverlayer/Inputlayer.csb"));
	this->addChild(_inputLayer);
	auto callback = [](Touch *, Event *)
	{
		return true;
	};
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = callback;
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _inputLayer);
	PlayScene* playScene = static_cast<PlayScene*>(this->getParent());
	_inputbg= static_cast<Sprite*>
		(DataOfGame::getInstance()->seekNodebyName(_inputLayer, "sprite_inputbg"));
	_inputbg->runAction(UiAction::getInstance()->pushin(0.2f,*CCCallFuncN::create(nullptr)));
	_inputbox= static_cast<ui::TextField*>(DataOfGame::getInstance()->seekNodebyName(_inputLayer,"textfield_inputbox"));
	_inputbox->addEventListener(CC_CALLBACK_2(GameOverLayer::TextFieldEvent, this));
	if (playScene->_username.size()>0 && playScene->_username!=" ")
	{
		_inputbox->setString(playScene->_username);
	}
	ui::Button* _inputok= static_cast<ui::Button*>(DataOfGame::getInstance()->seekNodebyName(_inputLayer, "button_ok"));
	_inputok->addTouchEventListener(CC_CALLBACK_2(GameOverLayer::inputcallback,this));
	_inputok->runAction(UiAction::getInstance()->buttonsacle(0.1f));
}

void GameOverLayer::TextFieldEvent(Ref * sender, ui::TextField::EventType type)
{
	ui::TextField * textField = _inputbox;
	switch (type)
	{
		case ui::TextField::EventType::ATTACH_WITH_IME:
		{	
			FadeIn* _fadeIn = FadeIn::create(0.3f);
			FadeOut* _fadeout = FadeOut::create(0.3f);
			textField->runAction(RepeatForever::create(Sequence::create(_fadeIn,_fadeout,nullptr)));
		}break;
		case ui::TextField::EventType::DETACH_WITH_IME:
		{
			textField->stopAllActions();
		}break;
		case ui::TextField::EventType::INSERT_TEXT:
		{
			textField->stopAllActions();
		}break;
		case ui::TextField::EventType::DELETE_BACKWARD:
		{
			textField->stopAllActions();
		}break;	
	}
}

int GameOverLayer::accountgold(int _score)
{
	PlayScene* playScene = static_cast<PlayScene*>(this->getParent());
	int _gold = 0;
	switch (playScene->_gameModule)
	{
	case 2:
	{
		_gold = _score / 1000;
	}break;
	case 3:
	{
		_gold = _score / 100;
	}break;
	case 4:
	{
		_gold = _score / 100;
	}break;
	default:
		break;
	}
	return (int)(_gold);
}

void GameOverLayer::buttonokcallck(Ref * sender, ui::Widget::TouchEventType type)
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
		_sprite_accountbg->runAction(UiAction::getInstance()->pushout(0.3f,
			*CCCallFuncN::create([=](Ref*) {
		PushInputBox();
		scoreAccountLayer->removeFromParent();
		})));
		
	}
	else if (type == ui::Widget::TouchEventType::CANCELED)
	{
		_button->setScale(1.0f);
	}
}

void GameOverLayer::addgoldcallback(Ref * sender)
{
}

void GameOverLayer::inputcallback(Ref * sender, ui::Widget::TouchEventType type)
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
		PlayScene* playScene = static_cast<PlayScene*>(this->getParent());
		char _strmodule[10];
		sprintf(_strmodule, "Module%d", playScene->_gameModule);
		CCLOG("yourname=%s", _inputbox->getString().c_str());

		if (_inputbox->getString()=="" || _inputbox->getString() ==" ")
		{
			//内容不合法
			return;
		}
		playScene->_username = _inputbox->getString().c_str();
		DataOfGame::getInstance()->setUsername(playScene->_username.c_str());
		AddHightToDataBase((char*)_strmodule, (char*)playScene->_username.c_str(),
			DataOfGame::getInstance()->_gameScore + DataOfGame::getInstance()->_scorenow + playScene->reward_num);
			if(playScene->_gameModule!=3)
			{
				FullLeaderboardFromDataBase(); 
			}
		_inputbg->runAction(UiAction::getInstance()->pushout(0.3f,
			*CCCallFuncN::create([=](Ref*sender) {
			_inputLayer->removeFromParent();
		})));
		
	}
	else if (type == ui::Widget::TouchEventType::CANCELED)
	{
		_button->setScale(1.0f);
	}
}

