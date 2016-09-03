/*
*��Ϸ��Դ�ļ��������Ϸ��ͼ�����Ƶ��Դ
*wimiDev 
*/
#ifndef __GAMERESOURCE_H_
#define __GAMERESOURCE_H_

#include"cocos2d.h"
#include "SimpleAudioEngine.h"
//#include "json/rapidjson.h"
//#include "json/document.h"
#include"DataOfGame.h"

using namespace cocos2d;

//�����࣬ͼƬ��Դ�����߶�����Դ
class ImgPath
{
public:
	static std::string path_powerpoolbg_nomal;
	static std::string path_powerpoolbg_light;
	//��Ϸ����
	static std::string path_mainUi;
	////�ؿ����ݸ�Ŀ¼
	static std::string path_round_data;
};
//�����࣬��Ч����������	
class Audio
{
public:
	enum DIRVER
	{
		_ANDROID,
		_IOS,
		WINPHONE
	};
	static Audio* getInstance();
	bool init();
	//Ԥ�ر�������
	void loadBgMusic();
	//Ԥ����Ч
	void loadEffect();
	void playbmgbykey(const char* _key);
	void PlayBgMusic(std::string path);//���ű�������
	void playeffectbykey(const char* _key,bool _allplay=false);
	void PlayEffect(std::string path,bool allplay=false);//������Ч
	void setIsPlayBgMusic(bool isplay);
	void setIsPlayEffect(bool isplay);
	bool isPlayBgMusic;
	bool isPlayEffect;
	std::string getbgmbykey(const char* _key);
	std::string geteffectbykey(const char* _key,DIRVER _dir = _ANDROID);
public:
	//��������·��
	std::string _bgmusicpath;
private:
	static Audio* _instance;

};
class GameStringValue
{
public:
	static std::string* getStringByKey(const std::string key);
};
#endif