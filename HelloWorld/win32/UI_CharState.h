#pragma once
#include"cocos2d.h"
using namespace cocos2d;

class UI_CharState : public CCSprite
{
	//��ġ 0�϶� ��� 1���� 2�� 3������;
	int m_iNumber;
public:
	bool init();
	void tick(ccTime dt);

	float getMenuAngle();
	void setNumber(int index){ m_iNumber = index; }

};