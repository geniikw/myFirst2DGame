#include"Battle_HitEffect.h"
#include"Manager_Resource.h"
#include"Manager_Sound.h"

Battle_HitEffect::Battle_HitEffect()
{
	CCTexture2D *p = Manager_Resource::getInstance()->getResourceWithString("hitEffect");
	CCAnimation *pAni = new CCAnimation;
	pAni->initWithName("hit");

	for (int n = 0; n < 20; n++)
	{
		pAni->addFrameWithTexture(p, CGRect( (n%10) * 134, n/11 *145, 128, 128));
	}
	this->addAnimation(pAni);

	Manager_Sound::shareClass()->Play_Blow();

	m_fMaxFrameTime = 0.005f;
	m_iCurFrame = 0;
	m_fFrameTime = 0.f;
}

void Battle_HitEffect::tick(ccTime dt)
{
	setDisplayFrame("hit", m_iCurFrame);
	ccBlendFunc rf = { GL_SRC_ALPHA, GL_ONE };
	this->setBlendFunc(rf);
	
	m_fFrameTime += dt;
	if (m_fFrameTime > m_fMaxFrameTime)
	{
		m_fFrameTime = 0.f;
		m_iCurFrame++;
	}
	if (m_iCurFrame == this->animationByName("hit")->getFrames()->count())
	{
		getParent()->removeChild(this, true);
	}
}
