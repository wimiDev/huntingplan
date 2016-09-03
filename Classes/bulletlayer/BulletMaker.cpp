#include "BulletMaker.h"


//BulletMaker::BulletMaker()
//{
//}
//
//
//BulletMaker::~BulletMaker()
//{
//
//}
//
////MeterBullet* BulletMaker::make_meterBullet(float rotate)
////{
////	MeterBullet* _bullet = MeterBullet::create(ImgPath::path_bullet1.c_str(), 0, 1, 1, 1, 5, rotate);
////	_bullet->setPhysicsBody(createRect(_bullet->getContentSize()));
////	return _bullet;
////}
////DoubleBullet* BulletMaker::make_doubleBullet(float rotate)
////{
////	DoubleBullet* _bullet = DoubleBullet::create(ImgPath::path_bullet2.c_str(),0,2,2,1,5,rotate);
////	_bullet->setPhysicsBody(createPcircle(_bullet->getContentSize().width/2));
////	return _bullet;
////}
////NBombBullet* BulletMaker::make_nbombBullet(float rotate)
////{
////	NBombBullet* _bullet = NBombBullet::create(ImgPath::path_bullet3.c_str(), 0, 3, 1,0, 5, rotate, 200);
////	_bullet->setPhysicsBody(createRect(_bullet->getContentSize()));
////	return _bullet;
////}
//FireBomb * BulletMaker::make_fireBomb()
//{
//	//FireBomb* fireBomb = FireBomb::create();
//	//fireBomb->setPhysicsBody(createRect(fireBomb->getContentSize()));
//	//return fireBomb;
//}
//PhysicsBody* BulletMaker::createPcircle(float r)
//{
//	//PhysicsBody* body = PhysicsBody::createCircle(r, PhysicsMaterial(0.0f, 1.0f, 0.0f));
//	//body->setMass(5);
//	//body->setCategoryBitmask(BULLET_MASK);
//	//body->setContactTestBitmask(BULLET_CATE_MASK);
//	//body->setCollisionBitmask(BULLET_COLL_MASK);
//	//return body;
//}
//PhysicsBody* BulletMaker::createRect(Size size)
//{
//	//PhysicsBody* body = PhysicsBody::createBox(size, PhysicsMaterial(0.0f, 1.0f, 0.0f));
//	//body->setMass(5);
//	//body->setCategoryBitmask(BULLET_MASK);
//	//body->setContactTestBitmask(BULLET_CATE_MASK);
//	//body->setCollisionBitmask(BULLET_COLL_MASK);
//	//return body;
//}