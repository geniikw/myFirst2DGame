#include"My3DEllipse.h"

My3DEllipse::My3DEllipse(float r)
{
	m_fRadius = r;
}

void My3DEllipse::cc3dDraw()
{	
	static float r;
	r += 3.141592 / 180.f;
	ccDrawCircle(ccp(m_pos.x, m_pos.y), m_fRadius * getDisplayScale(), r, 25, true);
}