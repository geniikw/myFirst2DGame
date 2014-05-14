#pragma once

#include"cocos2d.h"
#include"UI_CharState.h"
#include"UI_TownMenu.h"
using namespace cocos2d;


class UI_Menu : public CCSprite
{
	UI_CharState *m_pChar[4];
	UI_TownMenu *m_pMenu;

	float m_fSeletedAngle;
	float m_fDestAngle;

	int m_iRightKeyPress;
	int m_iLeftKeyPress;

public:
	bool init();
	void tick(ccTime dt);

public:
	void semiInit();//Hero <-> Menu간 이동할 때 호출되는 함수
};