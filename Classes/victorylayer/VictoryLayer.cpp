#include"VictoryLayer.h"

bool VictoryLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(VictoryLayer::onTouchBegan,this);
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->setSwallowsTouches(false);
	Size winsize = Director::getInstance()->getWinSize();
	Node* node_victorylayer = CSLoader::createNode("victorylayer/VictoryLayer.csb");
	node_victorylayer->setPosition(DataOfGame::getInstance()->getrealposition(Vec2(winsize.width/2,winsize.height/2)));
	this->addChild(node_victorylayer);
	Sprite* sprite_bg = static_cast<Sprite*>(DataOfGame::getInstance()->seekNodebyName(node_victorylayer,"sprite_bg"));
	nextround = static_cast<ui::Button*>
		(DataOfGame::getInstance()->seekNodebyName(node_victorylayer,"button_nextround"));
	nextround->addTouchEventListener(CC_CALLBACK_2(VictoryLayer::NextMenuCallback,this));
	nextround->setEnabled(false);
	replay = static_cast<ui::Button*>
		(DataOfGame::getInstance()->seekNodebyName(node_victorylayer, "button_replay"));
	replay->addTouchEventListener(CC_CALLBACK_2(VictoryLayer::RestartCallback, this));
	replay->setEnabled(false);
	menu = static_cast<ui::Button*>
		(DataOfGame::getInstance()->seekNodebyName(node_victorylayer, "button_menu"));
	menu->addTouchEventListener(CC_CALLBACK_2(VictoryLayer::JmpMenuCallback, this));
	menu->setEnabled(false);
	//*分数标签
	text_score = static_cast<ui::Text*>
		(DataOfGame::getInstance()->seekNodebyName(node_victorylayer,"text_score"));
	sprite_rect1 = static_cast<Sprite*>
		(DataOfGame::getInstance()->seekNodebyName(node_victorylayer,"sprite_rect1"));
	//剩余文本
	text_residue= static_cast<ui::Text*>
		(DataOfGame::getInstance()->seekNodebyName(node_victorylayer, "text_residue"));
	//奖励文本
	text_gift= static_cast<ui::Text*>
		(DataOfGame::getInstance()->seekNodebyName(node_victorylayer, "text_gift"));
	text_gold = static_cast<ui::Text*>
		(DataOfGame::getInstance()->seekNodebyName(node_victorylayer, "text_gold"));
	//
	sprite_rect2= static_cast<Sprite*>
		(DataOfGame::getInstance()->seekNodebyName(node_victorylayer, "sprite_rect2"));
	sprite_rect3 = static_cast<Sprite*>
		(DataOfGame::getInstance()->seekNodebyName(node_victorylayer, "sprite_rect3"));
	sprite_rect4 = static_cast<Sprite*>
		(DataOfGame::getInstance()->seekNodebyName(node_victorylayer, "sprite_rect4"));
	sprite_rect4->setVisible(false);

	return true;
}

VictoryLayer * VictoryLayer::create()
{
	VictoryLayer* victoryLayer = new VictoryLayer();
	victoryLayer->init();
	victoryLayer->setAnchorPoint(Vec2(0.5f,0.5f));
	return victoryLayer;
}

void VictoryLayer::accountScore(int score)
{	
	PlayScene* playScene=static_cast<PlayScene*>(this->getParent());
	//奖励信息
	int reward_score = playScene->reward_num;
	char str_rewrad[100];
	std::string* str_jiangli = GameStringValue::getStringByKey("jiangli");
	sprintf(str_rewrad, "%s:%d",str_jiangli->c_str(), reward_score);
	text_gift->setString(str_rewrad);
	//updateTextPosition(sprite_rect3, text_gift);
	this->_score = score;
	this->_addspeed = score / (_ADDSCORESPEED * 10);
	this->_addscore = 0;
	this->schedule(schedule_selector(VictoryLayer::accounttimer),0.1f);
}
void VictoryLayer::accounttimer(float dt)
{
	char str_score[100];
	std::string* str_defen = GameStringValue::getStringByKey("defen");
	sprintf(str_score,"%s:%d",str_defen->c_str(),_addscore);
	if (_addscore < _score)
	{
		_addscore += _addspeed;
	}
	else
	{
		//注销定时器
		unschedule(schedule_selector(VictoryLayer::accounttimer));
		CCCallFuncN* callback = CCCallFuncN::create(CC_CALLBACK_1(VictoryLayer::addresidue, this));
		sprite_rect2->runAction(createAddScoreAction(callback));
		
	}
	text_score->setString(str_score);
	//updateTextPosition(sprite_rect1, text_score);
}
void VictoryLayer::addreward(Ref*sender)
{
	PlayScene* playScene = static_cast<PlayScene*>(this->getParent());
	//奖励信息
	int reward_score = playScene->reward_num;
	DataOfGame::getInstance()->_scorenow += reward_score;
	playScene->reward_num = 0;//奖励分数清零
	_score =DataOfGame::getInstance()->_gameScore + DataOfGame::getInstance()->_scorenow;
	char str_score[100];
	std::string* str_defen = GameStringValue::getStringByKey("defen");
	sprintf(str_score, "%s:%d", str_defen->c_str(), _score);
	text_score->setString(str_score);
	Audio::getInstance()->playeffectbykey("ding");
	DataOfGame::getInstance()->recycle_bin.pushBack(sprite_rect3);
	//*开始显示金币
	char _strgold[30];
	std::string _strjinbi = GameStringValue::getStringByKey("jinbi")->c_str();
	sprintf(_strgold,"%s:%d",_strjinbi.c_str(),DataOfGame::getInstance()->getGold());
	text_gold->setString(_strgold);
	sprite_rect4->setVisible(true);
	sprite_rect4->setScale(0);
	sprite_rect4->runAction(UiAction::getInstance()->pushin(0.2f, *CCCallFuncN::create([=](Ref*sender) {
	accountgold();
	})));
}
void VictoryLayer::addresidue(Ref*sender)
{
	DataOfGame::getInstance()->_scorenow += 120 * _bulletResidue;
	_score = DataOfGame::getInstance()->_scorenow+ DataOfGame::getInstance()->_gameScore;
	char str_score[100];
	std::string* str_defen = GameStringValue::getStringByKey("defen");
	sprintf(str_score, "%s:%d", str_defen->c_str(), _score);
	text_score->setString(str_score);
	//updateTextPosition(sprite_rect1, text_score);
	CCCallFuncN* callback = CCCallFuncN::create(CC_CALLBACK_1(VictoryLayer::addreward, this));
	sprite_rect3->runAction(createAddScoreAction(callback));
	DataOfGame::getInstance()->recycle_bin.pushBack(sprite_rect2);
	Audio::getInstance()->playeffectbykey("ding");
}
void VictoryLayer::accountgold()
{
	Vec2 _textps = Vec2(text_gold->getContentSize().width, text_gold->getContentSize().height);
	char _strgold[10];
	int _addgold = _score / 100;
	sprintf(_strgold,"%d",_addgold);
	ui::Text* _addtext = ui::Text::create(_strgold, "font/fangzhengzongyijianti.ttf", 48);
	_addtext->setPosition(_textps);
	text_gold->addChild(_addtext);
	_addtext->setScale(0);
	_addtext->runAction(UiAction::getInstance()->pushin(1.0f, *CCCallFuncN::create([=](Ref* sender) {
		int _gold = DataOfGame::getInstance()->getGold();
		_gold += _addgold;
		DataOfGame::getInstance()->setGold(_gold);
		_addtext->removeFromParentAndCleanup(true);
		Audio::getInstance()->playeffectbykey("ding");
		char _strgold[30];
		std::string* _strjinbi = GameStringValue::getStringByKey("jinbi");
		sprintf(_strgold,"%s:%d", _strjinbi->c_str(), DataOfGame::getInstance()->getGold());
		text_gold->setString(_strgold);
		//所有结算动作结束
		nextround->setEnabled(true);
		nextround->runAction(UiAction::getInstance()->buttonsacle(0.1f));
		replay->setEnabled(true);
		replay->runAction(UiAction::getInstance()->buttonsacle(0.1f));
		menu->setEnabled(true);
		menu->runAction(UiAction::getInstance()->buttonsacle(0.1f));
	})));
}

Action * VictoryLayer::createAddScoreAction(CCCallFuncN* callback)
{
	Action* action = nullptr;
	ScaleTo* scalebig = ScaleTo::create(0.5f, 1.2f);
	MoveTo* moveToScoreText = MoveTo::create(0.5f, 
		Vec2(sprite_rect1->getPosition().x+text_score->getContentSize().width/2,sprite_rect1->getPosition().y));
	DelayTime* delay05s = DelayTime::create(0.5f);
	ScaleTo* scaleSmall = ScaleTo::create(0.1f, 0.01f);
	action=Sequence::create(Spawn::create(scalebig,moveToScoreText, nullptr),delay05s, scaleSmall, callback, nullptr);
	return action;
}
void VictoryLayer::passallround()
{
	Layer* _passall = static_cast<Layer*>(CSLoader::createNode("victorylayer/passallround.csb"));
	this->addChild(_passall);
	auto listener = EventListenerTouchOneByOne::create();
	listener->setEnabled(true);
	listener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event*e)->bool {
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	Sprite* _sahde = static_cast<Sprite*>(DataOfGame::getInstance()->seekNodebyName(_passall,"sprite_shade"));
	Sprite* _bg= static_cast<Sprite*>(DataOfGame::getInstance()->seekNodebyName(_passall, "sprite_bg"));
	ui::Text* _textnum= static_cast<ui::Text*>(DataOfGame::getInstance()->seekNodebyName(_passall, "text_num"));
	ui::Button* _buttonget= static_cast<ui::Button*>(DataOfGame::getInstance()->seekNodebyName(_passall, "button_next"));
	_buttonget->addTouchEventListener(CC_CALLBACK_2(VictoryLayer::passallcallback,this));
}
//void VictoryLayer::updateTextPosition(Sprite * panel, ui::Text * text)
//{
//	float p_x =
//		(panel->getContentSize().width + text->getContentSize().width / 2);
//	text->setPositionX(p_x);
//}
void VictoryLayer::accountBullet(int countBullet,int& score)
{
	_bulletResidue = countBullet;
	char str_score[100];
	std::string* str_shengyu = GameStringValue::getStringByKey("shengyu");
	sprintf(str_score,"%s:%d",str_shengyu->c_str(),countBullet);
	text_residue->setString(str_score);
	//updateTextPosition(sprite_rect2, text_residue);
}

void VictoryLayer::RestartCallback(Ref * sender, ui::Widget::TouchEventType type)
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
		DataOfGame::getInstance()->_scorenow = 0;
		playScene->Replay();
		this->removeFromParent();
	}
	else if (type == ui::Widget::TouchEventType::CANCELED)
	{
		_button->setScale(1.0f);
	}
}

void VictoryLayer::NextMenuCallback(Ref * sender, ui::Widget::TouchEventType type)
{
	ui::Button* _button = static_cast<ui::Button*>(sender);
	if (type == ui::Widget::TouchEventType::BEGAN)
	{
		Audio::getInstance()->playeffectbykey("click");
		_button->setScale(0.8f);
	}
	if (type == ui::Widget::TouchEventType::ENDED)
	{
		//*下一关	
		//把当前所得分数+累计分数
		_button->setScale(1.0f);
		//DataOfGame::getInstance()->_gameScore = DataOfGame::getInstance()->_gameScore + DataOfGame::getInstance()->_scorenow;
		DataOfGame::getInstance()->_scorenow = 0;
		GameModule3ResetData();
		Node* menu = static_cast<Node*>(sender);
		PlayScene* playScene = static_cast<PlayScene*>(this->getParent());
		PanelLayer* panelLayer = static_cast<PanelLayer*>(playScene->getChildByName("panelLayer"));
		panelLayer->resetCombo();//重置combo
		if (DataOfGame::getInstance()->getround() < _MAXROUND)
		{
			DataOfGame::getInstance()->setround(DataOfGame::getInstance()->getround()+1);
		}
		else
		{
			//通关
			passallround();
			return;
		}
		DataOfGame::getInstance()->Load_RoundData(DataOfGame::getInstance()->_round);
		this->removeFromParent();
		panelLayer->resetComboing = 0;
		panelLayer->showrount(DataOfGame::getInstance()->_round);
	}
	else if (type == ui::Widget::TouchEventType::CANCELED)
	{
		_button->setScale(1.0f);
	}
}

void VictoryLayer::JmpMenuCallback(Ref * sender, ui::Widget::TouchEventType type)
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
		DataOfGame::getInstance()->_gameScore = DataOfGame::getInstance()->_scorenow;
		DataOfGame::getInstance()->_scorenow = 0;
		PlayScene* playScene = static_cast<PlayScene*>(this->getParent());
		PanelLayer* panelLayer = static_cast<PanelLayer*>(playScene->getChildByName("panelLayer"));
		GameModule3ResetData();
		Scene* mainScene = MainScene::createScene();
		panelLayer->resetComboing = 0;
		playScene->isGameover = 0;
		Director::getInstance()->replaceScene(CCTransitionFade::create(1.0f, mainScene,Color3B::BLACK));
		this->stopAllActions();
	}
	else if (type == ui::Widget::TouchEventType::CANCELED)
	{
		_button->setScale(1.0f);
	}
}

void VictoryLayer::passallcallback(Ref * sender, ui::Widget::TouchEventType type)
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
		DataOfGame::getInstance()->_gameScore = DataOfGame::getInstance()->_scorenow;
		DataOfGame::getInstance()->_scorenow = 0;
		PlayScene* playScene = static_cast<PlayScene*>(this->getParent());
		PanelLayer* panelLayer = static_cast<PanelLayer*>(playScene->getChildByName("panelLayer"));
		GameModule3ResetData();
		Scene* mainScene = MainScene::createScene();
		panelLayer->resetComboing = 0;
		playScene->isGameover = 0;
		//发放奖励99999金币
		DataOfGame::getInstance()->setGold(DataOfGame::getInstance()->getGold()+99999);
		Director::getInstance()->replaceScene(CCTransitionFade::create(1.0f, mainScene, Color3B::BLACK));
		this->stopAllActions();
		DataOfGame::getInstance()->setround(1);
	}
	else if (type == ui::Widget::TouchEventType::CANCELED)
	{
		_button->setScale(1.0f);
	}
}

bool VictoryLayer::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * e)
{
	return true;
}

void VictoryLayer::GameModule3ResetData()
{
	PlayScene* playScene = static_cast<PlayScene*>(this->getParent());
	DataOfGame::getInstance()->totleEnemy = 0;
	DataOfGame::getInstance()->enemyResidue = 0;
	DataOfGame::getInstance()->enemyOnScene = 0;
	playScene->_propList[2] = 0;
	playScene->_gameState = 0;
	for (int i = 0; i < DataOfGame::getInstance()->targetsVector.size(); ++i)
	{
		DataOfGame::getInstance()->recycle_bin.pushBack(DataOfGame::getInstance()->targetsVector.at(i));
	}
	DataOfGame::getInstance()->targetsVector.clear();
}

//void VictoryLayer::GameModule2RestData()
//{
//	
//}
