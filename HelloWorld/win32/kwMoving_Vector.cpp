#include"kwMoving_Vector.h"

#include"kwSprite.h"
kwMoving_Vector::kwMoving_Vector(kwSprite* Owner, float speed, CG3Point vector)
: kwMoving(Owner)
{
	m_fSpeed = speed;
	m_UnitVector = vector;
}


bool kwMoving_Vector::doMove(float dt)
{
	//�̾ȿ� ƽ������ owner�� ���� ���͸�ŭ �̵� ��Ŵ
	m_pOwner->setPosition(m_pOwner->get3DPosition() + m_UnitVector * m_fSpeed * dt);

	if (m_UnitVector.x > 0.f)
	{
		m_pOwner->setFlipX(false);
	}
	else
	{
		m_pOwner->setFlipX(true);
	}
	return false; // vector ������ �Ϸᰡ �ʿ��� ������ �ƴ϶� ������ false�� ������.

}