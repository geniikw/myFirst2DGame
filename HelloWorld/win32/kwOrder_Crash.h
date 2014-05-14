#pragma once

#include<memory>
using namespace std;

#include"kwOrder.h"

class kwMsg_Action;
class kwMsg_Ani;
class Battle_AttackBox;

class kwOrder_Crash : public kwOrder
{
	shared_ptr<kwMsg_Ani>	 m_pMsgAni;
	CG3Point	m_vctForce;
	int			m_iDamage;

	CG3Point	m_destPosition;
	float		m_fRemain;

public:

	kwOrder_Crash(Battle_Unit* owner, CG3Point force, int damage, shared_ptr<kwMsg_Ani> pMsgAni);
	bool execute(ccTime dt);

	static kwOrder_Crash* makeCrashOrder(Battle_Unit* owner, CG3Point force, int damage, shared_ptr<kwMsg_Ani> pMsgAni);
};