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
	//���� �޴� ��...
	CG3Point	m_destPosition;
	float		m_fRemain;
	//hit�� ���Ͽ� �� �ΰ��� ��찡 �ִ�.
	//

public:

	kwOrderHit(Battle_Unit* owner, shared_ptr<kwMsg_Action> pMsgAttack, shared_ptr<kwMsg_Ani> pMsgAni);
	bool execute(ccTime dt);

	static kwOrderHit* makeHitOrder(Battle_Unit* owner, shared_ptr<kwMsg_Action> pMsgAttack, shared_ptr<kwMsg_Ani> pMsgAni);
};