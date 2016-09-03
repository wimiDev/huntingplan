#include "FreedomTarget.h"


FreedomTarget::FreedomTarget()
{

}


FreedomTarget::~FreedomTarget()
{
}
FreedomTarget* FreedomTarget::create(const char path[50])
{
	FreedomTarget*sprite = new FreedomTarget();
	sprite->initWithFile(path);
	return sprite;
}
FreedomTarget* FreedomTarget::create(const char path[50], int id, int kind, int blood, float velocity)
{
	FreedomTarget*sprite = new FreedomTarget();
	sprite->initWithSpriteFrameName("enemytexture/freedomenemy/freedomenemy_1.png");
	sprite->setId(id);
	sprite->setKind(kind);
	sprite->setBlood(blood,true);
	sprite->setVelocity(velocity);
	sprite->setcvelocity(velocity);
	sprite->setIsBezier(false);
	auto animation = Animation::create();
	animation->addSpriteFrame(SpriteFrameCache::getInstance()
		->getSpriteFrameByName("enemytexture/freedomenemy/freedomenemy_1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()
		->getSpriteFrameByName("enemytexture/freedomenemy/freedomenemy_2.png"));
	animation->setDelayPerUnit(1.0f / 24.0f);
	animation->setRestoreOriginalFrame(true);
	sprite->_runingAction = Animate::create(animation);
	sprite->runAction(RepeatForever::create(sprite->_runingAction));
	return sprite;
}
void FreedomTarget::setBlood(int blood, bool isAddCombo)
{
	if (blood < this->_blood&&blood > 0)
	{
		int score = abs(blood - _blood)*this->getHitScore();
		this->setHaveScore(getHaveScore() - score);
		GameUi::score->addScoreOnScene(score, this->getParent(), this->getPosition());
		this->_blood = blood;
		Audio::getInstance()->playeffectbykey("enemyhit");
	}
	else if (blood <= 0)
	{
		this->_blood = blood;
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
//TODO:
void FreedomTarget::bombAnimation()
{
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
	////TODO:this->getparent有时候获取到的是空，发生异常
	//if (this->getParent() == nullptr)
	//{
	//	log("bombAnimation getParent==nullptr");
	//	return;
	//}
	//this->getParent()->addChild(sprite_ani, 2);
	//auto action = Animate::create(animation);
	//this->stopAllActions();
	//CCCallFuncN*callback = CCCallFuncN::create([](Ref*sender)
	//{
	//	auto freedomTarget = static_cast<FreedomTarget*>(sender);
	//	DataOfGame::getInstance()->recycle_bin.pushBack(freedomTarget);
	//});
	//sprite_ani->runAction(Sequence::create(action, action->reverse(), callback, nullptr));
	BombParticle* _explosion = BombParticle::create("particle/particle_bomb5.plist");
	_explosion->setPosition(this->getPosition());
	this->getParent()->addChild(_explosion);
	Audio::getInstance()->playeffectbykey("smallenemybomb");
	this->stopAllActions();
	DataOfGame::getInstance()->recycle_bin.pushBack(this);
}

void FreedomTarget::runtoNext(Vec2 point)
{
	//摇取速度随机值
	int _ransp = random(1,3);
	//CCLOG("_ransp=%d",_ransp);
	if (_ransp == 2)
	{
		this->setVelocity(this->getcvelocity()*2);
	}
	else
	{
		this->setVelocity(this->getcvelocity());
	}
	float speed = sqrt(std::pow(abs(this->getPosition().x - point.x), 2) +
		std::pow(abs(this->getPosition().y - point.y), 2)) / this->getVelocity();
	MoveTo* moveTo = MoveTo::create(speed, point);
	float rota = getRotate(point);
	//CCLOG("%f",rota);
	RotateTo* rotate = RotateTo::create(0.5f, rota);

	CCCallFuncN* movefinish = CCCallFuncN::create(CC_CALLBACK_1(target::moveFinish, this));

	if (!getIsBezier())
	{
		Action* _action = Sequence::create(Spawn::create(moveTo, rotate, nullptr),
			movefinish, nullptr);
		_action->setTag(_ENEMYRUN_TAG_);
		this->runAction(_action);
	}
	else
	{
		//this->runAction(Sequence::create(bezier, movefinish, nullptr));
	}
	
}
