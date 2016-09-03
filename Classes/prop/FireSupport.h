
#ifndef __FIRESUPPORT_H_
#define __FIRESUPPORT_H_

#include "prop/Prop.h"
#include"bulletlayer/bullet/FireBomb.h"
#include"playscene/PlayScene.h"
#include"panellayer/gameinfotext.h"
#include"panellayer/PanelLayer.h"

class FireSupport :
	public Prop
{
public:
	FireSupport();
	~FireSupport();
	/*
	*¿ªÆô»ðÁ¦Ö§Ô®
	*/
	void OpenFireSupport(Node*scne);
};

#endif
