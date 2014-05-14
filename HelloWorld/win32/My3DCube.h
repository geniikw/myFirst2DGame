#pragma once
#include"MYUnit.h"

class My3DCube : public MYUnit
{
	CG3Point m_size;
public:
	CG3Point getSize(){ return m_size; }

private: //displayData buffer;
	CGPoint drawBufferPoint[8];

public:
	My3DCube(){ ; }
	explicit My3DCube(CG3Point size);
	~My3DCube(){ ; }

	virtual inline CG3Point getOrigin() const;
	virtual void cc3dDraw();
	virtual inline float getRadius();
	virtual void cc3dDrawInSP(const CGPoint &minus, const float &scale);
	//??
public ://내부 virtual 함수 //충돌할 때 필요...
	virtual float MYUnitGetMaxX() const{ return getOrigin().x + m_size.x; }
	virtual float MYUnitGetMaxY() const{ return getOrigin().y + m_size.y; }
	virtual float MYUnitGetMaxZ() const{ return getOrigin().z + m_size.z; }
	virtual float MYUnitGetMinX() const{ return getOrigin().x; }
	virtual float MYUnitGetMinY() const{ return getOrigin().y; }
	virtual float MYUnitGetMinZ() const{ return getOrigin().z; }

	virtual float getXLength(){ return m_size.x; }
	virtual float getYLength(){ return m_size.y; }
	virtual float getZLength(){ return m_size.z; }

private://내부 함수
	void refleshBuffer();
	void drawCube();
	void drawRectXY();
	void drawRectYZ();
	void drawRectXZ();
};