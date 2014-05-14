#include"kwOrderMoveToPoint.h"
#include"Battle_Unit.h"
#include<memory>

//필요한 것들은 이렇게 한당.
#include"kwMoving_Vector.h"
#include"kwMsg_Ani.h"

kwOrderMoveToPoint::kwOrderMoveToPoint(
	Battle_Unit *owner, 
	CG3Point dest, 
	float sa, float ea, 
	float speed, 
	shared_ptr<kwMsg_Ani> pMsgAni)
: kwOrder(owner)
{
	m_iPhase = 0;
	m_dest = dest;
	m_fStartAcceleration = sa;
	m_fEndAccelaration = ea;
	m_fMaxSpeed = speed;
	m_pMsgAni = pMsgAni;
	
	m_pMovingStragith = NULL;
}

bool kwOrderMoveToPoint::execute(ccTime dt)
{
	if (m_pOwner == NULL)
	{
		MessageBoxA(NULL, "owner가 없이 명령을 실행함.", "error", MB_OK);
		return true;
	}

	if (m_iProcess == OP_STANDBY)
	{	//초기화 작업
		m_iProcess = OP_EXECUTING;

		m_pMovingStragith = new kwMoving_Vector(m_pOwner, 0.f, m_pOwner->get3DPosition() >> m_dest);
		m_pOwner->setAniMsg(m_pMsgAni);
		m_pOwner->setMoving(m_pMovingStragith);
	}

	if (m_iPhase == 0)
	{
		m_pMovingStragith->addSpeed(m_fStartAcceleration*dt);
	}

	if (m_pMovingStragith->getSpeed() < m_fMaxSpeed && m_iPhase == 0)
	{
		m_pMovingStragith->setSpeed(m_fMaxSpeed);
		m_iPhase = 1;
	}
	
	CG3Point remain = m_dest - m_pOwner->get3DPosition();
	if (remain.getVectorLenght() < m_fMaxSpeed *m_fMaxSpeed / m_fEndAccelaration / 2 && m_iPhase == 1)
	{
		m_iPhase = 2;
	}

	if ( m_iPhase == 2 )
	{	
		m_pMovingStragith->addSpeed(-m_fEndAccelaration*dt);
	}

	if ( (m_pMovingStragith->getSpeed() < 5.f&&m_iPhase == 2) || remain.getVectorLenght() < 10.f)
	{	
		//m_pOwner->setPosition(m_dest);
		m_iProcess = OP_END;
		m_pOwner->setAniMsg(NULL);
		m_pOwner->setMoving(NULL);
		delete m_pMovingStragith;

		return true; //완료
	}

	return false;//명령이 완료되면 true를 리턴
}

kwOrder* kwOrderMoveToPoint::makekwOrderMoveToPoint(Battle_Unit *owner, const CG3Point &dest, float sa, float ea, float speed, shared_ptr<kwMsg_Ani> pMsgAni)
{
	kwOrder* move = new kwOrderMoveToPoint(owner,dest,sa,ea,speed,pMsgAni);
	return move;
}

