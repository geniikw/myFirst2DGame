#pragma once

#include"kwOrder.h"
#include<memory>

class Battle_Unit;
class kwMsg_Ani;
class kwMoving_Vector;

class kwOrderMoveToTarget : public kwOrder
{
	//필요한 정보...

	int					  m_iPhase;
	CG3Point			  m_dest;//목적지... 흠...-_-

	float				  m_fStartAcceleration;
	float				  m_fEndAccelaration;
	float				  m_fMaxSpeed;
	shared_ptr<kwMsg_Ani> m_pMsgAni;

private://내부에서 사용되는 정보...
	//이게 owner에서 실행되면서 owner를 실행시킴 명령이 끝나면 delete
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