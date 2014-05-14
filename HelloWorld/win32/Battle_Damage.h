#pragma once
#include"cocos2d.h"
#include"header.h"
using namespace cocos2d;

class Battle_Damage : public CCSprite
{
	//현재는 그냥 new-> delete 이긴 한데 그냥 전부 선언하는게 좋다고 함
	bool	  m_bIsUsed;
	ccColor3B m_color;
	CCSprite *m_pNumbers[G_MAX_DIGIT];

	//그리는 변수들
	float	m_fScaleY;
	float	m_fScaleX;

	//frame time
	float	m_fTimer;
	float	m_fOpacity;
	CGPoint m_Offset;

public:
	Battle_Damage();

	void setUp(CGPoint pos,int Damage,ccColor3B color);
	void tick(ccTime dt);

private:
	void init();
	CCAnimation* makeNumbersAnimation();
};