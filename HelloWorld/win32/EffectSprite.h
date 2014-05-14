#pragma once
#include"cocos2d.h"
using namespace cocos2d;

class EffectSprite : public CCSprite
{

public:
	EffectSprite();
	virtual void tick(ccTime dt) = 0;
};