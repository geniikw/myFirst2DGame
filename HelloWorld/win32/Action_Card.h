#pragma once
#include"cocos2d.h"
using namespace cocos2d;

class Action_Card : public CCSprite
{
	int		m_iCardNumber;
public:
	Action_Card(int CardNumber);
	void setCardAngle(float angle);
	void setCardNumber(int CardNumber);
	int getCardNumber()const { return m_iCardNumber; }
};