#pragma once

#include<memory>
using namespace std;

#include"kwOrder.h"


class kwMsg_Action;
class kwMsg_Ani;
class Battle_AttackBox;

class kwOrderHit : public kwOrder
{
	shared_ptr<kwMsg_Action> m_pMsgAttack;
	shared_ptr<kwMsg_Ani>	 m_pMsgAni;
	//현재 받는 힘...
	CG3Point	m_destPosition;
	float		m_fRemain;
	//hit에 관하여 총 두가지 경우가 있다.
	//

public:

	kwOrderHit(Battle_Unit* owner, shared_ptr<kwMsg_Action> pMsgAttack, shared_ptr<kwMsg_Ani> pMsgAni);
	bool execute(ccTime dt);

	static kwOrderHit* makeHitOrder(Battle_Unit* owner, shared_ptr<kwMsg_Action> pMsgAttack, shared_ptr<kwMsg_Ani> pMsgAni);
};