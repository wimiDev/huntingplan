#include"TimidTarget.h"

TimidTarget::TimidTarget()
{

}

TimidTarget::~TimidTarget()
{

}
TimidTarget* TimidTarget::create(const char path[50])
{
	TimidTarget* timidTarget = new TimidTarget();
	timidTarget->initWithFile(path);
	return timidTarget;
}
TimidTarget* TimidTarget::create(const char path[50], int id, int kind, int blood, float velocity)
{
	TimidTarget* timidTarget = new TimidTarget();
	timidTarget->initWithSpriteFrameName("enemytexture/timidenemy/timidenemy_1.png");
	timidTarget->setId(id);
	timidTarget->setKind(kind);
	timidTarget->setBlood(blood,true);
	timidTarget->setVelocity(velocity);
	timidTarget->setHaveScore(300);
	timidTarget->setHitScore(150);
	timidTarget->setKillScore(300);
	auto animation = Animation::create();
	animation->addSpriteFrame(SpriteFrameCache::getInstance()
		->getSpriteFrameByName("enemytexture/timidenemy/timidenemy_1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()
		->getSpriteFrameByName("enemytexture/timidenemy/timidenemy_2.png"));
	animation->setDelayPerUnit(1.0f / 24.0f);
	animation->setRestoreOriginalFrame(true);
	timidTarget->_runingAction = Animate::create(animation);
	timidTarget->runAction(RepeatForever::create(timidTarget->_runingAction));
	return timidTarget;
}
void TimidTarget::setBlood(int _blood,bool isAddCombo)
{
	if (_blood != 0&&_blood<this->_blood)
	{
		this->_blood=_blood;
		Audio::getInstance()->playeffectbykey("enemyhit");
		this->moveFast();
	}
	else if (_blood <= 0)
	{
		this->_blood = 0;
		GameUi::score->addScoreOnScene(this->getKillScore()*DataOfGame::getInstance()->multiplying_power,this->getParent(),this->getPosition());//分数计算
		//if (isAddCombo)
		//	DataOfGame::getInstance()->addCombo(1,this->getParent());
		DataOfGame::getInstance()->enemyResidue -= 1;
		DataOfGame::getInstance()->enemyOnScene -= 1;
		//爆炸动画
		this->bombAnimation();
	}
	else
	{
		this->_blood = _blood;
	}
}
void TimidTarget::bombAnimation()
{
	BombParticle* _explosion = BombParticle::create("particle/particle_bomb6.plist");
	_explosion->setPosition(this->getPosition());
	this->getParent()->addChild(_explosion);
	Audio::getInstance()->playeffectbykey("smallenemybomb");
	//this->stopAllActions();
	DataOfGame::getInstance()->recycle_bin.pushBack(this);//移除
}
void TimidTarget::moveFast()
{
	float p_X = Director::getInstance()->getVisibleSize().width/2+ Director::getInstance()->getVisibleOrigin().x;
	if (this->getDirection() == 0)
	{
		p_X = -Director::getInstance()->getVisibleSize().width / 2- Director::getInstance()->getVisibleOrigin().x;
	}
	float p_Y = this->getPosition().y;
	float time = abs(this->getPosition().x-p_X)/(this->getVelocity()*3);
	auto moveFast = EaseSineIn::create(MoveTo::create(time,DataOfGame::getInstance()->getrealposition(Vec2(p_X,p_Y))));
	RotateTo* rotate = RotateTo::create(time, getRotate(Vec2(p_X, p_Y)));
	this->stopActionByTag(_ENEMYRUN_TAG_);
	CCCallFuncN* movefinish = CCCallFuncN::create(CC_CALLBACK_1(TimidTarget::moveFinish,this));
	//CCLOG("timid p_X=%.1f,p_Y=%0.1f,",p_X,p_Y);
	this->runAction(Sequence::create(Spawn::create(moveFast,rotate,nullptr),movefinish,nullptr));
}

void TimidTarget::moveFinish(Ref * sender)
{
	TimidTarget* _target = static_cast<TimidTarget*>(sender);
	addBloodLogo = Sprite::create("target/addbloodlogo.png");
	addBloodLogo->setPosition(_target->getContentSize());
	_target->addChild(addBloodLogo);
	ScaleTo*scaleBig = ScaleTo::create(0.5f,2.0f);
	ScaleTo* scaleNomal = ScaleTo::create(0.5f,1.0f);
	CallFuncN* addBlood = CallFuncN::create(CC_CALLBACK_1(TimidTarget::addBlood,this));
	addBloodLogo->runAction(Sequence::create(scaleBig,scaleNomal,addBlood,nullptr));
	Vec2 _nextPoint = _target->getNextPoint();
	//CCLOG("timid p_X=%.1f,p_Y=%0.1f,", _nextPoint.x, _nextPoint.y);
	_target->runtoNext(_nextPoint);
}

void TimidTarget::addBlood(Ref * sender)
{
	Sprite* addSprite = static_cast<Sprite*>(sender);
	addSprite->removeFromParent();
	setBlood(getBlood()+1,true);
}
