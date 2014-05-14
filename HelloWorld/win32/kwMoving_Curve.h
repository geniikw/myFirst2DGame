#pragma once

#include"kwMoving.h"

class kwMoving_Curve : public kwMoving
{
	CG3Point		m_vctStart;		//처음 가리키는 방향
	CG3Point		m_posTarget;    //타겟의 위치...
	
	float			m_fSpeed;
	float			m_fRotFactor;   ///회전 계수
	float			m_fRotYZRatio;  //이 값이 1이면 y축으로만 회전 // 0이면 z축으로만 회전		
public:

	kwMoving_Curve(kwSprite *pOwner, CG3Point posTarget, CG3Point vect, float speed, float rf,float rr);
	bool doMove(float dt);
};