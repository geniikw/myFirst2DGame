#include"EffectSprite.h"

EffectSprite::EffectSprite()
{
	init();
	schedule(schedule_selector(EffectSprite::tick));
	this->setScale(0.5f);
}