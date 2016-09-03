#include "bombparticle.h"

BombParticle * BombParticle::create(const char *_path)
{
	BombParticle* _bombparticle = new BombParticle();
	_bombparticle->init();
	ParticleSystemQuad* _explosion = nullptr;
	_explosion = ParticleSystemQuad::create(_path);
	_explosion->setPosition(0,0);
	_explosion->setAutoRemoveOnFinish(true);
	_bombparticle->addChild(_explosion);
	return _bombparticle;
}
