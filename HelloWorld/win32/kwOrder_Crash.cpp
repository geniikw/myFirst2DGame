#include"kwOrder_Crash.h"
#include"Battle_Unit.h"
#include"kwMsg_Action.h"
#include"kwMsg_Ani.h"

#include"BackGroundSprite.h"

#include"Battle_AttackBox.h"



kwOrder_Crash::kwOrder_Crash(Battle_Unit* owner, CG3Point force, int damage, shared_ptr<kwMsg_Ani> pMsgAni)
:kwOrder(owner)
{
	m_vctForce = force;
	m_iDamage = damage;
	
	m_pMsgAni = pMsgAni;
	m_destPosition = CG3PointZero;
	m_fRemain = 1.f;
}

bool kwOrder_Crash::execute(ccTime dt)
{
	

	if (m_pOwner == NULL)
	{
		MessageBoxA(NULL, "owner가 없이 명령을 실행함.", "error", MB_OK);
		return true;
	}

	if (m_iProcess == OP_STANDBY)
	{
		m_iProcess = OP_EXECUTING;
		m_pOwner->setAniMsg(m_pMsgAni);
		m_destPosition = m_pOwner->get3DPosition() + m_vctForce;
	}

	CG3Point remain = m_destPosition - m_pOwner->get3DPosition();
	m_destPosition = m_destPosition + CG3Point(0.f, 0.f, -200.f * dt); //중력 적용;

	remain = m_pOwner->get3DPosition() + remain * 5 * dt;

	if (remain.z < 0.f)
	{
		remain.z = 0.f;
	}
	m_pOwner->getPosData()->setPosition(remain);
	m_fRemain -= dt;

	if (remain.z == 0.f && m_fRemain < 0.f)
	{
		//다 맞고나서 자기자리로 돌아감 
		m_pOwner->addOrder(kwOrderMoveToPoint::makekwOrderMoveToPoint(
			m_pOwner,
			m_pOwner->getinitPosition(), 100.f, 100.f, 200.f,
			shared_ptr<kwMsg_Ani>(new kwMsg_Ani(CAT_WALK, 0, 0, 0, 0.1f))));
		return true;
	}

	return false;
}

kwOrder_Crash* kwOrder_Crash::makeCrashOrder(
	Battle_Unit* owner,
	CG3Point force, int damage,
	shared_ptr<kwMsg_Ani> msgAni)

{
	kwOrder_Crash *p = new kwOrder_Crash(owner, force,damage, msgAni);
	return p;
}