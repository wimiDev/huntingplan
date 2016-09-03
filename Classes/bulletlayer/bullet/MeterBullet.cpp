#include "MeterBullet.h"


MeterBullet::MeterBullet()
{
}


MeterBullet::~MeterBullet()
{
}
MeterBullet* MeterBullet::create(const char path[50])
{
	MeterBullet*sprite = new MeterBullet();
	sprite->initWithFile(path);
	return sprite;
}
MeterBullet* MeterBullet::create(const char path[50], int id, int kind, int blood, int kill,float velocity, float w_Rotation)
{
	MeterBullet*sprite = new MeterBullet();
	sprite->initWithSpriteFrameName("bullet/meterbullet/meterbullet_1.png");
	sprite->setID(id);
	sprite->setKind(kind);
	sprite->setBlood(blood);
	sprite->setCBlood(blood);
	sprite->setKillability(kill);
	sprite->setVelocity(velocity);
	sprite->setw_Rotation(w_Rotation);
	auto animation = Animation::create();
	animation->addSpriteFrame(SpriteFrameCache::getInstance()
		->getSpriteFrameByName("bullet/meterbullet/meterbullet_1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()
		->getSpriteFrameByName("bullet/meterbullet/meterbullet_2.png"));
	animation->setDelayPerUnit(1.0f / 24.0f);
	animation->setRestoreOriginalFrame(true);
	sprite->runAction(RepeatForever::create( Animate::create(animation)));
	return sprite;
}
void MeterBullet::shootIt()
{
	float rota = this->getw_Rotation();
	auto body = this->getPhysicsBody();
	if (body == nullptr)
	{
		log("MeterBullet::shootIt()..__body==nullptr");
		return;
	}
	float sx = 0;
	float sy = 0;
	float velocity = 1000 * this->getVelocity();
	if (rota >= 0)
	{
		sy = velocity * std::sin(CC_DEGREES_TO_RADIANS(90 - rota));
		sx = velocity* std::cos(CC_DEGREES_TO_RADIANS(90 - rota));
	}
	else
	{
		sy = velocity * std::sin(CC_DEGREES_TO_RADIANS(90 + rota));
		sx = -velocity* std::cos(CC_DEGREES_TO_RADIANS(90 + rota));
	}
	//CCLOG("sx = %f,sy = %f",sx,sy);
	body->applyImpulse(Vect(sx, sy));
}
