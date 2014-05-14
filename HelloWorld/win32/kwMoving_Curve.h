#pragma once

#include"kwMoving.h"

class kwMoving_Curve : public kwMoving
{
	CG3Point		m_vctStart;		//ó�� ����Ű�� ����
	CG3Point		m_posTarget;    //Ÿ���� ��ġ...
	
	float			m_fSpeed;
	float			m_fRotFactor;  ///ȸ�� ���
		
public:

	kwMoving_Curve(kwSprite *pOwner, CG3Point pTarget, CG3Point vect, float speed, float rf);
	void doMove(float dt);
};