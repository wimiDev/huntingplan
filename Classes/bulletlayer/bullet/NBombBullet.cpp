#include "NBombBullet.h"


NBombBullet::NBombBullet()
{
}


NBombBullet::~NBombBullet()
{
}
NBombBullet* NBombBullet::create(const char path[50], 
								int id, int kind, int blood,
								int kill, float velocity, float w_Rotation,
								float rBomb)
{
	NBombBullet*sprite = new NBombBullet();
	sprite->initWithFile(path);
	sprite->setID(id);
	sprite->setKind(kind);
	sprite->setBlood(blood);
	sprite->setCBlood(blood);
	sprite->setKillability(kill);
	sprite->setVelocity(velocity);
	sprite->setw_Rotation(w_Rotation);
	sprite->setR_Bomb(rBomb);
	return sprite;
}
void NBombBullet::shootIt()
{
	auto body = this->getPhysicsBody();
	if (body == nullptr)
	{
		log("NBombBullet::shootIt()..__body==nullptr");
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

