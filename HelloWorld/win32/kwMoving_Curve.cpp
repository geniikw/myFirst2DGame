#include"kwMoving_Curve.h"

kwMoving_Curve::kwMoving_Curve(kwSprite *pOwner, CG3Point target, CG3Point vect, float speed, float rf,float rr)
:kwMoving(pOwner)
{
	m_vctStart = vect;
	m_fSpeed = speed;
	m_fRotFactor = rf;
	m_fRotYZRatio = rr;
}

void kwMoving_Curve::doMove(float dt)
{
	//만약 목표지점에 가면... 
}