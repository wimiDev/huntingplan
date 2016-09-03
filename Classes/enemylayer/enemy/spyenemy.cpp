#include "spyenemy.h"

SpyEnemy::SpyEnemy()
{
	
	this->_blood = 0;
}

SpyEnemy::~SpyEnemy()
{

}

SpyEnemy * SpyEnemy::create()
{
	SpyEnemy* spyEnemy = new SpyEnemy();
	spyEnemy->initWithSpriteFrame(SpriteFrameCache::getInstance()
		->getSpriteFrameByName("enemytexture/spyenemy/spyenemy_1.png"));
	spyEnemy->spyLogo = Sprite::create("target/notkill.png");
	ScaleTo* scaleBig = ScaleTo::create(0.5f,2.0f);
	ScaleTo* scaleNomal = ScaleTo::create(0.5f,1.0f);
	FadeIn* _fadein = FadeIn::create(0.3f);
	FadeOut* _fadeout = FadeOut::create(0.5f);
	spyEnemy->spyLogo->runAction(RepeatForever::create(Sequence::create(_fadein,_fadeout,nullptr)));
	spyEnemy->spyLogo->setPosition(spyEnemy->getContentSize().width/2,spyEnemy->getContentSize().height/2);
	spyEnemy->addChild(spyEnemy->spyLogo);
	spyEnemy->setId(0);
	spyEnemy->setKind(7);
	spyEnemy->setHaveScore(0);
	spyEnemy->setKillScore(0);
	spyEnemy->setHitScore(0);
	spyEnemy->setVelocity(220.0);
	spyEnemy->setBlood(3);
	spyEnemy->followTime = 1.0f;
	auto animation = Animation::create();
	animation->addSpriteFrame(SpriteFrameCache::getInstance()
		->getSpriteFrameByName("enemytexture/spyenemy/spyenemy_1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()
		->getSpriteFrameByName("enemytexture/spyenemy/spyenemy_2.png"));
	animation->setDelayPerUnit(1.0f / 24.0f);
	animation->setRestoreOriginalFrame(true);
	spyEnemy->_runingAction = Animate::create(animation);
	spyEnemy->runAction(RepeatForever::create(spyEnemy->_runingAction));
	//spyEnemy->schedule(schedule_selector(SpyEnemy::followEnemy),3.0f,kRepeatForever, 0);
	return spyEnemy;
}

void SpyEnemy::setBlood(int val,bool addcombo)
{
	if (val < _blood && val>0)
	{
		//*血量减少
		Audio::getInstance()->playeffectbykey("enemyhit");
		_blood = val;
	}
	else if (val <= 0)
	{
		//*被击毁
		DataOfGame::getInstance()->enemyResidue -= 1;
		DataOfGame::getInstance()->enemyOnScene -= 1;
		_blood = 0;
		bombAnimation();
	}
	else
	{ 
		this->_blood = val;
	}
}

int SpyEnemy::getBlood()
{
	return this->_blood;
}

void SpyEnemy::bombAnimation()
{
	BombParticle* _explosion = BombParticle::create("particle/particle_bomb8.plist");
	_explosion->setPosition(this->getPosition());
	this->getParent()->addChild(_explosion);
	Audio::getInstance()->playeffectbykey("smallenemybomb");
	this->stopAllActions();
	createEnemy(5);
	//this->removeFromParentAndCleanup(true);
	DataOfGame::getInstance()->recycle_bin.pushBack(this);
}

void SpyEnemy::createEnemy(int num)
{
	//*生成5个敌人
	//TODO:位置不对，设置位置无效
	DataOfGame::getInstance()->totleEnemy += num;
	DataOfGame::getInstance()->enemyResidue += num;
	DataOfGame::getInstance()->enemyOnScene += num;
	EnemyLayer* _enemylayer =static_cast<EnemyLayer*>(this->getParent());
	_enemylayer->killspy();
	_enemylayer->addbitenemy(1, num, this->getDirection(), this->getPosition());
}

void SpyEnemy::boomCallback(Ref * sender)
{
	Sprite* spyEnemy = static_cast<Sprite*>(sender);
	//createEnemy(5);
	//DataOfGame::getInstance()->recycle_bin.pushBack(spyEnemy);
}

void SpyEnemy::followEnemy(float dt)
{
	//int mini = 0;
	//int max = DataOfGame::getInstance()->targetsVector.size()-1;
	//int kind = 0;
	//int randCount = 0;
	//while (randCount < 10)
	//{
	//	if (mini >= max)
	//		break;
	//	kind = random(mini,max);
	//	target* enemy = static_cast<target*>(DataOfGame::getInstance()->targetsVector.at(kind));
	//	if (enemy->getKind() != 7)
	//	{
	//		this->setTexture(enemy->getTexture());
	//		break;
	//	}
	//	randCount++;
	//}
}
