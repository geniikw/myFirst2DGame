#include"kwOrderMakeBullet.h"
#include"kwMsg_Action.h"

#include"Battle_Unit.h"
#include"BackGroundSprite.h"

kwOrderMakeBullet::kwOrderMakeBullet(Battle_Unit *pOwner, shared_ptr<kwMsg_Action> pAction)
: kwOrder(pOwner), m_pActionMsg(pAction)
{
}

bool kwOrderMakeBullet::execute(ccTime dt)
{
	if (m_pOwner == NULL)
	{
		MessageBoxA(NULL, "owner�� ���� ����� ������.", "error", MB_OK);
		return true;
	}

	m_pActionMsg->m_iABFrame = setAbit(m_pActionMsg->m_iABFrame, m_pOwner->getCurFrame(), 0);
	m_pOwner->getParentMap()->requestUseAttackBox(m_pActionMsg, m_pOwner);
	
	return true; //�ð� �ٵǸ� ��� ����...
}
