#include"Object_Char.h"
bool Object_Char::init()
{
	if (!kwSprite::init(50,5,40))return false;

	schedule(schedule_selector(Object_Char::tick));


	m_pPosData->setAnchor(CG3Point(0.5f, 0.5f, 0.f));
	this->setAnchorPoint(ccp(0.f, 0));
	return true;
}

void Object_Char::tick(ccTime dt)
{
	if (GetAsyncKeyState(VK_UP))
	{
		addPosition(CG3Point(0.f,0.f, 100 * dt));
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		addPosition(CG3Point(0.f,0.f,-100 * dt));
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		addPosition(CG3Point(100 * dt,0.f, 0.f));
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		addPosition(CG3Point(-100 * dt, 0.f, 0.f));
	}
}