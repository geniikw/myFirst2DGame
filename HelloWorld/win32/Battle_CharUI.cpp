#include"Battle_CharUI.h"

#include"Battle_Unit.h"
#include"Manager_Resource.h"
#include"Manager_Global.h"

const CGPoint CHARMENU_HERO_POSITION = ccp(250, 10);

#include"Battle_Portrait.h"
#include"Action_Card.h"

Battle_CharUI::Battle_CharUI(Battle_Unit *unit, CGPoint const *pCenter, const CGPoint &hidePosition)
{
	this->initWithSpriteFrame(Manager_Resource::getInstance()->getFrameWithString("CharMenu"));

	m_pHeroUnit = unit;

	m_pCenterPosition = pCenter;
	m_hidePostion = hidePosition;
	
	static int n = 0;
	m_iMenuPostion = n++;

	m_pHero = new CCSprite;
	m_pHero->init();
	m_pHero->autorelease();
	m_pHero->setAnchorPoint(ccp(0.5, 0));
	m_pHero->addAnimation(m_pHeroUnit->animationByName("IDLE"));
	m_pHero->setPosition(CHARMENU_HERO_POSITION);

	schedule(schedule_selector(Battle_CharUI::tick));

	this->addChild(m_pHero);
}

void Battle_CharUI::tick(ccTime dt)
{
	doAni(dt);
	doMenu(dt);
}

void Battle_CharUI::doMenu(ccTime dt)
{
	CGPoint dif;
	float y;
	switch (m_iMenuPostion)
	{
		case MP_DOWN:
		dif = *m_pCenterPosition + ccp(160 * cosf(3.f*3.14f / 2.f), (30 * sinf(3.f*3.14f / 2.f))) - this->getPosition();
		break;
		case MP_LEFT:
		dif = *m_pCenterPosition + ccp(160 * cosf(0*3.14f / 2.f), (30 * sinf(0*3.14f / 2.f))) - this->getPosition();
		break;
		case MP_UP:
		dif = *m_pCenterPosition + ccp(160 * cosf(1*3.14f / 2.f), (30 * sinf(1*3.14f / 2.f))) - this->getPosition();
		break;
		case MP_RIGHT:
		dif = *m_pCenterPosition + ccp(160 * cosf(2*3.14f / 2.f), (30 * sinf(2*3.14f / 2.f))) - this->getPosition();
		break;
		case MP_HIDE:
		dif = m_hidePostion - this->getPosition();
		break;
		case MP_ACTIVE:
		dif = ACTIVE_POSITION - this->getPosition();
		break;
	}

	y = max(370, this->getPosition().y);
	this->setOpacity(255 - (1 - 370 / y));
	this->setScale(370 / y - (1 - (370 / y)) * 2);
	this->setPosition(this->getPosition() + dif*5.f*dt);
	getParent()->reorderChild(this, EZ_UI -y);
}

int Battle_CharUI::getAniMaxFrame()
{
	return m_pHero->animationByName(GA(m_iCAT))->getFrames()->count();
}
