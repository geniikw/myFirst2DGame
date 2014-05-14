#include"Battle_CutEffect.h"
#include"Manager_Resource.h"
#include"Manager_Sound.h"

Battle_CutEffect::Battle_CutEffect(ccColor3B color)
{
	CCSprite::init();
	
	this->setColor(color);

	this->setDisplayFrame(Manager_Resource::getInstance()->getFrameWithString("cutEffect"));
	ccBlendFunc rf = { GL_SRC_ALPHA, GL_ONE };
	this->setBlendFunc(rf);
	
	Manager_Sound::shareClass()->Play_Cut();

	this->setRotation(rand() % 360);
	m_fYScale = 1.f;
}

void Battle_CutEffect::tick(ccTime dt)
{
	m_fYScale -= dt;
	setScaleY(m_fYScale);

	if (m_fYScale < 0.f)
	{
		getParent()->removeChild(this, true);
	}
}