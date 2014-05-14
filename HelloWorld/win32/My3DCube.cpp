#include"My3DCube.h"
#include"header.h"
/*

display this shape;
   /───/											
  /│   /│                                                 
┌──┐	 │
│ /─│─/
│/	.│/         '.' : center point
└──┘

bottom plot
┌──┐      
│ . │      
└──┘
*/

My3DCube::My3DCube(CG3Point size)
{
	m_size = size;
	setAnchor(CG3Point(0.5f, 0.5f, 0));
	refleshBuffer(); //초기값 세팅
}
float My3DCube::getRadius()
{
	float ax = m_Anchor.x < 0.5 ? 1 - m_Anchor.x : m_Anchor.x;
	float ay = m_Anchor.y < 0.5 ? 1 - m_Anchor.y : m_Anchor.y;
	float az = m_Anchor.z < 0.5 ? 1 - m_Anchor.z : m_Anchor.z;
	
	//이 길이..
	return sqrtf(square(m_size.x* ax) + square(m_size.y * ay) + square(m_size.z *az));
}

void My3DCube::cc3dDraw()
{	
	refleshBuffer();

	drawCube();
}

void My3DCube::cc3dDrawInSP(const CGPoint &minus, const float &scale)
{
	refleshBuffer();
	
	for (int n = 0; n < 8; n++)
	{
		drawBufferPoint[n] -= minus;
		drawBufferPoint[n] /= scale;
	}

	
	
	if (m_size.x == 0.f)
	{
		drawRectXZ();
		return;
	}
	else if (m_size.y == 0.f)
	{
		drawRectYZ();
		return;
	}
	else if (m_size.z == 0.f)
	{
		drawRectXY();
		return;
	}
	drawCube();
}

void My3DCube::refleshBuffer()
{
	if (m_pMapData == NULL)
		return;
	
	drawBufferPoint[0] = transDisplayPosition(m_pos.x - m_size.x * (m_Anchor.x)		 , m_pos.y - m_size.y * (m_Anchor.y)	  , m_pos.z);
	drawBufferPoint[1] = transDisplayPosition(m_pos.x + m_size.x * (1.f - m_Anchor.x), m_pos.y - m_size.y * (m_Anchor.y)	  , m_pos.z);
	drawBufferPoint[2] = transDisplayPosition(m_pos.x + m_size.x * (1.f - m_Anchor.x), m_pos.y + m_size.y * (1.f - m_Anchor.y), m_pos.z);
	drawBufferPoint[3] = transDisplayPosition(m_pos.x - m_size.x * (m_Anchor.x)		 , m_pos.y + m_size.y * (1.f - m_Anchor.y), m_pos.z);
	drawBufferPoint[4] = transDisplayPosition(m_pos.x - m_size.x * (m_Anchor.x)		 , m_pos.y + m_size.y * (1.f - m_Anchor.y), m_pos.z + m_size.z);
	drawBufferPoint[5] = transDisplayPosition(m_pos.x + m_size.x * (1.f - m_Anchor.x), m_pos.y + m_size.y * (1.f - m_Anchor.y), m_pos.z + m_size.z);
	drawBufferPoint[6] = transDisplayPosition(m_pos.x + m_size.x * (1.f - m_Anchor.x), m_pos.y - m_size.y * (m_Anchor.y)	  , m_pos.z + m_size.z);
	drawBufferPoint[7] = transDisplayPosition(m_pos.x - m_size.x * (m_Anchor.x)		 , m_pos.y - m_size.y * (m_Anchor.y)	  , m_pos.z + m_size.z);
}

void My3DCube::drawCube()
{
	ccDrawPoly(drawBufferPoint, 8, true);
	ccDrawLine(drawBufferPoint[0], drawBufferPoint[3]);
	ccDrawLine(drawBufferPoint[4], drawBufferPoint[7]);
	ccDrawLine(drawBufferPoint[1], drawBufferPoint[6]);
	ccDrawLine(drawBufferPoint[2], drawBufferPoint[5]);
}

void My3DCube::drawRectXY()
{
	ccDrawPoly(drawBufferPoint, 4, true);
}

void My3DCube::drawRectYZ()
{
	ccDrawLine(drawBufferPoint[0], drawBufferPoint[1]);
	ccDrawLine(drawBufferPoint[1], drawBufferPoint[6]);
	ccDrawLine(drawBufferPoint[6], drawBufferPoint[7]);
	ccDrawLine(drawBufferPoint[7], drawBufferPoint[0]);
}

void My3DCube::drawRectXZ()
{
	ccDrawLine(drawBufferPoint[0], drawBufferPoint[3]);
	ccDrawLine(drawBufferPoint[3], drawBufferPoint[4]);
	ccDrawLine(drawBufferPoint[4], drawBufferPoint[7]);
	ccDrawLine(drawBufferPoint[7], drawBufferPoint[0]);
}

CG3Point My3DCube::getOrigin() const
{
	return m_pos - m_size * m_Anchor;
}