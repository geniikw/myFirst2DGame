#pragma once
#include"cocos2d.h"
using namespace cocos2d;

#include"kwSprite.h"
class Object_Char : public kwSprite
{
public:

	CG3Point getOrigin(){ return m_pPosData->getOrigin(); }

	bool init();
	void tick(ccTime dt);
};