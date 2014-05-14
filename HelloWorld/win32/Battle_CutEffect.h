#pragma once
#include"EffectSprite.h"

#include"header.h"
using namespace cocos2d;

class Battle_CutEffect : public EffectSprite
{
	float m_fYScale;

public:
	Battle_CutEffect(ccColor3B color);
	void tick(ccTime dt);
};