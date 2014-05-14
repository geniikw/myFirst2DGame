#include"kwMoving_Curve.h"

#include"Battle_Unit.h"

kwMoving_Curve::kwMoving_Curve(kwSprite *pOwner, CG3Point target, CG3Point vect, float speed, float rf,float rr)
:kwMoving(pOwner)
{
	m_vctStart = vect;
	m_fSpeed = speed;
	m_fRotFactor = rf;
	m_fRotYZRatio = rr;
}

bool kwMoving_Curve::doMove(float dt)
{
	m_pOwner->setPosition(m_pOwner->get3DPosition() + m_vctStart * m_fSpeed * dt);


	//초기 백터로부터 현제점과 목표점에 대한 벡터로 회전를 한다...-_-?

	//만약 목표지점에 가면... true를 리턴??

	return false;
}