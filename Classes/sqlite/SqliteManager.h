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
	//   ����һ�����ݿ�
	void createSqliteDatebase(char* dataBaseName);
	//  ������
	bool createTable(const char* tablename);
	//   ����һ������
	bool insertData(const char* tablename,const char* rank, const char *name,const char*score);
	//   ����һ������
	bool updateData(const char* tablename,const char* rank, const char *name, const char*score);
	//   ɾ��һ������
	bool deleteData(const char* tableanme,const char* _rank);
	//  ��ѯ��ȡscore����
	const char* getScore(int _rank,char* tableName);
	const char* getName(int _rank,char* _tablename);
	//  �ر����ݿ�
	void CloseDataBase();
};
#endif
