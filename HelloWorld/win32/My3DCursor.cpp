#include"My3DCursor.h"
#include"header.h"

My3DCursor::My3DCursor(float radius, float height)
{
	m_fRadius = radius;
	m_fHeight = height;
	m_fAngleOffset = 0.f;
}

void My3DCursor::cc3dDraw()
{
	refleshBuffer();
	drawCursor();
}

void My3DCursor::cc3dDrawInSP(const CGPoint &minus, const float &scale)
{
	refleshBuffer();
	for (int n = 0; n < 6; n++)
	{
		drawBufferPoint[n] -= minus;
		drawBufferPoint[n] /= scale;
	}
	drawCursor();
}

void My3DCursor::refleshBuffer()
{

	static float a1;
	static float a2;
	static float a3;
	static float a4;
	static float a5;

	a1 = m_fAngleOffset * 3.141592f / 180.f;
	a2 = (360.f / 5.f * 1.f + m_fAngleOffset)* 3.141592f / 180.f;
	a3 = (360.f / 5.f * 2.f + m_fAngleOffset)* 3.141592f / 180.f;
	a4 = (360.f / 5.f * 3.f + m_fAngleOffset)* 3.141592f / 180.f;
	a5 = (360.f / 5.f * 4.f + m_fAngleOffset)* 3.141592f / 180.f;

	drawBufferPoint[0] = transDisplayPosition(m_pos.x, m_pos.y, m_pos.z);
	drawBufferPoint[1] = transDisplayPosition(m_pos.x + m_fRadius * cos(a1), m_pos.y + m_fRadius * sin(a1) * 0.5, m_pos.z + m_fHeight);
	drawBufferPoint[2] = transDisplayPosition(m_pos.x + m_fRadius * cos(a2), m_pos.y + m_fRadius * sin(a2)* 0.5, m_pos.z + m_fHeight);
	drawBufferPoint[3] = transDisplayPosition(m_pos.x + m_fRadius * cos(a3), m_pos.y + m_fRadius * sin(a3)* 0.5, m_pos.z + m_fHeight);
	drawBufferPoint[4] = transDisplayPosition(m_pos.x + m_fRadius * cos(a4), m_pos.y + m_fRadius * sin(a4)* 0.5, m_pos.z + m_fHeight);
	drawBufferPoint[5] = transDisplayPosition(m_pos.x + m_fRadius * cos(a5), m_pos.y + m_fRadius * sin(a5)* 0.5, m_pos.z + m_fHeight);
}

void My3DCursor::drawCursor()
{
	ccDrawPoly(drawBufferPoint+1, 5, true);
	ccDrawLine(drawBufferPoint[0], drawBufferPoint[1]);
	ccDrawLine(drawBufferPoint[0], drawBufferPoint[2]);
	ccDrawLine(drawBufferPoint[0], drawBufferPoint[3]);
	ccDrawLine(drawBufferPoint[0], drawBufferPoint[4]);
	ccDrawLine(drawBufferPoint[0], drawBufferPoint[5]);
}
