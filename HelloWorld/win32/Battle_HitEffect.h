#pragma once

#include"EffectSprite.h"


class Battle_HitEffect : public EffectSprite
{
	float		m_fMaxFrameTime;
	float		m_fFrameTime;
	int			m_iCurFrame;
public:
	Battle_HitEffect();
	void tick(ccTime dt);
};