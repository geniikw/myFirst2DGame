#pragma once
#include"cocos2d.h"
#include"header.h"
using namespace cocos2d;

class Battle_Damage : public CCSprite
{
	//����� �׳� new-> delete �̱� �ѵ� �׳� ���� �����ϴ°� ���ٰ� ��
	bool	  m_bIsUsed;
	ccColor3B m_color;
	CCSprite *m_pNumbers[G_MAX_DIGIT];

	//�׸��� ������
	float	m_fScaleY;
	float	m_fScaleX;

	//frame time
	float	m_fTimer;
	float	m_fOpacity;
	CGPoint m_Offset;

public:
	Battle_Damage();

	void setUp(CGPoint pos,int Damage,ccColor3B color);
	void tick(ccTime dt);

private:
	void init();
	CCAnimation* makeNumbersAnimation();
};