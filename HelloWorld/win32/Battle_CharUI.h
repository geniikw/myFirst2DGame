#pragma once

#include"cocos2d.h"
#include"Animation.h"

using namespace cocos2d;

const CGPoint ACTIVE_POSITION = ccp(200,400);
enum MenuPosition
{
	MP_HIDE,
	MP_DOWN,
	MP_LEFT,
	MP_UP,
	MP_RIGHT,
	MP_ACTIVE
};

class Battle_Unit;

class Battle_CharUI : public CCSprite, public Animation
{
private:
	CGPoint	const *m_pCenterPosition;
	CGPoint		m_hidePostion;
	int			m_iMenuPostion;

private:

	Battle_Unit *m_pHeroUnit;
	CCSprite	*m_pHero;
	//끝인가?!
public:
	void setOwner(Battle_Unit* owner){ m_pHeroUnit = owner; }  //일달 설정만..
	Battle_CharUI(Battle_Unit *unit,CGPoint const *pCenter,const CGPoint &hidePosition);

	void tick(ccTime dt);

	virtual void doMenu(ccTime dt);
	virtual int getAniMaxFrame();

	CCSprite* getOwner(){ return m_pHero; }
	Battle_Unit *getUnitP(){ return m_pHeroUnit; }

public:
	void setMenuPosition(int mpIndex){ m_iMenuPostion = mpIndex; }
	int getMenuPosition(){ return m_iMenuPostion; }
};