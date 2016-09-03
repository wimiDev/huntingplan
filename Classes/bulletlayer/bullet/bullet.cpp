#include "Bullet.h"


Bullet::Bullet()
{
	_id = -1;
	_kind = -1;
	_blood = 0;
	_velocity = 0;
	this->setTag(100);
}


Bullet::~Bullet()
{
}

PhysicsBody* Bullet::createPcircle(float r)
{
	PhysicsBody* body = PhysicsBody::createCircle(r, PhysicsMaterial(0.0f, 1.0f, 0.0f));
	body->setMass(5);
	body->setCategoryBitmask(BULLET_MASK);
	body->setContactTestBitmask(BULLET_CATE_MASK);
	body->setCollisionBitmask(BULLET_COLL_MASK);
	return body;
}
PhysicsBody* Bullet::createRect(Size size)
{
	PhysicsBody* body = PhysicsBody::createBox(size, PhysicsMaterial(0.0f, 1.0f, 0.0f));
	body->setMass(5);
	body->setCategoryBitmask(BULLET_MASK);
	body->setContactTestBitmask(BULLET_CATE_MASK);
	body->setCollisionBitmask(BULLET_COLL_MASK);
	return body;
}