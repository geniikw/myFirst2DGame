#pragma once

#include"MYUnit.h"



class My3DCursor : public MYUnit
{
	float	m_fRadius;
	float	m_fHeight;
	float	m_fAngleOffset;
	CGPoint drawBufferPoint[6];

private:
	float	m_fSinHeight;

public:
	My3DCursor(float radius, float height);

	virtual void cc3dDraw();
	virtual void cc3dDrawInSP(const CGPoint &minus, const float &scale);

public:
	void refleshBuffer();
	void drawCursor();

	void addAngle(float angle){ m_fAngleOffset += angle; }
};