#pragma once


#include"cocos2d.h"

using namespace cocos2d;


class Battle_ATB : public CCSprite
{
	CCSprite *m_pProgressImage;
	float  m_fProgressTime;
	float  m_fFlipColor;

	bool		m_bReduce;


public:

	Battle_ATB();
	float& getProgressRef(){ return m_fProgressTime; }
	void tick(ccTime dt);//무늬만 설정하자.


	bool reduceTick(ccTime dt);

};