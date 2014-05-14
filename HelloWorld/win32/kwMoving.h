#pragma once
#include"Point.h"

class kwSprite;//ÀÛ¾÷ °´Ã¼.

class kwMoving
{
protected:
	kwSprite *m_pOwner;
	
public:
	kwMoving(kwSprite *Owner);

	void setOwner(kwSprite *Owner){ m_pOwner = Owner; }
	virtual bool doMove(float dt) = 0;
};