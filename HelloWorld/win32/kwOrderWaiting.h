#pragma once

#include"kwOrder.h"
#include"Point.h"
#include<memory>
using namespace std;

class Battle_Unit;
class kwMsg_Ani;

class kwOrderWaiting : public kwOrder
{
	shared_ptr<kwMsg_Ani> m_pMsgAni;
	float	   m_fWaitTime;
public:
	kwOrderWaiting(Battle_Unit *owner,float waitTime,shared_ptr<kwMsg_Ani> pMsgAni);

	bool execute(ccTime dt);
	static kwOrderWaiting* makeWaitOrder(Battle_Unit*,float waittime, int cat,int fs,int fr,int fe,float ft);
};