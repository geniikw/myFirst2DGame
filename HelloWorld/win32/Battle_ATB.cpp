#include"Battle_ATB.h"

#include"Manager_Resource.h"

Battle_ATB::Battle_ATB()
{
	init();
	m_pProgressImage = CCSprite::spriteWithSpriteFrame(Manager_Resource::getInstance()->getFrameWithString("ATBar"));
	this->addChild(m_pProgressImage, 1);

	m_pProgressImage->setColor(ccc3(150, 200, 0));
	this->setColor(ccc3(51, 51, 51));
	this->setDisplayFrame(Manager_Resource::getInstance()->getFrameWithString("ATBar"));

	static int temp = 0;  //¾Æ ¸ô¶ó ±ÞÇØ ¤Ì¤Ì
	if (temp == 0)
	{
		m_pProgressImage->setAnchorPoint(ccp(0, 0));
		
	}
	else
	{
		m_pProgressImage->setAnchorPoint(ccp(1, 0));
		m_pProgressImage->setPosition(ccp(120, 0));
	}
	temp++;
	m_fProgressTime = 0.f;
	m_fFlipColor = 0.f;
	m_bReduce = false;
	schedule(schedule_selector(Battle_ATB::tick));
}


void Battle_ATB::tick(ccTime dt)
{
	m_pProgressImage->setColor(ccc3(150 + m_fFlipColor, 100 + m_fProgressTime, 0));
	
	m_fFlipColor += dt * 20.f;
	if (m_fFlipColor > 10.f)
		m_fFlipColor = 0.f;

	m_pProgressImage->setScaleX(m_fProgressTime / 100.f);
	
}

bool Battle_ATB::reduceTick(ccTime dt)
{
	m_fProgressTime -= dt * 5;

	if (m_fProgressTime < 0.f)
	{
		m_bReduce = false;
		return true;
	}

	return false;
}