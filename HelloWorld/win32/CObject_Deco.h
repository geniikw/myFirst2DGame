#pragma once
#include"cocos2d.h"
using namespace cocos2d;

#include"Object_header.h"

//캐릭터나 다른 무언가에 붙어서 사용됨 악세서리 같은걸 붙임
//칼같은거라던가...-_- 


class CObject_Deco : public CCSprite
{
	string m_szWhat;
	CGPoint m_PointOffset;
	//기본치는 0...
	CGPoint m_PointMoving;
	float m_fAngle;

public:
	bool init();
	bool initWithTextureName(string name);

	void tick(float dt);
};