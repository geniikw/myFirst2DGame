#pragma once
#include"cocos2d.h"
using namespace cocos2d;

#include"Object_header.h"

//ĳ���ͳ� �ٸ� ���𰡿� �پ ���� �Ǽ����� ������ ����
//Į�����Ŷ����...-_- 


class CObject_Deco : public CCSprite
{
	string m_szWhat;
	CGPoint m_PointOffset;
	//�⺻ġ�� 0...
	CGPoint m_PointMoving;
	float m_fAngle;

public:
	bool init();
	bool initWithTextureName(string name);

	void tick(float dt);
};