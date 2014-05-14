#pragma once
#include"cocos2d.h"
using namespace cocos2d;

class Battle_Unit;

class Battle_Portrait : public CCSprite
{
	Battle_Unit			*m_pUnit;
	CCSprite			*m_pFace;
	CCSprite			*m_pGauge[4];

public:

	Battle_Portrait();//init
	void setUnit(Battle_Unit *pChar);

	void tick(ccTime dt);

	//tick이 없이 tag를받아서 케릭터를 출력함.

};