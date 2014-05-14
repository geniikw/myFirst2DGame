#pragma once
#include"kwMoving.h"

class kwMoving_Target : public kwMoving
{
	kwSprite *m_pTarget;
	float	  m_fSpeed;

public:

	kwMoving_Target(kwSprite *pOwner,kwSprite *pTarget,float speed);
	void setSpeed(float speed){ m_fSpeed = speed; }
	bool doMove(float dt);
};