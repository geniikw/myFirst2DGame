#pragma once
#include"cocos2d.h"
#include"CObject_Deco.h"
#include"Object_header.h"


using namespace cocos2d;

//이 오브젝트는 마을에서만 사용됨.
//feedback 슬라이딩을 거느니 다이나믹 무빙 적용하는게 나을듯함.

class Object_Hero : public CCSprite
{
private://에니메이션 관련 변수
	float m_fFrameTime;
	float m_fFrameMaxTime;
	int m_iFrameNumber;
	int m_iFrameMaxNumber;
	char m_szStateBuf[10];

private:
	ENUM_SPEECH m_iSpeech;
public:
	int getiSpeech(){ return m_iSpeech; }

private:
	float m_fSpeed;
	ENUM_STATE m_iprvState;
	ENUM_STATE m_iState;

private://다이나믹 무빙 관련.
	CGPoint m_destPosition;

public:
	void setPassivePosition(CGPoint pos); //셋포지션 오버로딩. 데스트 포지션도 같이 바꿈.

public://왜 퍼블릭이징..
	CObject_Deco *m_pDeco;
	CObject_Deco *m_pSpeech;//말풍선표...?

public:
	Object_Hero();

	bool init(wstring name);
	void tick(ccTime dt);

	void action(ccTime dt);
	void animation(ccTime dt);

public:
	//upkey action;

	void popUpStore();
	void popUpMenu();
};


