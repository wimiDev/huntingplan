#ifndef __SQLITEMANAGER_H_
#define __SQLITEMANAGER_H_
#include"sqlite/sqlite3.h"
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;
class SqliteManager
{
private:
	sqlite3 * pdb;
	string sql;
	int result;
	char **re;
	string _databasename;
public:
	SqliteManager();
	~SqliteManager();
	//   创建一个数据库
	void createSqliteDatebase(char* dataBaseName);
	//  创建表
	bool createTable(const char* tablename);
	//   插入一条数据
	bool insertData(const char* tablename,const char* rank, const char *name,const char*score);
	//   更新一条数据
	bool updateData(const char* tablename,const char* rank, const char *name, const char*score);
	//   删除一条数据
	bool deleteData(const char* tableanme,const char* _rank);
	//  查询获取score数据
	const char* getScore(int _rank,char* tableName);
	const char* getName(int _rank,char* _tablename);
	//  关闭数据库
	void CloseDataBase();
};
#endif
