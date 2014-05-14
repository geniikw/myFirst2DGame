#pragma once

#include"kwOrder.h"
#include<memory>

class Battle_Unit;
class kwMsg_Ani;
class kwMoving_Vector;

class kwOrderMoveToTarget : public kwOrder
{
	//�ʿ��� ����...

	int					  m_iPhase;
	CG3Point			  m_dest;//������... ��...-_-

	float				  m_fStartAcceleration;
	float				  m_fEndAccelaration;
	float				  m_fMaxSpeed;
	shared_ptr<kwMsg_Ani> m_pMsgAni;

private://���ο��� ���Ǵ� ����...
	//�̰� owner���� ����Ǹ鼭 owner�� �����Ŵ ����� ������ delete
	kwMoving_Vector *m_pMovingStragith;

public:
	kwOrderMoveToTarget(Battle_Unit *owner,
		CG3Point dest,
		float sa, float ea, float speed,
		shared_ptr<kwMsg_Ani> pMsgAni);

	virtual bool execute(ccTime dt);

	static kwOrder* makekwOrderMoveToPoint(
		Battle_Unit* owner,
		const CG3Point &dest,
		float sa, float ea, float speed,
		shared_ptr<kwMsg_Ani> pMsgAni);

};