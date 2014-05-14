#pragma once
#include"cocos2d.h"
#include"header.h"
#include"kwController.h"
#include"Portrait.h"
using namespace cocos2d;
using namespace std;

const CGPoint G_CHARMENU_HIDE_POSITION[MAX_HERO_COUNT] = {
	ccp(-150, 0),
	ccp(-150, 130),
	ccp(-150, 260),
	ccp(-150, 390)
};

const CGPoint G_CHARMENU_VISIBLE_POSITION = ccp(320, 400);
const CGPoint G_CHAR_PORTRAIT_POSITION = ccp(520, 400);

//t키를 눌렀을 때 나오는 UI를 조작한다.

class Battle_CharUI;
class Battle_Unit;

class Battle_MenuUI : public CCSprite
{
	int			m_iMenu;
	int			m_iCurrentSelected;
	KwController	m_Controller;
	Battle_CharUI	*m_pCharUI[MAX_HERO_COUNT];
	Portrait	*m_pPortrait;

	float			m_fPortOpacity;

public:

	Battle_MenuUI(vector<Battle_Unit*>* pList);
	void tick(ccTime dt);
	void doCtrl(ccTime dt);
	void doMenu(ccTime dt);

private:
	void doCtrlMenu1(ccTime dt);
	void doCtrlMenu2(ccTime dt);
	void doCtrlMenu3(ccTime dt);
};