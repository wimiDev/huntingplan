#include "PlayScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* PlayScene::createScene(int gameModule)
{
    // 'scene' is an autorelease object
	//auto scene = Scene::create();
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    
    // 'layer' is an autorelease object
    auto layer = PlayScene::create();

    // add layer as a child to scene
    scene->addChild(layer);
	layer->_gameModule = gameModule;
	layer->initGameData(gameModule);
    // return the scene
    return scene;
}
// on "init" you need to initialize your instance
bool PlayScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
	//initGameData(_gameModule);
    return true;
}
void PlayScene::onEnterTransitionDidFinish()
{
	w_onEnter();
	_isTransitionFinished = true;
}
void PlayScene::changeGameState()
{
	if(_gameModule==3)
	{ 
		float per = (DataOfGame::getInstance()->enemyResidue*1.0/ DataOfGame::getInstance()->totleEnemy);
		if (per < (1.0 / 3))
		{
			_addEnemyTimer = 2.0f;
			_gameState = 2;
		}
		else if (per>1.0 / 3 && per < 2.0 / 3)
		{
			_addEnemyTimer =1.0f;
			_gameState = 1;
		}
		else
		{
			_addEnemyTimer = 0.1f;
			_gameState = 0;
		}
	}

}
void PlayScene::gameModule4Update()
{
	if (_statetime >= _nexttime)
	{
		int _next = 0;
		DataOfGame::getInstance()->loadmodule4dat(_module4dp,_next);
		_module4dp++;
		_nexttime += _next;
		DataOfGame::getInstance()->totleEnemy *= _grads;
		//如果检测到0，本次状态结束
		if (_next == 0)
		{
			_statetime = 0;
			_module4dp = 0;
			_nexttime = 0;
			_grads ++;
		}
		
	}
	panelLayer->setMissState(_omitEnemy);
	if (_omitEnemy >=DataOfGame::getInstance()->_missnum&&isGameover!=1)
	{
		isGameover = 1;
		_gameoverpoint = *GameStringValue::getStringByKey("nbnfzdr");
		//panelLayer->addshade_text(0,_strgv);
		_isfire = -1;
		_propList[2] = 0;//停止能量支持
		this->scheduleOnce(schedule_selector(PlayScene::gameOverTimer_ones),0.5f);
		
	}
	if (isGameover!=1&& _killspy)
	{
		_killspy = 0;
		//isGameover = 1;
		_isfire = -1;
		_omitEnemy++;
		//_gameoverpoint = *GameStringValue::getStringByKey("jljd");
		//panelLayer->addshade_text(0, _strgv);
		//_propList[2] = 0;//停止能量支持
		//this->scheduleOnce(schedule_selector(PlayScene::gameOverTimer_ones), 0.5f);
	}
}
void PlayScene::gameModule2Update()
{
	if (DataOfGame::getInstance()->_bulletTotle <= 0 &&
		isGameover==0&&_propList[2]<=0)
	{
		isGameover = 1;
		_gameoverpoint = *GameStringValue::getStringByKey("ywsypd");
		scheduleOnce(schedule_selector(PlayScene::gameOverTimer_ones), 2.5f);
	}
	if (DataOfGame::getInstance()->_bulletTotle> 0 &&isGameover!=0
		&&_propList[2] <= 0&& isGameover!=-1)
	{
		isGameover = 0;
	}

}
void PlayScene::gameModule3Update()
{
	//*判断是否挑战成功
	if (DataOfGame::getInstance()->targetsVector.size() == 0 
		&& DataOfGame::getInstance()->enemyResidue == 0&&
		isGameover!=-1)
	{
		isGameover = -1;
		std::string _strvt = *GameStringValue::getStringByKey("jlsydr");//击落所有敌人
		panelLayer->addshade_text(1, _strvt);
		_propList[2] = 0;//停止能量支持
		Audio::getInstance()->playeffectbykey("victory");
		scheduleOnce(schedule_selector(PlayScene::ShowVictorySceneCallback), 1.5f);
	}
	else
	{
		int spyCount = 0;
		bool isHaveOther = false;
		//查找是否都是间谍
		for (int i = 0; i < DataOfGame::getInstance()->targetsVector.size(); i++)
		{
			target* _enemy = static_cast<target*>(DataOfGame::getInstance()->targetsVector.at(i));
			if (_enemy->getKind() != 7)
			{
				isHaveOther = true;
			}
			else
			{
				spyCount++; 
			}
		}
		if (!isHaveOther&&isGameover!=-1&&
			spyCount == DataOfGame::getInstance()->enemyResidue)
		{
			log("victory");
			isGameover = -1;
			std::string _strvt = *GameStringValue::getStringByKey("jlsydr");//击落所有敌人
			panelLayer->addshade_text(1,_strvt);
			_propList[2] = 0;//停止能量支持
			Audio::getInstance()->playeffectbykey("victory");
			scheduleOnce(schedule_selector(PlayScene::ShowVictorySceneCallback), 1.5f);
		}
		else if (
			isHaveOther&&DataOfGame::getInstance()->_bulletTotle<=0&&
			DataOfGame::getInstance()->enemyResidue>0&&isGameover!=1&&
			combo<7&&_propList[2]<=0
			)
		{
			isGameover = 1;
			_gameoverpoint = *GameStringValue::getStringByKey("ywsypd");//用完所有炮弹
			//panelLayer->addshade_text(0,_strgv);
			_propList[2] = 0;//停止能量支持
			scheduleOnce(schedule_selector(PlayScene::gameOverTimer_ones),2.5f);
		}
	}
	if (DataOfGame::getInstance()->enemyResidue != panelLayer->_enemyprocess->_enemynum)
	{
		panelLayer->_enemyprocess->SetEnemyNum( DataOfGame::getInstance()->enemyResidue,
		DataOfGame::getInstance()->enemyResidue*1.0 / DataOfGame::getInstance()->totleEnemy * 100);
	}
}
void PlayScene::Update(float dt)
{
	DataOfGame::getInstance()->clearRecycle_bin();
	if (!_isTransitionFinished)
	{
		return;
	}
	if (_gameModule == 4)
	{
		gameModule4Update();
	}
	else if (_gameModule == 2)
	{
		gameModule2Update();
	}
	else if (_gameModule == 3)
	{
		gameModule3Update();
	}
	panelLayer->score->updateScoreLabel(DataOfGame::getInstance()->_gameScore +
		DataOfGame::getInstance()->_scorenow);
	/*panelLayer->gold->setGlodNum(DataOfGame::getInstance()->gold);*/
	if(_gameModule!=4)
	panelLayer->_bulletview->SetBulletNum(DataOfGame::getInstance()->_bulletTotle);
	if(combo!= panelLayer->comboPower->getNum())
	{
		panelLayer->comboPower->setNum(combo,100-combo*1.0/7*100);
		if (combo >= 7 )
		{ 
			if(panelLayer->comboPower->getActionByTag(5)==nullptr)
			{ 
				panelLayer->comboPower->runAction(panelLayer->comboPower->createLightAction());
			}
			panelLayer->button_fireSupport->setEnabled(true);
		}
		else
		{ 
			if (panelLayer->comboPower->getActionByTag(5) != nullptr)
			{
				panelLayer->comboPower->stopAction(panelLayer->comboPower->getActionByTag(5));
			}
			panelLayer->comboPower->runAction(panelLayer->comboPower->createNomalAction());
			panelLayer->button_fireSupport->setEnabled(false);
		}	
	}
	changeGameState();
}
void PlayScene::gameModule4Logic()
{
	enemyLayer->GameModule_4AddEnemy();
}
void PlayScene::gameModule2Logic()
{
	enemyLayer->GameModule_2AddEnemy();
}
void PlayScene::gameModule3AddEnemy()
{
	enemyLayer->GameModule_3AddEnemy();
}
void PlayScene::gameLogic(float dt)
{
	if (!_isTransitionFinished || isGameover != 0)
	{
		return;
	}
//	CCLOG("%f",dt);
	if (_gameModule == 4)
	{
		gameModule4Logic();
	}
	else if (_gameModule == 2)
	{
		gameModule2Logic();
	}
	else if (_gameModule == 3)
	{
		gameModule3AddEnemy();
	}
}
void PlayScene::timerByProt(float dt)
{
	if (_propList[2]>0)
	{
		PowerSupport*powerSupport = PowerSupport::getinstance();
		powerSupport->showSupportTime(_powertime,this);
		if (_powertime>0)
		{ 
			_enabletouch = true;
			panelLayer->_bulletview->setlock(true);
			_powertime--;
			Audio::getInstance()->playeffectbykey("time",true);
			if (_powertime == 0)
			{
				_enabletouch = false;
				//TODO:做出提示特效
			}
		}
		else
		{
			_propList[2]=0;
			panelLayer->_bulletview->setlock(false);
			_enabletouch = true;
		}
	}
	else
	{ 
		panelLayer->_bulletview->setlock(false);
	}	
	if (_gameModule == 4)
	{
		 gameTime++;
		 _statetime++;
	}
}

void PlayScene::gameOverTimer_ones(float dt)
{
	if (isGameover != 1)
	{
		return;
	}
	_propList[2] = 0;//停止能量支持
	Audio::getInstance()->playeffectbykey("gameover");
	std::string _strgv = _gameoverpoint;//用完所有炮弹
	panelLayer->addshade_text(0, _strgv);
	unschedule(SEL_SCHEDULE(schedule_selector(PlayScene::gameOverTimer_ones)));
	this->schedule(schedule_selector(PlayScene::pushgameshop),2.0f);
	_enabletouch = false;
	AdviewAd::requestInstl();
}

void PlayScene::ShowVictorySceneCallback(float dt)
{
	panelLayer->removeshade_text();
	if (isGameover == -1)
	{
		victory();
	}
	unschedule(SEL_SCHEDULE(schedule_selector(PlayScene::ShowVictorySceneCallback)));
}

bool PlayScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event*e)
{
	if (!_isTransitionFinished || _isfire == 1)
	{
		return false;
	}
	Vec2 _org = Director::getInstance()->getVisibleOrigin();
	Size _winsize = Director::getInstance()->getWinSize();
	_touchlocation = touch->getLocation();
	Vec2 _point2 = Vec2(_winsize.width / 2, _org.y);

	_isfire = 1;
	//_firetime = 0;
	float _rotate = panelLayer->turret->GetRotate(_touchlocation, _point2);
	panelLayer->turret->Rotate(_rotate, nullptr);
	this->scheduleOnce(schedule_selector(PlayScene::resetfire), 0.2f);
	return _enabletouch;
}
void PlayScene::resetfire(float dt)
{
	_isfire = 0;
}


void PlayScene::onTouchEnded(cocos2d::Touch*touch, cocos2d::Event*touch_event)
{
	if (getTouchIsturret(touch->getLocation()))
	{

		return;
	}
	//log("touch_x=%f,touch_y=%f", touch->getLocation().x, touch->getLocation().y);

	Vec2 Org = Director::getInstance()->getVisibleOrigin();
	Vec2 _local = touch->getLocation();
	if (_local.y < (Org.y + panelLayer->ariship->getContentSize().height))
	{
		return;
	}
	//if (_gameModule!=4)
	//{
		bulletLayer->readyShoot(_local);
	//}
	//_isfire = 0;
	//_firetime = 0;
}
void PlayScene::onTouchMove(cocos2d::Touch*touch, cocos2d::Event*touch_event)
{
	Vec2 _org = Director::getInstance()->getVisibleOrigin();
	Vec2 _local = touch->getLocation();
	if (_local.y < (_org.y + panelLayer->ariship->getContentSize().height))
	{
		//_isfire = 0;
		return;
	}
	Size _winsize = Director::getInstance()->getWinSize();
	Vec2 _point2 = Vec2(_winsize.width / 2, _org.y);
	_touchlocation = touch->getLocation();
	float _rotate = panelLayer->turret->GetRotate(_touchlocation, _point2);
	panelLayer->turret->Rotate(_rotate, nullptr);
}


bool PlayScene::w_onContactBegin(const PhysicsContact& contact)
{
	auto contactA = (Node*)contact.getShapeA()->getBody()->getNode();//经测试一般，这个是被撞物体
	auto contactB = (Node*)contact.getShapeB()->getBody()->getNode();//碰撞物体
	//if (contactA->getName() == "firebomb" || contactB->getName() == "firebomb")
	//{
	//	CCLOG("contacta_tag= %d,contact_tag=%d", contactA->getTag(), contactB->getTag());
	//}
	if (contactA->getTag() == 99 || contactB->getTag() == 99)
	{
		//和边框碰撞
		if (contactA->getTag() == 99)
		{
			//A是边框
			Bullet* _bullet = static_cast<Bullet*>(contactB);
			if (_bullet->getBlood() == _bullet->getCBlood() && 
				_bullet->getID() == 0 &&combo<7)
			{
				panelLayer->resetCombo();
			}
			_bullet->setBlood(0);
			DataOfGame::getInstance()->recycle_bin.pushBack(_bullet);
		}
		else
		{
			//B是边框
			Bullet* _bullet = static_cast<Bullet*>(contactA);
			if (_bullet->getBlood() == _bullet->getCBlood() && 
				_bullet->getID() == 0 &&combo<7)
			{
				panelLayer->resetCombo();
			}
			_bullet->setBlood(0);
			DataOfGame::getInstance()->recycle_bin.pushBack(_bullet);
		}
		
	}
	else
	{
		target* _enemy = nullptr;
		if (contactA->getTag() == 100)
		{
			//A是炮弹，B是敌人
			Bullet* _bullet = static_cast<Bullet*>(contactA);
			 _enemy = static_cast<target*>(contactB);
			ContactDeal::bulletContact(contactB, contactA, this);
			ContactDeal::targetContact(contactB, contactA, this);
		
		}
		else
		{
			//B是炮弹，A是敌人
			Bullet* _bullet = static_cast<Bullet*>(contactB);
			_enemy = static_cast<target*>(contactA);
			ContactDeal::bulletContact(contactA, contactB, this);
			ContactDeal::targetContact(contactA, contactB, this);
		}
	}
	return true;
}

bool PlayScene::w_onContactpreSolve(const PhysicsContact& contact)
{
	return true;
}
void PlayScene::w_onContactPostSolve(const PhysicsContact& contact)
{

}
void PlayScene::w_onContectSeparate(const PhysicsContact& contact)
{
	
}
bool PlayScene::getTouchIsturret(Vec2 point)
{
	Vec2 turretPoint = panelLayer->turret->getPosition();
	turretPoint = Vec2(turretPoint.x - panelLayer->turret->getContentSize().width / 2,
		turretPoint.y - panelLayer->turret->getContentSize().height / 2);
	Rect turrrtRect = Rect(turretPoint, panelLayer->turret->getContentSize());
	if (turrrtRect.containsPoint(point))
	{
		return true;
	}
	return false;
}

void PlayScene::initGameData(int _gameModule)
{
	_enabletouch = true;
	Size winSize = Director::getInstance()->getWinSize();
	bgLayer = BgLayer::create(ImgPath::path_mainUi.c_str());
	bgLayer->setAnchorPoint(Vec2(0.5f, 0.5f));
	bgLayer->setName("bgLayer");
	this->addChild(bgLayer, 1);

	panelLayer = PanelLayer::create();
	panelLayer->setAnchorPoint(Vec2(0.5f, 0.5f));
	panelLayer->setPosition(DataOfGame::getInstance()->getrealposition(Vec2(winSize.width / 2, winSize.height / 2)));
	panelLayer->setPosition(DataOfGame::getInstance()->getrealposition(panelLayer->getPosition()));
	this->addChild(panelLayer,5);
	panelLayer->setName("panelLayer");
	panelLayer->addAllToLayer();

	enemyLayer = EnemyLayer::create();
	enemyLayer->setAnchorPoint(Vec2(0.5f, 0.5f));
	enemyLayer->setPosition(DataOfGame::getInstance()->getrealposition(Vec2(winSize.width / 2, winSize.height / 2)));
	enemyLayer->setName("enemyLayer");
	this->addChild(enemyLayer, 2);

	bulletLayer = BulletLayer::create();
	bulletLayer->setAnchorPoint(Vec2(0.5f, 0.5f));
	bulletLayer->setPosition(DataOfGame::getInstance()->getrealposition(Vec2(winSize.width / 2, winSize.height / 2)));
	bulletLayer->setName("bulletLayer");
	this->addChild(bulletLayer, 3);
	DataOfGame::getInstance()->_scorenow = 0;//置0
	//DataOfGame::getInstance()->setm2new(true);
	//DataOfGame::getInstance()->setm3new(true);
	//DataOfGame::getInstance()->setm4new(true);
	if (_gameModule == 2)
	{
		_addEnemyTimer = 1.0f;
		//读取做高分
		DataOfGame::getInstance()->_gameModule2HeihtScore = 
		DataOfGame::getInstance()->getGameModule2HeihtScore();
		Audio::getInstance()->playbmgbykey("gamemodule2bgm");
		int _m2new = DataOfGame::getInstance()->getm2new();
		if(_m2new)
		{ 
			panelLayer->showcourse(_gameModule);
			DataOfGame::getInstance()->setm2new(false);
		}
	}
	else if (_gameModule == 3)
	{
		DataOfGame::getInstance()->setround(38);
		DataOfGame::getInstance()->_bulletTotle = 0;
		_addEnemyTimer = 0.7f;
		_gameState = 0;
		DataOfGame::getInstance()->enemyOnScene = 0;
		Audio::getInstance()->playbmgbykey("gamemodule3bgm");
		if (DataOfGame::getInstance()->getround() <= 0)
		{
			DataOfGame::getInstance()->setround(1);
		}
		DataOfGame::getInstance()->Load_RoundData(DataOfGame::getInstance()->getround());
		DataOfGame::getInstance()->_gameModule3HeihtScore =
		DataOfGame::getInstance()->getGameModule3HeihtScore();
		int _m3new = DataOfGame::getInstance()->getm3new();
		if (_m3new)
		{
			panelLayer->showcourse(_gameModule);
			DataOfGame::getInstance()->setm3new(false);
		}
		else
		{
			panelLayer->showrount(DataOfGame::getInstance()->getround());
		}
	}
	else if (_gameModule == 4)
	{
		_addEnemyTimer = 0.3f;
		_omitEnemy = 0;
		_nexttime = 0;
		_statetime = 0;
		_module4dp = 0;
		_grads = 1;
		DataOfGame::getInstance()->totleEnemy = 10;
		Audio::getInstance()->playbmgbykey("gamemodule4bgm");
		DataOfGame::getInstance()->_gameModule4HeihtScore =
		DataOfGame::getInstance()->getGameModule4HeihtScore();
		_killspy = 0;
		int _m4new = DataOfGame::getInstance()->getm4new();
		if (_m4new)
		{
			panelLayer->showcourse(_gameModule);
			DataOfGame::getInstance()->setm4new(false);
		}
	}

	DataOfGame::getInstance()->targetsVector.clear();
	DataOfGame::getInstance()->_gameScore = 0; 
	DataOfGame::getInstance()->getGold();
	DataOfGame::getInstance()->multiplying_power = 1;
	combo = 0;
	panelLayer->resetComboing = 0;
	//isGameover = 0;
	gameOverTimer = 0;
	gameTime = 0;
	_propId = -1;
	_propList[0] = 0;
	_propList[1] = 0;
	_propList[2] = 0;
	_powertime = 0;
	_isfire = -1;
	_username = " ";
	_gameoverpoint = "I don`t know";
	//获取用户名
	_username = DataOfGame::getInstance()->getUsername();
	//操作处理
	auto listener = EventListenerTouchOneByOne::create();
	//listener->setSwallowTouches(true);
	listener->setEnabled(true);
	listener->onTouchBegan = CC_CALLBACK_2(PlayScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(PlayScene::onTouchEnded, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlayScene::onTouchMove, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	this->schedule(schedule_selector(PlayScene::Update), 1 / 60.0f, kRepeatForever, 0);
	this->schedule(schedule_selector(PlayScene::gameLogic), _addEnemyTimer, kRepeatForever, 0);
	this->schedule(schedule_selector(PlayScene::timerByProt), 1.0f, kRepeatForever, 0);
	this->schedule(schedule_selector(PlayScene::timer_05),0.3f, kRepeatForever, 0);
	//各种纹理的加载
}
void PlayScene::Replay()
{
	for (int i = 0; i < DataOfGame::getInstance()->targetsVector.size(); ++i)
	{
		DataOfGame::getInstance()->recycle_bin.pushBack(DataOfGame::getInstance()->targetsVector.at(i));
	}
	TargetMaker::getinstance()->loadenemytexture();
	DataOfGame::getInstance()->targetsVector.clear();
	DataOfGame::getInstance()->bulletsVector.clear();
	DataOfGame::getInstance()->_scorenow = 0;
	isGameover = 1;
	_isfire = -1;
	_enabletouch = true;
	GameShop* _gameshop = GameShop::create();
	_gameState = 0;
	_gameshop->setName("gameshop");
	switch (_gameModule)
	{
		case 2:
		{
			DataOfGame::getInstance()->_bulletTotle = 35;
			_gameshop->setattribute(&DataOfGame::getInstance()->_bulletTotle);
			_gameshop->_buycallback = std::bind(&PlayScene::buycallback, this);
			_gameshop->_exitcallback = _gameshop->_buycallback;
			_gameshop->bulletshop(_gameModule);
			_gameshop->setPosition(panelLayer->getmidPos());
			panelLayer->addChild(_gameshop);
		}break;
		case 3:
		{
		//	DataOfGame::getInstance()->setround(26);
			DataOfGame::getInstance()->totleEnemy = 0;
			DataOfGame::getInstance()->enemyResidue = 0;
			DataOfGame::getInstance()->enemyOnScene = 0;
			_propList[0] = 0;
			_propList[1] = 0;
			_propList[2] = 0;
			panelLayer->resetComboing = 0;
			combo = 0;
			panelLayer->showrount(DataOfGame::getInstance()->getround());
			DataOfGame::getInstance()->Load_RoundData(DataOfGame::getInstance()->getround());
			//isGameover = 0;
			/*_gameshop->setattribute(&DataOfGame::getInstance()->_bulletTotle);
			_gameshop->_buycallback = std::bind(&PlayScene::buycallback, this);
			_gameshop->_exitcallback = _gameshop->_buycallback;
			_gameshop->bulletshop(_gameModule);
			_gameshop->setPosition(DataOfGame::getInstance()->LayerGetRealPosition(-540, -360));
			panelLayer->addChild(_gameshop);*/
		}break;
		case 4:
		{
			//GameShop* _gameshop = GameShop::create();
			DataOfGame::getInstance()->_missnum = 2;
			_nexttime = 0;
			_statetime = 0;
			_module4dp = 0;
			_grads = 1;
			_gameshop->setattributeicon("shoplayer/missicon.png");
			_gameshop->setattribute(&DataOfGame::getInstance()->_missnum);
			_gameshop->setattributename(GameStringValue::getStringByKey("shiwugeshu")->c_str());
			_gameshop->_buycallback = std::bind(&PlayScene::buycallback, this);
			_gameshop->_exitcallback = _gameshop->_buycallback;
			_gameshop->bulletshop(_gameModule);
			_gameshop->setPosition(panelLayer->getmidPos());
			panelLayer->addChild(_gameshop);
		}break;
		default:
			break;
	}
}
void PlayScene::GameOverShop()
{
	_propList[2] = 0;//停止能量支持
	GameShop* _gameshop = GameShop::create();
	_gameshop->setName("gameshop");
	_gameshop->setpsstring(GameStringValue::getStringByKey("gameoverps")->c_str());
	if (_gameModule == 2)
	{
		for (int i = 0; i < DataOfGame::getInstance()->targetsVector.size(); ++i)
		{
			DataOfGame::getInstance()->recycle_bin.pushBack(DataOfGame::getInstance()->targetsVector.at(i));
		}
		DataOfGame::getInstance()->targetsVector.clear();
		_gameshop->setattribute(&DataOfGame::getInstance()->_bulletTotle);
		_gameshop->_buycallback = std::bind(&PlayScene::gameoverbuy, this);
		_gameshop->_exitcallback = std::bind(&PlayScene::buynotthing, this);;
		_gameshop->bulletshop(_gameModule);
		_gameshop->setPosition(panelLayer->getmidPos());
		panelLayer->addChild(_gameshop);
	}
	else if (_gameModule==3)
	{
		/*_gameshop->setattribute(&DataOfGame::getInstance()->_bulletTotle);
		_gameshop->_buycallback = std::bind(&PlayScene::gameoverbuy, this);
		_gameshop->_exitcallback = std::bind(&PlayScene::buynotthing, this);
		_gameshop->bulletshop(_gameModule);
		_gameshop->setPosition(panelLayer->getmidPos());
		panelLayer->addChild(_gameshop);*/
		GameOver();
	}
	else if (_gameModule==4)
	{
		for (int i = 0; i < DataOfGame::getInstance()->targetsVector.size(); ++i)
		{
			DataOfGame::getInstance()->recycle_bin.pushBack(DataOfGame::getInstance()->targetsVector.at(i));
		}
		DataOfGame::getInstance()->targetsVector.clear();
		DataOfGame::getInstance()->_missnum=0;
		_gameshop->setattributeicon("shoplayer/missicon.png");
		_gameshop->setattribute(&DataOfGame::getInstance()->_missnum);
		_gameshop->setattributename(GameStringValue::getStringByKey("shiwugeshu")->c_str());
		_gameshop->_buycallback = std::bind(&PlayScene::gameoverbuy, this);
		_gameshop->_exitcallback = std::bind(&PlayScene::buynotthing, this);
		_gameshop->bulletshop(_gameModule);
		_gameshop->setPosition(panelLayer->getmidPos());
		panelLayer->addChild(_gameshop);
	}
}
void PlayScene::addmiss()
{
	this->_omitEnemy++;
	if (_omitEnemy < DataOfGame::getInstance()->_missnum)
	{
		Audio::getInstance()->playeffectbykey("gameover");
	}
}
void PlayScene::w_onEnter()
{
	Size designSize = Director::getInstance()->getWinSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size ResourcesSzie = Size(400,400);
	auto body = PhysicsBody::createEdgeBox(Size(visibleSize.width+ResourcesSzie.width, 
		visibleSize.height+ResourcesSzie.height), PHYSICSBODY_MATERIAL_DEFAULT, 3);
	body->getShape(0)->setFriction(0.0f);
	body->getShape(0)->setRestitution(1.0f);
	body->setCategoryBitmask(BOX_MASK);
	body->setContactTestBitmask(BOX_CATE_MASK);
	body->setCollisionBitmask(BOX_COLL_MASK);
	edgeShpe = Sprite::create();
	edgeShpe->setPhysicsBody(body);
	edgeShpe->setPosition(DataOfGame::getInstance()->getrealposition(Vec2(designSize.width / 2, designSize.height / 2)));
	edgeShpe->setTag(99);
	addChild(edgeShpe);
	/*
	*物理世界碰撞监听
	*/
	Layer::onEnter();
	auto contacLister = EventListenerPhysicsContact::create();
	contacLister->onContactBegin = CC_CALLBACK_1(PlayScene::w_onContactBegin, this);
	contacLister->onContactPreSolve = CC_CALLBACK_1(PlayScene::w_onContactpreSolve,this);
	contacLister->onContactPostSolve = CC_CALLBACK_1(PlayScene::w_onContactPostSolve,this);
	contacLister->onContactSeparate = CC_CALLBACK_1(PlayScene::w_onContectSeparate,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contacLister, this);
}
void PlayScene::victory()
{
	panelLayer->resetCombo();
	_propList[2] = 0;
	VictoryLayer* victoryLayer = VictoryLayer::create();
	victoryLayer->setPosition(0, 0);
	this->addChild(victoryLayer, 5);
	victoryLayer->accountScore(DataOfGame::getInstance()->_gameScore + DataOfGame::getInstance()->_scorenow);
	victoryLayer->accountBullet(DataOfGame::getInstance()->_bulletTotle,
		DataOfGame::getInstance()->_scorenow);
}
void PlayScene::GameOver()
{
	if (isGameover != 1)
	{
		return;
	}
	GameOverLayer* gameoverLayer = GameOverLayer::create();
	gameoverLayer->setPosition(Vec2(0, 0));
	this->addChild(gameoverLayer, 5);
	//gameoverLayer->accountScore();
	_propList[2] = 0;//Õ£÷πƒ‹¡ø÷ß≥÷
	gameoverLayer->loadui();
	if (_gameModule == 2 || _gameModule == 4)
	{
		//gameoverLayer->module2_4init();
		gameoverLayer->accountScore();
		gameoverLayer->accoutHeightScore();
	}
	else
	{
		// gameoverLayer->module3init();
		gameoverLayer->accountScore();
		gameoverLayer->scoreAccountLayer->setPosition(0, 0);//
	}

	DataOfGame::getInstance()->clearvector(DataOfGame::getInstance()->bulletsVector);
	DataOfGame::getInstance()->clearvector(DataOfGame::getInstance()->targetsVector);
	_touchEnabled = true;
}
void PlayScene::buycallback()
{
	if (_gameModule == 2)
	{
		//DataOfGame::getInstance()->_bulletTotle = 35;
		DataOfGame::getInstance()->_gameScore = 0;
		panelLayer->resetComboing = 0;

	}
	else if (_gameModule == 3)
	{

		//isGameover = 0;
	}
	else if (_gameModule == 4)
	{
		_omitEnemy = 0;
		panelLayer->loadmissicon(panelLayer->_nodemiss);
		//isGameover = 0;
	}
	GameShop* _gameshop = static_cast<GameShop*>(panelLayer->getChildByName("gameshop"));
	if (_gameshop)
	{
		_gameshop->removeFromParentAndCleanup(true);
	}
	isGameover = 0;
}
void PlayScene::gameoverbuy()
{
	if (_gameModule == 2)
	{
		
	}
	else if (_gameModule == 3)
	{

	}
	else if (_gameModule == 4)
	{
		_omitEnemy = 0;
		panelLayer->loadmissicon(panelLayer->_nodemiss);
	}
	GameShop* _gameshop =static_cast<GameShop*>( panelLayer->getChildByName("gameshop"));
	_gameshop->removeFromParentAndCleanup(true);
	isGameover = 0;
}
void PlayScene::buynotthing()
{
	GameShop* _gameshop = static_cast<GameShop*>(panelLayer->getChildByName("gameshop"));
	_gameshop->removeFromParentAndCleanup(true);
	isGameover = 1;
	if (_gameModule == 3)
	{
		panelLayer->resetCombo();//重置combo
		DataOfGame::getInstance()->_bulletTotle = 0;
		enemyLayer->enemyResidue = enemyLayer->targetTotle = 0;
	}
	else if (_gameModule == 2)
	{
		panelLayer->resetCombo();//重置combo
	}
	else if (_gameModule == 4)
	{
		panelLayer->resetCombo();//重置combo
	}
		GameOver();
}
void PlayScene::pushgameshop(float dt)
{
	panelLayer->removeshade_text();
	if (isGameover != 1)
	{
		return;
	}
	GameOverShop();
	unschedule(SEL_SCHEDULE(schedule_selector(PlayScene::pushgameshop)));
}
void PlayScene::timer_05(float dt)
{
	if (isGameover==0 && _gameModule==4)
	{
		//bulletLayer->readyShoot(_touchlocation);
		//_firetime = 0;
	}
	//else if(_gameModule == 4 && _firetime < 5)
	//{
	//	_firetime = ++_firetime;
	//}
}
