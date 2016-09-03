#ifndef __PANELLAYER_GAMEINFOTEXT_H_
#define __PANELLAYER_GAMEINFOTEXT_H_
#include"cocos2d.h"
#include"ui/UIText.h"
using namespace cocos2d;

class GameInfoText:
	public ui::Text
{
public:
	static GameInfoText* create(const char* _string,const char* _font,int _size);
	//*œ‘ æ–≈œ¢£¨µØ¥∞£¨
	void showInfoText(CCCallFuncN* callback);
private:
};
#endif // !__PANELLAYER_GAMEINFOTEXT_H_
