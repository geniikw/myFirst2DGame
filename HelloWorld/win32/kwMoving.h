#pragma once
#include"Point.h"

class kwSprite;//�۾� ��ü.

class kwMoving
{
protected:
	kwSprite *m_pOwner;
	
public:
	kwMoving(kwSprite *Owner);

	void setOwner(kwSprite *Owner){ m_pOwner = Owner; }
	virtual bool doMove(float dt) = 0;
};