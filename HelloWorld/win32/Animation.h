#pragma once
#include"cocos2d.h"
#include"kwSprite.h"
#include<memory>
using namespace cocos2d;
using namespace std;

#define GA(CAT) getAnimationString(CAT)

class kwMsg_Ani;

class Animation
{
protected:
	int		m_iCAT;
	int		m_iFrameStartIndex;
	int		m_iFrameRepeatIndex;
	int		m_iFrameEndIndex;
	float	m_fFrameMaxTime;
	int		m_iCurFrame;
	float	m_fFrametime;
public:
	Animation();
	
	//NULL �� ������ ���ִ� �ڼ���
	void setAniMsg(shared_ptr<kwMsg_Ani> msg);
	int getCurFrame(){ return m_iCurFrame; }

	//�̰� ���� ��������Ʈ������ �ݵ�ø������� 
	virtual CCSprite* getOwner() = 0;

	int getAniMaxFrame(){return getOwner()->animationByName(GA(m_iCAT))->getFrames()->count(); }
	virtual void doAni(ccTime dt);
	
public:
	static char const* getAnimationString(int CAT);
};
