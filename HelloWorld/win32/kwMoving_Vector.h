#pragma once

#include"kwMoving.h"

class kwMoving_Vector : public kwMoving
{
	//벡터 방향으로 speed 만큼이동
	float    m_fSpeed;
	CG3Point m_UnitVector;

public:
	kwMoving_Vector(kwSprite* pOwner, float speed, CG3Point unitVector);
	void setSpeed(float speed){ m_fSpeed = speed; }
	void addSpeed(float add){ m_fSpeed = m_fSpeed + add; }

	CG3Point getVector(){ return m_UnitVector; }
	void setVector(CG3Point vect){ m_UnitVector = vect; }
	
	
	float getSpeed(){ return m_fSpeed; }
	void doMove(float dt);
};
