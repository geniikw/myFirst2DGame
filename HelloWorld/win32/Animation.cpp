#include"Animation.h"
#include"kwMsg_Ani.h"

Animation::Animation()
{
	m_iCAT = CAT_STAND;
	m_iFrameStartIndex = 0;
	
	m_iFrameRepeatIndex = 0;
	m_iFrameEndIndex = 0;
	
	m_fFrameMaxTime = 0.2f;
	m_iCurFrame = 0;
	m_fFrametime = 0.f;
}


void Animation::setAniMsg(shared_ptr<kwMsg_Ani> msg)	
{
	if (msg != NULL)
	{
		m_iCAT = msg->m_iCAT;
		m_iFrameStartIndex = msg->m_iFrameStartIndex;

		if (msg->m_iFrameEndIndex == 0 || msg->m_iFrameEndIndex > getAniMaxFrame())
			m_iFrameEndIndex = getAniMaxFrame()-1;
		else
			m_iFrameEndIndex = msg->m_iFrameEndIndex;

		m_fFrameMaxTime = msg->m_fFrameMaxTime;
		m_iCurFrame = m_iFrameStartIndex;
		m_iFrameRepeatIndex = msg->m_iFrameRepeatIndex;
	}
	else
	{
		m_iCAT = CAT_STAND;
		m_iFrameStartIndex = 0;
		m_iFrameRepeatIndex = 0;
		m_iFrameEndIndex = 0;
		m_fFrameMaxTime = 0.1f;
		m_iCurFrame = 0;
		m_fFrametime = 0.f;
	}


	m_fFrametime = 0.f;
}

char const* Animation::getAnimationString(int CAT)
{
	char const * temp;
	switch (CAT)
	{
		case CAT_STAND:  return temp = "IDLE"; break;
		case CAT_WALK:	 return temp = "WALK"; break;
		case CAT_RUN:return temp = "RUN"; break;
		case CAT_BACK:return temp = "BACK"; break;
		case CAT_ATTACK1:return temp = "ATTACK1"; break;
		case CAT_ATTACK2:return temp = "ATTACK2"; break;
		case CAT_ATTACK3:return temp = "ATTACK3"; break;
		case CAT_ATTACK4:return temp = "ATTACK4"; break;
		case CAT_ATTACK5:return temp = "ATTACK5"; break;
		case CAT_GUARD:return temp = "GAURD"; break;
		case CAT_HIT:return temp = "HIT"; break;
	}		 
	return temp;
}

void Animation::doAni(ccTime dt)
{
	if (m_iFrameEndIndex == 0)
		m_iFrameEndIndex = getAniMaxFrame()-1;

	m_fFrametime += dt;
	if (m_fFrameMaxTime < m_fFrametime)
	{
		m_fFrametime = 0.f;
		m_iCurFrame++;

		if (m_iCurFrame > m_iFrameEndIndex)
		{
			m_iCurFrame = m_iFrameRepeatIndex;
		}
	}
	getOwner()->setDisplayFrame(GA(m_iCAT), m_iCurFrame);
}