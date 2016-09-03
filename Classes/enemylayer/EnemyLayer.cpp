
#include"EnemyLayer.h"

void EnemyLayer::addbitenemy(int _kind, int _num,int _dir,Vec2 _pos)
{
	for (int _index = 0; _index < _num; ++_index)
	{
		target* _enemy = TargetMaker::getinstance()->Make_Target(_kind);
		_enemy->setDirection(_dir);
		_enemy->setPosition(_pos);
		this->addChild(_enemy);
		_enemy->runtoNext(_enemy->getNextPoint());
	}
}

EnemyLayer::EnemyLayer()
{

}
EnemyLayer::~EnemyLayer()
{

}
EnemyLayer * EnemyLayer::create()
{
	EnemyLayer* enemyLayer = new EnemyLayer();
	enemyLayer->init();
	enemyLayer->setContentSize(Size(540,360));
	enemyLayer->setColor(Color3B::GREEN);
	return enemyLayer;
}
bool EnemyLayer::init()
{
	if(!Layer::init())
	return false;
	EnemyLayer::tempTargetGropData = new int[5];
	EnemyLayer::targetTotle = 0;
	EnemyLayer::enemyResidue = 0;
	enemyInScene = 0;
	//TargetMaker::getinstance()->loadenemytexture();
	return true;
}
void EnemyLayer::GameModule_2AddEnemy()
{
	//��ѡȡ����
	int Kind = 0;
	Kind = random(1, 5);
	CCCallFuncN* callback = CCCallFuncN::create(CC_CALLBACK_1(EnemyLayer::Target_Movefinish, this));
	target* _target = TargetMaker::getinstance()->Make_Target(Kind);
	//ȷ�������˶��ķ���
	Vec2 startPoint;
	Vec2 endPoint;
	Size winSize = Director::getInstance()->getWinSize();
	int dir = 0;
	dir = random(0, 1);
	if (dir)
	{
		//������
		float start_Y = random((int)(winSize.height * 2 / 5), (int)(winSize.height - _target->getContentSize().height));
		startPoint = Vec2(0, start_Y);
		endPoint = Vec2(winSize.width, 0);
	}
	else
	{
		//���ҵ���
		float start_Y = random((int)(winSize.height * 2 / 5), (int)(winSize.height - _target->getContentSize().height));
		startPoint = Vec2(winSize.width, start_Y);
		endPoint = Vec2(-winSize.width, 0);
		_target->setRotation(-180);
	}
	_target->setAnchorPoint(Vec2(0.5f, 0.5f));
	startPoint = _target->ConverPoint(startPoint.x,startPoint.y);
	_target->setPosition(DataOfGame::getInstance()->LayerGetRealPosition(startPoint.x,startPoint.y));
	//_target->stopAllActions();
	this->addChild(_target);
	auto moveBy = MoveBy::create(abs(endPoint.x) / _target->getVelocity(), endPoint);
	_target->runAction(Sequence::create(moveBy, callback, nullptr));
}

void EnemyLayer::GameModule_4AddEnemy()
{
	//��ѡȡ����
	int Kind = 0;
	if (DataOfGame::getInstance()->totleEnemy >= 1000)
		{
			Kind = 6;
			DataOfGame::getInstance()->totleEnemy -= 1000;
		}
	else {
			Kind = random(1, 8); 
			if (DataOfGame::getInstance()->totleEnemy <= 0
				|| Kind == 3 || Kind == 7||Kind==6)
				{
					return;
				}
		}
	
	CCCallFuncN* callback = CCCallFuncN::create(CC_CALLBACK_1(EnemyLayer::GameModule4_enemyFinsh, this));
	target* _target = TargetMaker::getinstance()->Make_Target(Kind);
	//ȷ�������˶��ķ���
	Vec2 startPoint;
	Vec2 endPoint;
	Size winSize = Director::getInstance()->getWinSize();
	int dir = 0;
	_target->setDirection(dir);
	{
		//���ҵ���
		float start_Y = random((int)(winSize.height * 2 / 5), (int)(winSize.height - _target->getContentSize().height));
		startPoint = Vec2(winSize.width, start_Y);
		endPoint = Vec2(-winSize.width, 0);
		_target->setRotation(-180);
	}
	_target->setAnchorPoint(Vec2(0.5f, 0.5f));
	startPoint = _target->ConverPoint(startPoint.x,startPoint.y);
	_target->setPosition(DataOfGame::getInstance()->LayerGetRealPosition(startPoint.x,startPoint.y));
	this->addChild(_target);
	auto moveBy = MoveBy::create(abs(endPoint.x) / _target->getVelocity(), endPoint);
	_target->runAction(Sequence::create(moveBy, callback, nullptr));
	//�������м���һ������
	if(Kind != 6)
	{ 
		DataOfGame::getInstance()->totleEnemy--;
	}
}
void EnemyLayer::GameModule_3AddEnemy()
{
	PlayScene* playScene = static_cast<PlayScene*>(this->getParent());
	if (DataOfGame::getInstance()->enemyOnScene >= 
		DataOfGame::getInstance()->_enemyOnLayer[playScene->_gameState])
	{
	//	log("enemy > enemyOnLayer:%d", DataOfGame::getInstance()->enemyOnScene);
		return;
	}
	int enemyKind = rand_enemyKind();
	if (enemyKind <= 0)
		return;
	int dir = 0;
		dir = random(0,1);
		target* enemy = TargetMaker::getinstance()->Make_Target(enemyKind);
		enemy->setDirection(dir);
		Vec2 startPoint =enemy->getStartPoint();
		enemy->setPosition(Vec2(startPoint.x,startPoint.y));//DataOfGame::getInstance()->LayerGetRealPosition
		//log("startPoint.x=%f, startPoint.y=%f", enemy->getPosition().x,enemy->getPosition().y);
		addChild(enemy);
		enemy->runtoNext(enemy->getNextPoint());
	for (int i = 0; i < DataOfGame::getInstance()->enemyData.size(); ++i)
		{
			if (DataOfGame::getInstance()->enemyData.at(i).kind == enemyKind)
			{
				DataOfGame::getInstance()->enemyData.at(i).num-=1;
				DataOfGame::getInstance()->enemyOnScene += 1;
			}
		}
}

void EnemyLayer::killspy()
{
	PlayScene* playScene = static_cast<PlayScene*>(this->getParent());
	playScene->_killspy = 1;
}

int EnemyLayer::rand_enemyKind()
{
	int miniKind = 0;//��ȡ��Сid
	int maxKind = 0;//��ȡ����id
	for (int i = 0; i < DataOfGame::getInstance()->enemyData.size(); ++i)
	{
		if (DataOfGame::getInstance()->enemyData.at(i).kind>maxKind)
		{
			maxKind = DataOfGame::getInstance()->enemyData.at(i).kind;
		}
		if (DataOfGame::getInstance()->enemyData.at(i).kind < miniKind)
		{
			miniKind= DataOfGame::getInstance()->enemyData.at(i).kind;
		}
	}
	int kind = 0;
	int n = 100;
	while(n--)
	{ 
		kind = random(miniKind,maxKind);
		for (int i = 0; i < DataOfGame::getInstance()->enemyData.size(); ++i)
		{
			if (DataOfGame::getInstance()->enemyData.at(i).kind == kind)
			{
				if (DataOfGame::getInstance()->enemyData.at(i).num > 0)
				{
					kind = DataOfGame::getInstance()->enemyData.at(i).kind;
					return kind;
				}
					
			}
		}
	}
	kind = 0;
	return kind;
}
void EnemyLayer::Target_Movefinish(Ref * sender)
{
	target* _target = static_cast<target*>(sender);
	_target->setisFlo(false);
	DataOfGame::getInstance()->recycle_bin.pushBack(_target);
}
void EnemyLayer::GameModule4_enemyFinsh(Ref * sender)
{
	target* enemy = static_cast<target*>(sender);
	DataOfGame::getInstance()->recycle_bin.pushBack(enemy);
	if (enemy->getKind() == 7)
	{
		//����Ǽ���򲻼���
		return;
	}
	PlayScene* playScene = static_cast<PlayScene*>(this->getParent());
	playScene->addmiss();
}
void EnemyLayer::rand_br_start_end_point(int f)
{
	Size winSize = Director::getInstance()->getVisibleSize();;
	//��ȷ���˶�����f
	int seCount = 0;
	do {
		seCount++;
		brSePoint[0].x = random(0, (int)(winSize.width));
		brSePoint[0].y = random((int)(winSize.height * 1 / 3), (int)(winSize.height));
		brSePoint[1].x = random(0, (int)(winSize.width));
		brSePoint[1].y = random((int)(winSize.height * 1 / 3), (int)(winSize.height));
		if (abs(brSePoint[0].x - brSePoint[1].x) > 100)
			break;
	} while (seCount<10);
	int appear = 0;
	appear = random(1, 2);//ȷ�����ֵ�λ��
	if (appear == 1)
	{
		//��y���ϳ���
		if (f)
		{
			//��������
			sePoint[0].x = 0;
			sePoint[0].y = random(winSize.height / 2, winSize.height);
		}
		else
		{
			//��������
			sePoint[0].x = winSize.width;
			sePoint[0].y = random(winSize.height / 2, winSize.height);
		}
	}
	else
	{
		//��x���ϳ���
		if (f)
		{
			sePoint[0].x = random(0, (int)(winSize.width * 1 / 3));
			sePoint[0].y = winSize.height;
		}
		else
		{
			sePoint[0].x = random((int)(winSize.width * 2 / 3), (int)(winSize.width));
			sePoint[0].y = winSize.height;
		}
	}

	int disappear = 0;
	disappear = random(1, 2);//ȷ����ʧ��λ��
	if (disappear == 1)
	{
		//��y����ʧ
		if (f)
		{
			sePoint[1].x = winSize.width;
			sePoint[1].y = random((int)(winSize.height * 1 / 3), (int)(winSize.height));
		}
		else
		{
			sePoint[1].x = 0;
			sePoint[1].y = random((int)(winSize.height * 1 / 3), (int)(winSize.height));
		}
	}
	else
	{
		//��x����ʧ
		if (f)
		{
			sePoint[1].x = random((int)(winSize.width * 3 / 5), (int)(winSize.width));
			sePoint[1].y = winSize.height;
		}
		else
		{
			sePoint[1].x = random(0, (int)(winSize.width * 2 / 5));
			sePoint[1].y = winSize.height;
		}
	}
}
