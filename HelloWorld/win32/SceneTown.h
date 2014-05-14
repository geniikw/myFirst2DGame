#include"cocos2d.h"
#include"Object_Hero.h"
#include"UI_Menu.h"

using namespace cocos2d;


class SceneTown : public CCLayer
{

private:
	//�̰� ����Ű�� ��ü�� ������ �����ϴ�.
	CCSprite *m_pControllRight;

private:
	//�����
	Object_Hero *m_pHero;
	
private://���
	CCSprite *m_pSky;
	CCSprite *m_pBg;
	CCSprite *m_pHouse1;
	CCSprite *m_pHouse2;
	CCLayerColor *m_pFade; //��ü���� ȭ���� ��Ӱ� �� �� ��������... �޴��� ��ο��� ;��;

	float m_fTime;
	int m_iShadow;
	int m_iFade;//0~255���� ������...
	int m_iDestFade;

private:
	//�޴�ȭ��
	UI_Menu *m_pMenu;

public:
	static CCScene* scene();
	LAYER_NODE_FUNC(SceneTown)

	bool init();
	void tick(ccTime dt);
	virtual void ccTouchesBegan(NSSet *pTouches, UIEvent *pEvent);
	virtual void ccTouchesMoved(NSSet *pTouches, UIEvent *pEvent);
	virtual void ccTouchesEnded(NSSet *pTouches, UIEvent *pEvent);

public:
	CCSprite* getConstroll();
	void setControll(CCSprite *owner);
	//can't get objectPoint to set from child

public:
	int searchTown(CGPoint point);
	void SwapMenuHero();

public://���̵� ���� �Լ�.
	void setFade(int value){ m_iDestFade = value; }
	//�ǵ����̸� 75�̳����� ����ϵ���.
};