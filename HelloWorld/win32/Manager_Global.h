#pragma once
#include"cocos2d.h"
using namespace cocos2d;

class Battle_Unit;

class Manager_Global
{//�����ھ� ������
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

	CGPoint g_offsetGameScroll;  //ȭ�� ��ũ�ѽ� ����...
	CGPoint g_DestOffsetGameScroll;
	Battle_Unit *g_pScollTarget;
public:
	void *g_pControllPermission; //�̰��� ����Ű�� �ִ� ��ü�� Ű�Է��� ���� �� ����...
	void *g_pBattleMenuUI;
	void *g_pBattleSprite;
	
public:
	
	float globalTick(float dt);
};