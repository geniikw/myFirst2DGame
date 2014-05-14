#include"cocos2d.h"
#include"Object_Hero.h"
#include"UI_Menu.h"

using namespace cocos2d;


class SceneTown : public CCLayer
{

private:
	//이게 가리키는 객체만 조작이 가능하다.
	CCSprite *m_pControllRight;

private:
	//히어로
	Object_Hero *m_pHero;
	
private://배경
	CCSprite *m_pSky;
	CCSprite *m_pBg;
	CCSprite *m_pHouse1;
	CCSprite *m_pHouse2;
	CCLayerColor *m_pFade; //전체적인 화면을 어둡게 할 때 사용되지만... 메뉴도 어두워짐 ;ㅁ;

	float m_fTime;
	int m_iShadow;
	int m_iFade;//0~255값을 가진다...
	int m_iDestFade;

private:
	//메뉴화면
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

public://페이드 관련 함수.
	void setFade(int value){ m_iDestFade = value; }
	//되도록이면 75이내에서 사용하도록.
};