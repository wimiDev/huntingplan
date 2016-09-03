#include "GameResource.h"

/*
*图片，动画资源
*/

//背景
std::string ImgPath::path_mainUi= "mainscenelayer/playscenebg_1.png";

std::string ImgPath::path_powerpoolbg_nomal = "texture_img/texture_button/combopower_1.png";
std::string ImgPath::path_powerpoolbg_light = "texture_img/texture_button/combopower_2.png";

//关卡数据
std::string ImgPath::path_round_data = "rounddata/round_data%d.json";

/*音频*/
Audio* Audio::_instance = nullptr;
bool Audio::init()
{
	isPlayBgMusic = false;
	isPlayEffect = false;
	_bgmusicpath = "";
	return true;
}
Audio* Audio::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new Audio();
		_instance->init();
	}
	return _instance;
}
std::string Audio::getbgmbykey(const char* _key)
{
	std::string _path = "";
	std::string _strjson = 
		DataOfGame::getInstance()->getJsonString("audio/background_music/backgroundmusic.json");
	rapidjson::Document _doc;
	_doc.Parse<0>(_strjson.c_str());
	if (_doc.HasParseError())
	{
		CCLOG("getbgmbykey parse error!");
		return _path;
	}
	if (!_doc.HasMember(_key))
	{
		CCLOG("getbgmbykey not '%s'!",_key);
		return _path;
	}
	_path = _doc[_key].GetString();
	return _path;
}
std::string Audio::geteffectbykey(const char* _key, DIRVER _dir)
{
	std::string _path = "";
	std::string _strjson =
		DataOfGame::getInstance()->getJsonString("audio/effect/effect.json");
	rapidjson::Document _doc;
	_doc.Parse<0>(_strjson.c_str());
	if (_doc.HasParseError())
	{
		CCLOG("geteffectbykey parse error!");
		return _path;
	}
	rapidjson::Value _dirkey;
	switch (_dir)
	{
	case _ANDROID:
	{
		if (!_doc.HasMember("android"))
		{
			CCLOG("geteffectbykey not android!");
			return _path;
		}
		_dirkey = _doc["android"];
		if (!_dirkey.HasMember(_key))
		{
			CCLOG("geteffectbykey not '%s'!",_key);
			return _path;
		}
		_path = _dirkey[_key].GetString();
	}break;
	case _IOS:
	{
		if (!_doc.HasMember("ios"))
		{
			CCLOG("geteffectbykey not ios!");
			return _path;
		}
		_dirkey = _doc["ios"];
		if (!_dirkey.HasMember(_key))
		{
			CCLOG("geteffectbykey not '%s'!", _key);
			return _path;
		}
		_path = _dirkey[_key].GetString();
	}break;
	case WINPHONE:
	{
		if (!_doc.HasMember("winphone"))
		{
			CCLOG("geteffectbykey not winphone!");
			return _path;
		}
		_dirkey = _doc["winphone"];
		if (!_dirkey.HasMember(_key))
		{
			CCLOG("geteffectbykey not '%s'!", _key);
			return _path;
		}
		_path = _dirkey[_key].GetString();
	}break;
	default:
		break;
	}
	return _path;
}
void Audio::setIsPlayBgMusic(bool isplay)
{
	isPlayBgMusic = isplay;
	if (!isPlayBgMusic)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(_bgmusicpath.c_str(), true);
	}
}
void Audio::setIsPlayEffect(bool isplay)
{
	isPlayEffect = isplay;
	if (!isPlayEffect)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
	}
}
void Audio::PlayBgMusic(std::string path)
{
	_bgmusicpath = path;
	if (isPlayBgMusic)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(path.c_str(),true);
	}
}
void Audio::playbmgbykey(const char* _key)
{
	std::string _path = getbgmbykey(_key);
	_bgmusicpath = _path;
	if (isPlayBgMusic)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(_path.c_str(), true);
	}
}
void Audio::PlayEffect(std::string path,bool allPlay)
{
	if (isPlayEffect)
	{
		//if(!allPlay)
		//CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(path.c_str());
	}
}
void Audio::playeffectbykey(const char* _key,bool _allplay)
{
	if (isPlayEffect)
	{
		//if (!_allplay)
		//CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
		std::string  _path = geteffectbykey(_key);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(_path.c_str());
	}
}
void Audio::loadBgMusic()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(getbgmbykey("mainscenebgm").c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(getbgmbykey("gamemodule2bgm").c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(getbgmbykey("gamemodule3bgm").c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(getbgmbykey("gamemodule4bgm").c_str());
}
void Audio::loadEffect()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(geteffectbykey("meterbullet").c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(geteffectbykey("firebomb").c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(geteffectbykey("combo").c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(geteffectbykey("combofial").c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(geteffectbykey("gameover").c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(geteffectbykey("getprop").c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(geteffectbykey("propappear").c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(geteffectbykey("enemyhit").c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(geteffectbykey("smallenemybomb").c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(geteffectbykey("bigenemybomb").c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(geteffectbykey("click").c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(geteffectbykey("messagepush").c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(geteffectbykey("ding").c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(geteffectbykey("victory").c_str());
}


std::string* GameStringValue::getStringByKey(const std::string key)
{
	std::string *str_string=new std::string("null");
	ssize_t file_size = 0;
	unsigned char* pBytes = cocos2d::FileUtils::sharedFileUtils()->getFileData("stringvalue/stringvalue.json", "r", &file_size);
	if (pBytes == nullptr || strcmp((char*)pBytes, "") == 0)
	{
		str_string =new  std::string("file error");
		return str_string;
	}
	std::string dataByTarget((const char*)pBytes, file_size);
	rapidjson::Document d;
	d.Parse<0>(dataByTarget.c_str());
	if (!d.HasParseError())
	{
		log("Parese_ok");
		if (d.HasMember(key.c_str()))
		{
			*str_string= d[key.c_str()].GetString();
		}

	}
	return str_string;
}