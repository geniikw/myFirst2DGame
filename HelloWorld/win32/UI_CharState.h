#pragma once
#include"cocos2d.h"
using namespace cocos2d;

class UI_CharState : public CCSprite
{
	//위치 0일때 가운데 1왼쪽 2뒤 3오른쪽;
	int m_iNumber;
public:
	bool init();
	void tick(ccTime dt);

	float getMenuAngle();
	void setNumber(int index){ m_iNumber = index; }

};