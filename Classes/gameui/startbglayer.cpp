#include"startbglayer.h"

StartBgLayer::StartBgLayer()
{
}

StartBgLayer::~StartBgLayer()
{

}

bool StartBgLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	_startvector = new Vector<Sprite*>();

	return true;
}

StartBgLayer * StartBgLayer::create()
{
	StartBgLayer* _startbglayer = new StartBgLayer();
	_startbglayer->setAnchorPoint(Vec2(0.5f,0.5f));
	_startbglayer->init();
	return _startbglayer;
}

void StartBgLayer::fullStartToLayer(int _num)
{
	float _pX = 0.0f;
	float _pY = 0.0f;

	float _minX = 0.0f;
	float _maxX = 1080;

	float _minY = 0.0f;
	float _maxY = 720;

	for (int index = 0; index < _num; ++index)
	{
		_pX = random(_minX,_maxX);
		_pY = random(_minY,_maxY);
		Sprite* _start = Sprite::create("mainscenelayer/start_1.png");
		if (!_start)
		{
			continue;
		}
		_start->setPosition(Vec2(_pX,_pY));
		_startvector->pushBack(_start);
		this->addChild(_start);
	}

}
