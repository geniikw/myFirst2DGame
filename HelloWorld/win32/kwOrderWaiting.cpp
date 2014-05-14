#include"kwOrderWaiting.h"
#include"Battle_Unit.h"
#include"kwMsg_Ani.h"

const kwMsg_Ani ANI_MSG_STAND = kwMsg_Ani(CAT_STAND, 0, 0,0, 0.1f);

kwOrderWaiting::kwOrderWaiting(Battle_Unit *owner, float waitTime, shared_ptr<kwMsg_Ani> pMsgAni)
:kwOrder(owner), m_pMsgAni(pMsgAni), m_fWaitTime(waitTime)
{
}

bool kwOrderWaiting::execute(ccTime dt)
{
	if (m_iProcess == OP_STANDBY)
	{
		m_pOwner->setAniMsg(m_pMsgAni);
		
		m_iProcess = OP_EXECUTING;
	}

	m_fWaitTime -= dt;
	if (m_fWaitTime < 0.f)
	{
		m_pOwner->setAniMsg(NULL);
		m_iProcess = OP_END;
		return true;
	}
	
	return false;
}

kwOrderWaiting* kwOrderWaiting::makeWaitOrder(Battle_Unit* owner, float waittime, int cat, int fs,int fr, int fe, float ft)
{
	kwOrderWaiting *pOrder = new kwOrderWaiting(owner,waittime, shared_ptr<kwMsg_Ani>(new kwMsg_Ani(cat,fs,fr,fe,ft)));
	return pOrder;
}