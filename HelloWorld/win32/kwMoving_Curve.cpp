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


	//�ʱ� ���ͷκ��� �������� ��ǥ���� ���� ���ͷ� ȸ���� �Ѵ�...-_-?

	//���� ��ǥ������ ����... true�� ����??

	return false;
}