#include"Object_MiniCube.h"
bool Object_MiniCube::init()
{
	if (!kwSprite::init(10, 10, 10)) return false;

	static float angle = 0;
	m_fAngle = angle;
	angle += 10.f;
	setTag(CT_OBJECT);
	schedule(schedule_selector(Object_MiniCube::tick));
	return true;
}

void Object_MiniCube::tick(ccTime dt)
{
	float x = 320.f + 300.f*cos(m_fAngle);
	float y = 30.f + 70.f*sin(m_fAngle);
	m_fAngle += dt*1.f;

	m_pPosData->setPosition(CG3Point(x, y, 300));
}