#pragma once
#include"cocos2d.h"
using namespace cocos2d;

class Battle_Unit;

class Manager_Global
{//게임코어 같은거
private:
	Manager_Global();

public:
	static Manager_Global* instance;
	static Manager_Global* getInstance();

public:
	float g_fBattleDT;
	int	  g_iDebugFlag;
	int	  g_iRenderFlag;

	int	  g_iID;

	CGPoint g_offsetGameScroll;  //화면 스크롤시 쓰임...
	CGPoint g_DestOffsetGameScroll;
	Battle_Unit *g_pScollTarget;
public:
	void *g_pControllPermission; //이것이 가리키고 있는 객체만 키입력을 받을 수 있음...
	void *g_pBattleMenuUI;
	void *g_pBattleSprite;
	
public:
	
	float globalTick(float dt);
};