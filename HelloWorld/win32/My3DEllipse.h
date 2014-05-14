#pragma once
#include"cocos2d.h"
using namespace cocos2d;

#include"MYUnit.h"

class My3DEllipse : public MYUnit
{//
protected:
	float m_fRadius;

public:
	My3DEllipse(){ ; }
	My3DEllipse(float r);

	virtual void cc3dDraw();
	virtual float getRadius(){ return m_fRadius; }
private://내부 함수

};