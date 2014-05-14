#pragma once
#include"cocos2d.h"
#include"CObject_Deco.h"
#include"Object_header.h"


using namespace cocos2d;

//�� ������Ʈ�� ���������� ����.
//feedback �����̵��� �Ŵ��� ���̳��� ���� �����ϴ°� ��������.

class Object_Hero : public CCSprite
{
private://���ϸ��̼� ���� ����
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

private://���̳��� ���� ����.
	CGPoint m_destPosition;

public:
	void setPassivePosition(CGPoint pos); //�������� �����ε�. ����Ʈ �����ǵ� ���� �ٲ�.

public://�� �ۺ���¡..
	CObject_Deco *m_pDeco;
	CObject_Deco *m_pSpeech;//��ǳ��ǥ...?

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


