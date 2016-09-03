#include "enemyprocess.h"

EnemyProcess * EnemyProcess::create()
{
	EnemyProcess* _enemyprocess = new EnemyProcess();
	_enemyprocess->_nodeenemyprocess=CSLoader::createNode("panellayer/node_enemyprocess.csb");
	_enemyprocess->_enemynum = 0;
	_enemyprocess->_enmeynumbg =
		static_cast<Sprite*>(DataOfGame::getInstance()->seekNodebyName(_enemyprocess->_nodeenemyprocess, "sprite_bg"));
	_enemyprocess->enemyIcon =
		static_cast<Sprite*>(DataOfGame::getInstance()->seekNodebyName(_enemyprocess->_nodeenemyprocess, "sprite_icon"));
	_enemyprocess->_textenemynum =
		static_cast<ui::Text*>(DataOfGame::getInstance()->seekNodebyName(_enemyprocess->_nodeenemyprocess, "text_enemynum"));
	_enemyprocess->_loadingbarenemy =
		static_cast<ui::LoadingBar*>(DataOfGame::getInstance()->seekNodebyName(_enemyprocess->_nodeenemyprocess, "loadingbar_enemyprocess"));
	return _enemyprocess;
}

void EnemyProcess::SetEnemyNum(int _num, float _per)
{
	char _strnum[10];
	sprintf(_strnum,"%d",_num);
	_textenemynum->setString(_strnum);
	_loadingbarenemy->setPercent(_per);
	_enemynum = _num;
}
