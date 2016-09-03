#include "RepairEnemy.h"


RepairEnemy::RepairEnemy()
{
}


RepairEnemy::~RepairEnemy()
{
}

RepairEnemy* RepairEnemy::create()
{
	RepairEnemy* repairEnemy = new RepairEnemy();
	repairEnemy->initWithSpriteFrameName("enemytexture/repairenemy/repairenemy_1.png");
	repairEnemy->setId(0);
	repairEnemy->setKind(8);
	repairEnemy->setBlood(3,true);
	repairEnemy->_oldBlood = repairEnemy->getBlood();
	repairEnemy->setVelocity(120);
	repairEnemy->setRotation(0);
	repairEnemy->setHaveScore(300);
	repairEnemy->setHitScore(100);
	auto animation = Animation::create();
	animation->addSpriteFrame(SpriteFrameCache::getInstance()
		->getSpriteFrameByName("enemytexture/repairenemy/repairenemy_1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()
		->getSpriteFrameByName("enemytexture/repairenemy/repairenemy_2.png"));
	animation->setDelayPerUnit(1.0f / 24.0f);
	animation->setRestoreOriginalFrame(true);
	repairEnemy->_runingAction = Animate::create(animation);
	repairEnemy->_repairTime = 3.0f;
	repairEnemy->runAction(RepeatForever::create(repairEnemy->_runingAction));
	repairEnemy->schedule(schedule_selector(RepairEnemy::RepairTimer),repairEnemy->_repairTime,kRepeatForever,0);
	return repairEnemy;
}
void RepairEnemy::setBlood(int val,bool isAddCombo)
{
	if (val>0&&val<this->_blood)
	{
		int score = abs(val - _blood)*this->getHitScore();
		if(getHaveScore()>score)
		this->setHaveScore(getHaveScore() - score);
		else
		{
			this->setHaveScore(0);
			score = getHaveScore();
		}
		GameUi::score->addScoreOnScene(score, this->getParent(), this->getPosition());
		this->_blood = val;//扣血
		Audio::getInstance()->playeffectbykey("enemyhit");
	}
	else if (val <= 0)
	{
		this->_blood = 0;//死亡
		GameUi::score->addScoreOnScene(this->getHaveScore()*DataOfGame::getInstance()->multiplying_power,
		this->getParent(), this->getPosition());
		//if (isAddCombo)
		//{
		//	PanelLayer* panelLayer = getPanelLayer();
		//	panelLayer->addCombo(1, this->getParent());
		//}
		DataOfGame::getInstance()->enemyResidue -= 1;
		DataOfGame::getInstance()->enemyOnScene -= 1;
		bombAnimation();
	}
	else
	{
		this->_blood = val;//初始化
	}
}

void RepairEnemy::bombAnimation()
{
	//TODO:this->getparent有时候获取到的是空，发生异常
	//if (this->getParent() == nullptr)
	//{
	//	log("bombAnimation getParent==nullptr");
	//	return;
	//}

	//auto animation = Animation::create();
	//for (int i = 0; i < ImgPath::path_meterTarget_Bomb_Animation.size(); ++i)
	//{
	//	animation->addSpriteFrameWithFile(ImgPath::path_meterTarget_Bomb_Animation.at(i));
	//}
	//animation->setDelayPerUnit(1.0f / 24);
	//animation->setRestoreOriginalFrame(false);
	//Sprite* sprite_ani = Sprite::create();
	//sprite_ani->setAnchorPoint(Vec2(0.5f, 0.5f));
	//sprite_ani->setPosition(this->getPosition());

	//this->getParent()->addChild(sprite_ani, 2);
	//auto action = Animate::create(animation);
	//this->stopAllActions();
	//CCCallFuncN*callback = CCCallFuncN::create([](Ref*sender) {
	//	RepairEnemy* repairEnemy = static_cast<RepairEnemy*>(sender);
	//	DataOfGame::getInstance()->recycle_bin.pushBack(repairEnemy);
	//});
	//sprite_ani->runAction(Sequence::create(action, action->reverse(), callback, nullptr));
	BombParticle* _explosion = BombParticle::create("particle/particle_bomb7.plist");
	_explosion->setPosition(this->getPosition());
	this->getParent()->addChild(_explosion);
	Audio::getInstance()->playeffectbykey("smallenemybomb");
	//this->stopAllActions();
	DataOfGame::getInstance()->recycle_bin.pushBack(this);
}

void RepairEnemy::RepairTimer(float dt)
{
	if (getBlood()<_oldBlood)
	{
		Sprite* addLogo = Sprite::create("target/addbloodlogo.png");
		addLogo->setPosition(this->getContentSize().width,this->getContentSize().height);
		this->addChild(addLogo);
		ScaleTo* scaleBig = ScaleTo::create(0.8f,2.0f);
		CallFuncN* scaleDone = CallFuncN::create(CC_CALLBACK_1(RepairEnemy::Repair,this));
		addLogo->runAction(Sequence::create(scaleBig,scaleDone,nullptr));
	}
}

void RepairEnemy::Repair(Ref*sender)
{
	Sprite* addLogo = static_cast<Sprite*>(sender);
	addLogo->removeFromParent();
	setBlood(getBlood()+1,true);
}
