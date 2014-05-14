#include"kwMoving_Curve.h"

kwMoving_Curve::kwMoving_Curve(kwSprite *pOwner, CG3Point target, CG3Point vect, float speed, float rf)
:kwMoving(pOwner)
{
	
	m_vctStart = vect;
	m_fSpeed = speed;
	m_fRotFactor = rf;
}

void kwMoving_Curve::doMove(float dt)
{

}