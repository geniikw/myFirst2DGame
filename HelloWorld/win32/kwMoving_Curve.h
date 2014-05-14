#pragma once

#include"kwMoving.h"

class kwMoving_Curve : public kwMoving
{
	CG3Point		m_vctStart;		//ó�� ����Ű�� ����
	CG3Point		m_posTarget;    //Ÿ���� ��ġ...
	
	float			m_fSpeed;
	float			m_fRotFactor;   ///ȸ�� ���
	float			m_fRotYZRatio;  //�� ���� 1�̸� y�����θ� ȸ�� // 0�̸� z�����θ� ȸ��		
public:

	kwMoving_Curve(kwSprite *pOwner, CG3Point posTarget, CG3Point vect, float speed, float rf,float rr);
	bool doMove(float dt);
};