#include "DoubleBullet.h"


DoubleBullet::DoubleBullet()
{
}


DoubleBullet::~DoubleBullet()
{
}
DoubleBullet* DoubleBullet::create(const char path[50], int id, int kind, int blood, int kill, float velocity, float w_Rotation)
{
	DoubleBullet*sprite = new DoubleBullet();
	sprite->initWithFile(path);
	sprite->setID(id);
	sprite->setKind(kind);
	sprite->setBlood(blood);
	sprite->setCBlood(blood);
	sprite->setKillability(kill);
	sprite->setVelocity(velocity);
	sprite->setw_Rotation(w_Rotation);
	return sprite;
}
void DoubleBullet::ScaleSmall(float scale)
{
	auto scaleTo = ScaleTo::create(0.1f,scale);
	auto body = this->getPhysicsBody();
	body->createCircle(this->getContentSize().width / 4, PhysicsMaterial(0.0f, 1.0f, 0.0f));
	this->runAction(scaleTo);
	this->setKillability(this->getKillability()*2);
}
void DoubleBullet::shootIt()
{
	auto body = this->getPhysicsBody();
	if (body == nullptr)
	{
		log("DoubleBullet::shootIt()..__body==nullptr");
		return;
	}
	float rota = this->getw_Rotation();
	float sx = 0;
	float sy = 0;
	float velocity = 1000 * this->getVelocity();
	if (rota >= 0)
	{
		sx = velocity * (rota / 90);
		sy = velocity * ((90 - rota) / 90);
	}
	else
	{
		sx = -velocity * (-rota / 90);
		sy = velocity * ((90 + rota) / 90);
	}
	body->applyImpulse(Vect(sx, sy));
}
