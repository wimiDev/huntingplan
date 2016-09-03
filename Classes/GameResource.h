/*
*游戏资源文件，存放游戏的图像和音频资源
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

//单例类，图片资源，或者动画资源
class ImgPath
{
public:
	static std::string path_powerpoolbg_nomal;
	static std::string path_powerpoolbg_light;
	//游戏背景
	static std::string path_mainUi;
	////关卡数据根目录
	static std::string path_round_data;
};
//单例类，音效，背景音乐	
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
	//预载背景音乐
	void loadBgMusic();
	//预载音效
	void loadEffect();
	void playbmgbykey(const char* _key);
	void PlayBgMusic(std::string path);//播放背景音乐
	void playeffectbykey(const char* _key,bool _allplay=false);
	void PlayEffect(std::string path,bool allplay=false);//播放音效
	void setIsPlayBgMusic(bool isplay);
	void setIsPlayEffect(bool isplay);
	bool isPlayBgMusic;
	bool isPlayEffect;
	std::string getbgmbykey(const char* _key);
	std::string geteffectbykey(const char* _key,DIRVER _dir = _ANDROID);
public:
	//背景音乐路径
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