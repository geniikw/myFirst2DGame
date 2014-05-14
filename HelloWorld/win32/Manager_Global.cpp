#include"Manager_Global.h"
#include"Battle_Unit.h"

Manager_Global::Manager_Global()
{
	g_fBattleDT = 1.f;
	g_iDebugFlag = 0;
	g_iRenderFlag = 1;
	g_iID = 0;
	
	g_offsetGameScroll = CGPointZero;
	g_DestOffsetGameScroll = CGPointZero;
	g_pScollTarget = NULL;
}

Manager_Global* Manager_Global::getInstance()
{
	if (instance == nullptr) instance = new Manager_Global;

	return instance;
}

	
float Manager_Global::globalTick(float dt)
{
	if (g_iDebugFlag == 1)
	{
		if (GetAsyncKeyState(VK_RIGHT))
		{
			g_offsetGameScroll.x -= 100.f *dt;
		}

		if (GetAsyncKeyState(VK_LEFT))
		{
			g_offsetGameScroll.x += 100.f *dt;
		}

		if (g_pScollTarget == NULL)
		{
			g_DestOffsetGameScroll = CGPointZero;
		}
	}
	else
	{
		CGPoint dif = g_DestOffsetGameScroll - g_offsetGameScroll;
		dif.x = dif.x * dt;
		dif.y = dif.y * dt;

		g_offsetGameScroll = g_offsetGameScroll + dif;
	}
	//디버깅용... 전투 tick에서 들어가있음

	dt = dt * g_fBattleDT;
	return dt;
}

