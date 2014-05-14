#include"kwMoving_Target.h"
#include"kwSprite.h"

kwMoving_Target::kwMoving_Target(kwSprite *pOwner, kwSprite *pTarget, float speed)
: kwMoving(pOwner)
{
	m_pTarget = pTarget;
	m_fSpeed = speed;
}

void kwMoving_Target::doMove(float dt)
{
	m_pOwner->setPosition(m_pOwner->get3DPosition() + (*m_pOwner >> *m_pTarget) * m_fSpeed);
}