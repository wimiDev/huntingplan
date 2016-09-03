#include "PropTarget.h"

PropTarget::PropTarget()
{
}
PropTarget::~PropTarget()
{
}
PropTarget* PropTarget::create(const char path[50])
{
	PropTarget*sprite = new PropTarget();
	sprite->initWithSpriteFrameName("enemytexture/propenemy/propenemy_1.png");
	auto animation = Animation::create();
	animation->addSpriteFrame(SpriteFrameCache::getInstance()
		->getSpriteFrameByName("enemytexture/propenemy/propenemy_1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()
		->getSpriteFrameByName("enemytexture/propenemy/propenemy_2.png"));
	animation->setDelayPerUnit(1.0f / 14.0f);
	animation->setRestoreOriginalFrame(true);
	sprite->_runingAction = Animate::create(animation);
	sprite->runAction(RepeatForever::create(sprite->_runingAction));
	return sprite;
}
PropTarget* PropTarget::create(const char path[50], int id, int kind, int blood, float velocity)
{
	PropTarget*sprite = new PropTarget();
	sprite->initWithSpriteFrameName("enemytexture/propenemy/propenemy_1.png");
	sprite->setId(id);
	sprite->setKind(kind);
	sprite->setBlood(blood,false);
	sprite->setVelocity(velocity);
	auto animation = Animation::create();
	animation->addSpriteFrame(SpriteFrameCache::getInstance()
		->getSpriteFrameByName("enemytexture/propenemy/propenemy_1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()
		->getSpriteFrameByName("enemytexture/propenemy/propenemy_2.png"));
	animation->setDelayPerUnit(1.0f / 5.0f);
	animation->setRestoreOriginalFrame(true);
	sprite->_runingAction = Animate::create(animation);
	sprite->runAction(RepeatForever::create(sprite->_runingAction));
	return sprite;
}
void PropTarget::bombAnimation()
{
	//分数计算
	Audio::getInstance()->playeffectbykey("samllenemybomb");
	BombParticle* _explosion = BombParticle::create("particle/particle_bomb3.plist");
	_explosion->setPosition(this->getPosition());
	this->getParent()->addChild(_explosion);
	Audio::getInstance()->playeffectbykey("smallenemybomb",true);
	this->stopAllActions();
	randProp(this);
	DataOfGame::getInstance()->recycle_bin.pushBack(this);
}

void PropTarget::setBlood(int blood, bool isAddCombo)
{
	if (blood < this->_blood&&blood > 0)
	{
		//计算伤害值
		int score = abs(blood - _blood)*this->getHitScore();
		this->setHaveScore(getHaveScore()-score);
		GameUi::score->addScoreOnScene(score, this->getParent(), this->getPosition());
		Audio::getInstance()->playeffectbykey("enemyhit");
		this->_blood = blood;
	}
	else if (blood <= 0)
	{
		//击杀处理，添加道具
		this->_blood =blood;
		GameUi::score->addScoreOnScene(this->getHaveScore()*DataOfGame::getInstance()->multiplying_power, 
			this->getParent(), this->getPosition());
		DataOfGame::getInstance()->enemyResidue -= 1;
		DataOfGame::getInstance()->enemyOnScene -= 1;
		bombAnimation();
	}
	else
	{
		this->_blood = blood;
	}
}
void PropTarget::randProp(Ref*sender)
{
	EnemyLayer* enemyLayer = static_cast<EnemyLayer*>(this->getParent());
	PlayScene* playScene = static_cast<PlayScene*>(enemyLayer->getParent());
	PropTarget* amtionSprite = static_cast<PropTarget*>(sender);
	if (playScene->_gameModule == 2)
	{
		playScene->_propId = random(1, 3);
	}
	else
	{
		playScene->_propId = random(0, 3);
	}
	//Audio::getInstance()->playeffectbykey("smallenmeybomb");
	AddpropAction(playScene->_propId, amtionSprite->getParent());
	DataOfGame::getInstance()->recycle_bin.pushBack(amtionSprite);
}
void PropTarget::AddpropAction(int propId,Node*scene)
{
	// 道具弹出
	Node* _nodeprop = CSLoader::createNode("propitem/nodeprop.csb");
	_nodeprop->setPosition(this->getPosition());
	scene->addChild(_nodeprop);
	Sprite* _propbg = static_cast<Sprite*>(DataOfGame::getInstance()->seekNodebyName(_nodeprop,"sprite_bg"));
	ui::Text* _textnum= static_cast<ui::Text*>(DataOfGame::getInstance()->seekNodebyName(_nodeprop, "text_num"));
	//log("%d",propId);
	switch (propId)
	{
	case 0:
	{
		//金币
		_propbg->setTexture("propitem/prop_2.png");
		_textnum->setString("10");
	}
	break;
	case 1:
	{
		//增加普通炮弹
		_propbg->setTexture("propitem/prop_1.png");
		_textnum->setString("2");
		//num_label->setString("2");
	}
	break;
	case 2:
	{
		//num_label->setString("1");
		_propbg->setTexture("propitem/prop_3.png");
		_textnum->setString("1");
	}
	break;
	case 3:
	{
		//num_label->setString("1");
		_propbg->setTexture("propitem/prop_4.png");
		_textnum->setString("1");
	}
	break;
	default:
		break;
	}
	auto scaleto = ScaleTo::create(0.3f, 1.0f);
	auto delay = DelayTime::create(1.0f);
	PanelLayer* panelLayer = static_cast<PanelLayer*>(this->getParent()->getParent()->getChildByName("panelLayer"));
	auto moveTo = MoveTo::create(abs(panelLayer->turret->getPosition().y - _propbg->getPosition().y) / 1000,
		Vec2(ConverPoint(panelLayer->ariship->getPosition().x, panelLayer->ariship->getPosition().y)));
	CCCallFuncN* callback = CCCallFuncN::create(CC_CALLBACK_1(PropTarget::propSpriteMovefinish,this));
	_nodeprop->runAction(Sequence::create(scaleto, delay, moveTo, callback, nullptr));
	Audio::getInstance()->playeffectbykey("propappear",true);
}
void PropTarget::propSpriteMovefinish(Ref*sender)
{
		Node* propBg = static_cast<Node*>(sender);
		EnemyLayer* enemyLayer = static_cast<EnemyLayer*>(propBg->getParent());
		PlayScene* playScene = static_cast<PlayScene*>(enemyLayer->getParent());
		AddProp(playScene->_propId,propBg->getParent()->getParent());
		Audio::getInstance()->playeffectbykey("getprop",true);
		DataOfGame::getInstance()->recycle_bin.pushBack(propBg);
}
void PropTarget::AddProp(int propId,Node*scene)
{
	PlayScene* playScene = static_cast<PlayScene*>(scene);
	PanelLayer* _panellayer = static_cast<PanelLayer*>(playScene->getChildByName("panelLayer"));
	switch (propId)
	{
	case 0:
	{
		//金币
		DataOfGame::getInstance()->setGold(DataOfGame::getInstance()->getGold()+10);
		_panellayer->gold->showGold(DataOfGame::getInstance()->getGold());
	}
	break;
	case 1:
	{
		//增加普通炮弹
		DataOfGame::getInstance()->_bulletTotle += 2;
	}
	break;
	case 2:
	{
		//能量奖励
		PowerSupport* powerSupport = new PowerSupport();
		powerSupport->setCount(1);
		powerSupport->setsupportTime(10);
		powerSupport->startSupport(playScene);

		playScene->_propList[2]=1;
		playScene->_powertime = 10;
		//playScene->panelLayer->meterbulletView->setigSprite(1);
		//playScene->panelLayer->meterbulletView->setisUse(true);
	}
	break;
	case 3:
	{
		//地面火力支援
		FireSupport*fireSupport = new FireSupport();
		fireSupport->setKindId(5);
		fireSupport->OpenFireSupport(scene);
	}
	break;
	default:
	{

	}
		break;
	}
}