#include"kwOrderHit.h"
#include"Battle_Unit.h"
#include"kwMsg_Action.h"
#include"kwMsg_Ani.h"

#include"BackGroundSprite.h"

#include"Battle_Damage.h"

kwOrderHit::kwOrderHit(
	Battle_Unit* owner, 
	shared_ptr<kwMsg_Action> msgAttack, 
	shared_ptr<kwMsg_Ani> msgAni)
:kwOrder(owner)
{
	m_pMsgAttack = msgAttack;
	m_pMsgAni = msgAni;
	m_destPosition = CG3PointZero;
	m_fRemain = 1.f;
}

bool kwOrderHit::execute(ccTime dt)
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
		m_destPosition = m_pOwner->get3DPosition() + m_pMsgAttack->m_vctABforce;
		


		m_pMsgAttack = NULL;
	}

	CG3Point remain = m_destPosition - m_pOwner->get3DPosition();
	CG3Point rayCast;
	
	remain = remain * 5 * dt;

	rayCast = m_pOwner->getParentMap()->moveRayCast(*((My3DCube*)m_pOwner->getPosData()), remain, CT_OBJECT);


	CG3Point moving = m_pOwner->get3DPosition() + rayCast;
	
	m_destPosition = m_destPosition + CG3Point(0.f, 0.f,-300.f * dt); //중력 적용;
	
	if (moving.z < 0.f)
	{
		moving.z = 0.f;
	}

	m_pOwner->getPosData()->setPosition(moving);
	m_fRemain -= dt;

	if (abs(rayCast.x - remain.x) > 1.f)
	{

		moving = m_destPosition - m_pOwner->get3DPosition();
		moving.x = -moving.x;
		
		if (moving.x < 0.f)
			m_pOwner->damaged(CG3Point(-100, 0, 200), 20);
		else
			m_pOwner->damaged(CG3Point(100,0,200), 20);

		delete this;
	}

	if (moving.z == 0.f && m_fRemain < 0.f)
	{
		//다 맞고나서 자기자리로 돌아감 
		m_pOwner->addOrder(kwOrderMoveToPoint::makekwOrderMoveToPoint(
			m_pOwner, 
			m_pOwner->getinitPosition(),100.f,100.f,200.f,
			shared_ptr<kwMsg_Ani>(new kwMsg_Ani(CAT_WALK,0,0,0,0.1f))));
		return true;
	}

	return false;
}

kwOrderHit* kwOrderHit::makeHitOrder(
	Battle_Unit* owner, 
	shared_ptr<kwMsg_Action> msgAttack, 
	shared_ptr<kwMsg_Ani> msgAni)

{
	kwOrderHit *p = new kwOrderHit(owner,msgAttack,msgAni);
	return p;
}