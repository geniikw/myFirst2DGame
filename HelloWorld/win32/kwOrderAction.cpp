#include"kwOrderAction.h"

#include"kwMsg_Action.h"
#include"Battle_Unit.h"
#include"BackGroundSprite.h"
//#include"header.h"

kwOrderAction::kwOrderAction(
	Battle_Unit *owner,
	shared_ptr<kwMsg_Action> pMsgAction,
	shared_ptr<kwMsg_Ani> pMsgAni)
	: 
	kwOrder(owner), 
	m_pActionMsg(pMsgAction),
	m_pAniMsg(pMsgAni)
{
	//초기화 예제  kwOrderAction(pOwner,new kwMsg_Action(...),new kwMsg_Ani(...));
}
kwOrderAction::~kwOrderAction()
{

}

bool kwOrderAction::execute(ccTime dt)
{
	if (m_pOwner == NULL)
	{
		MessageBoxA(NULL, "owner가 없이 명령을 실행함.", "error", MB_OK);
		return true;
	}

	if (m_iProcess == OP_STANDBY)
	{
		m_iProcess = OP_EXECUTING;
		m_pOwner->setAniMsg(m_pAniMsg);
		m_pOwner->setMoving(m_pActionMsg->m_pOwnerMoving);




		if (m_pOwner->get3DPosition().x < m_pActionMsg->m_pTarget->get3DPosition().x)
			m_pOwner->setFlipX(false);
		else
			m_pOwner->setFlipX(true);

	}
	//어택박스를 만든다.
	if (analyzeCInt(m_pActionMsg->m_iABFrame, m_pOwner->getCurFrame()))
	{
		//해당하는 비트를 0으로 만든다. (이중 실행 방지)
		m_pActionMsg->m_iABFrame = setAbit(m_pActionMsg->m_iABFrame, m_pOwner->getCurFrame(), 0);
		m_pOwner->getParentMap()->requestUseAttackBox(m_pActionMsg, m_pOwner);
	}
	//if (m_pAttackMsg->m_fActionTime < 0.f)
	if (m_pOwner->getCurFrame() == m_pOwner->getAniMaxFrame()-1)
	{
		m_iProcess = OP_END;
		m_pOwner->setAniMsg(NULL);
		m_pOwner->setMoving(NULL);

		return true; //시간 다되면 명령 종료...
	}
	return false;
}

kwOrderAction* kwOrderAction::makeActionOrder(
	Battle_Unit *owner,
	shared_ptr<kwMsg_Action> pMsgAction,
	shared_ptr<kwMsg_Ani> pMsgAni)
{
	kwOrderAction *p = new kwOrderAction(owner, pMsgAction, pMsgAni);
	return p;
}