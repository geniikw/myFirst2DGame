#pragma once
#include"kwSprite.h"
#include"kwController.h"
#include"Manager_Global.h"

class BackGroundSprite;

class Battle_Cursor : public kwSprite
{
	kwSprite *m_pTarget;
	float		m_fSinValue;
public:
	void setTarget(kwSprite* target);
	CG3Point getTargetPosition(){ return m_pTarget->get3DPosition(); }

public:
	Battle_Cursor(float radius, float height);

	virtual void draw(){
		//kwSprite::draw();
		CCSprite::draw();
		if (m_pPosData != NULL)
		{
			m_pPosData->cc3dDrawInSP(getPosition() - Manager_Global::getInstance()->g_offsetGameScroll, getScale());
		}
	}


public:
	void tick(ccTime dt);
};