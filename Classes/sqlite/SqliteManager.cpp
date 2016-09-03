#include"SqliteManager.h"

//创建数据库
void SqliteManager::createSqliteDatebase(char* dataBaseName)
{
	pdb = NULL;
	// 1.指定数据库路径
	_databasename = dataBaseName;
	string path = CCFileUtils::sharedFileUtils()->getWritablePath() + _databasename;
	//  2.检查指定路径下数据库 audio.db3是否存在
	bool isExist = CCFileUtils::sharedFileUtils()->isFileExist(path);
	if (!isExist) {
		CCLOG("%s不存在", path.c_str());
	}
	else
	{
		CCLOG("%s存在", path.c_str());
		//        在IOS或安卓上删除该数据库
		//        your code .........
	}
	result = sqlite3_open(path.c_str(), &pdb);
	if (result == SQLITE_OK)
	{
		CCLOG("open database success,  number=%d", result);
	}
	else
	{
		CCLOG("open database failed,  number=%d", result);
	}

	//this->createTable("module");
}
//  创建表
bool SqliteManager::createTable(const char* tablename)
{

	sql = "create table " + string(tablename) + "(RANK integer primary key autoincrement,name text,score text)";
	//创建表
	result = sqlite3_exec(pdb,sql.c_str(), NULL, NULL, NULL);
	if (result == SQLITE_OK)
	{
		CCLOG("create table success!");
		return true;
	}
	else
	{
		CCLOG("create table failed!");
		return false;
	}
}
//    插入一条数据
bool SqliteManager::insertData(const char* _tablename, const char* _rank, const char *_name, const char*_score)
{
	string s1("insert into "+ string(_tablename) +" values(");
	string s2(_rank);
	string s3(",");
	string s4(_name);
	string s5(_score);

	sql = s1 + s2 + s3 + "'" + s4 + "'"+","+"'"+s5+"'"+")";
	CCLOG("%s", sql.c_str());
	result = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	if (result != SQLITE_OK)
	{
		CCLOG("insert data failed!");
		return false;
	}
	else
	{
		CCLOG("insert data success!");
		return true;
	}

}
//    更新一条数据
bool SqliteManager::updateData(const char* tablename,const char* _rank, const char *_name, const char*_score)
{
	bool _issccuful = false;
	string s1("update "+string(tablename)+" set name=");
	string s2(_name);
	string s5("set score=");
	string s6(_score);
	string s3(" where RANK=");
	string s4(_rank);
	sql = s1 + "'" + s2 +"'"+  s3 + s4;//","+s5+"'"+s6+"'" +
	CCLOG("%s", sql.c_str());
	result = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	if (result != SQLITE_OK)
	{
		CCLOG("update name=%s fail!",_name);
		return false;
	}
	else
	{

		CCLOG("update name=%ssucceful!",_name);
		_issccuful = true;
	}
	s1="update " + string(tablename) + " set score=";
	s6=_score;
	s3=" where RANK=";
	s4=_rank;
	sql = s1 + "'" + s6 + "'" + s3 + s4;
	result = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	if (result != SQLITE_OK)
	{
		CCLOG("update score=%s fail!", _score);
		return false;
	}
	else
	{

		CCLOG("update score=%s succeful!", _score);
		_issccuful = true;
	}
	return _issccuful;
}
//   删除一条数据
bool SqliteManager::deleteData(const char* _tableanme, const char* _rank)
{


	string s1("delete from "+string(_tableanme)+" where RANK=");
	string s2(_rank);
	sql = s1 + s2;
	CCLOG("%s", sql.c_str());
	result = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	if (result != SQLITE_OK)
	{
		CCLOG("delete data failed!");
		return false;
	}
	else
	{

		CCLOG("delete data success!");
		return true;
	}

}
//  查询获取数据
const char * SqliteManager::getScore(int _rank, char* _tableName)
{
	int r, c;
	char buff[200] = { 0 };
	string s1("select score from "+string(_tableName)+" where RANK=");
	sprintf(buff, "%d", _rank);
	string s2(buff);
	sql = s1 + s2;
	CCLOG("%s", sql.c_str());
	result = sqlite3_get_table(pdb, sql.c_str(), &re, &r, &c, NULL);
	CCLOG("row is %d,column is %d", r, c);
	if (result != SQLITE_OK||(r==0&&c==0))
	{
		CCLOG(" data failed!");
		return " ";
	}
	else
	{

		CCLOG("data success!");
		CCLOG("re=%s",re[1]);
		return re[1];
	}

}
const char * SqliteManager::getName(int _rank, char * _tablename)
{
	int r, c;
	char buff[200] = { 0 };
	string s1("select name from " + string(_tablename) + " where RANK=");
	sprintf(buff, "%d", _rank);
	string s2(buff);
	sql = s1 + s2;
	CCLOG("%s", sql.c_str());
	result = sqlite3_get_table(pdb, sql.c_str(), &re, &r, &c, NULL);
	CCLOG("row is %d,column is %d", r, c);
	if (result != SQLITE_OK || (r == 0 && c == 0))
	{
		CCLOG(" data failed!");
		return " ";
	}
	else
	{

		CCLOG("data success!");
		CCLOG("re=%s", re[1]);
		return re[1];
	}
	return " ";
}
void SqliteManager::CloseDataBase()
{
	sqlite3_free_table(re);

	sqlite3_close(pdb);
}

SqliteManager::SqliteManager()
{

}
SqliteManager::~SqliteManager()
{
	if (re != NULL)
	{
		sqlite3_free_table(re);

		sqlite3_close(pdb);
	}

}