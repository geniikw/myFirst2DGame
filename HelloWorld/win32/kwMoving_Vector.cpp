#include"kwMoving_Vector.h"

#include"kwSprite.h"
kwMoving_Vector::kwMoving_Vector(kwSprite* Owner, float speed, CG3Point vector)
: kwMoving(Owner)
{
	m_fSpeed = speed;
	m_UnitVector = vector;
}


void kwMoving_Vector::doMove(float dt)
{
	//이안에 틱에서는 owner를 단위 벡터만큼 이동 시킴
	m_pOwner->setPosition(m_pOwner->get3DPosition() + m_UnitVector * m_fSpeed * dt);

	if (m_UnitVector.x > 0.f)
	{
		m_pOwner->setFlipX(false);
	}
	else
	{
		m_pOwner->setFlipX(true);
	}

}