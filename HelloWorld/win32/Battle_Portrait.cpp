#include"Battle_Portrait.h"
#include"header.h"
#include"Manager_Resource.h"
#include"Battle_Unit.h"

Battle_Portrait::Battle_Portrait()
{
	CCSprite::init();

	m_pUnit = NULL;
	
	CCTexture2D *portaits = Manager_Resource::getInstance()->getResourceWithString("portrait");
	
	CCAnimation *pPA = new CCAnimation;
	pPA->initWithName("IDPicture");
	
	m_pFace = new CCSprite;
	m_pFace->autorelease();
	m_pFace->init();
	m_pFace->setAnchorPoint(ccp(0, 1));
	m_pFace->setScale(0.3f);
	this->setAnchorPoint(ccp(0, 1));
	pPA->addFrameWithTexture(portaits, CGRect(0, 0, 1, 1));
	for (int n = 0; n < MAX_CHARACTER_NUMBER + 1; n++)
	{
		pPA->addFrameWithTexture(portaits, CGRect(226 * (n % 8), (n / 8) * 482, 225, 260));
	}
	m_pFace->addAnimation(pPA);
	this->addChild(m_pFace);


	CCSprite *pSP = CCSprite::spriteWithSpriteFrame(Manager_Resource::getInstance()->getFrameWithString("portFrame"));
	pSP->setAnchorPoint(ccp(0, 0));
	pSP->setPosition(ccp(0, -80));
	this->addChild(pSP);
	pSP = CCSprite::spriteWithSpriteFrame(Manager_Resource::getInstance()->getFrameWithString("UICharFrame"));
	pSP->setAnchorPoint(ccp(0, 0));
	pSP->setPosition(ccp(15, -90));
	this->addChild(pSP);


	m_pGauge[0] = CCSprite::spriteWithSpriteFrame(Manager_Resource::getInstance()->getFrameWithString("UIgauge4"));
	m_pGauge[1] = CCSprite::spriteWithSpriteFrame(Manager_Resource::getInstance()->getFrameWithString("UIgauge3"));
	m_pGauge[2] = CCSprite::spriteWithSpriteFrame(Manager_Resource::getInstance()->getFrameWithString("UIgauge2"));
	m_pGauge[3] = CCSprite::spriteWithSpriteFrame(Manager_Resource::getInstance()->getFrameWithString("UIgauge1"));

	for (int n = 0; n < 4 ; n++)
	{
		m_pGauge[n]->setAnchorPoint(ccp(0, 0));
		m_pGauge[n]->setPosition(ccp(15, -90));
		addChild(m_pGauge[n]);
	}

	schedule(schedule_selector(Battle_Portrait::tick));
}

void Battle_Portrait::setUnit(Battle_Unit *pChar)
{
	m_pUnit = pChar;
	m_pFace->setDisplayFrame("IDPicture", pChar->getCharacterName());
}

void Battle_Portrait::tick(ccTime dt)
{
	int count = m_pUnit->getActionCount();

	for (int n = 0; n < 4; n++)
	{
		if (count < n+1)
			m_pGauge[n]->setColor(ccc3(255, 255, 255));
		else
			m_pGauge[n]->setColor(ccc3(50, 255, 0));	
	}
}