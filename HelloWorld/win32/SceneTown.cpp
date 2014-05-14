#include"SceneTown.h"
#include"Manager_Resource.h"
#include"Manager_Global.h"

CCScene* SceneTown::scene()
{
	CCScene *pScene = CCScene::node();
	SceneTown *pLayer = SceneTown::node();

	pScene->addChild(pLayer);

	return pScene;
}

bool SceneTown::init()
{
	if (!CCLayer::init()) return false;

	m_fTime = 0.f;
	m_iShadow = 0;
	m_iFade = 0;
	m_iDestFade = 0;
	m_pFade = new CCLayerColor;
	m_pFade->initWithColor(ccc4(0, 0, 0, 0));
	this->addChild(m_pFade,10);

	this->schedule(schedule_selector(SceneTown::tick));
	this->setIsTouchEnabled(true);

	Manager_Resource* resStore = Manager_Resource::getInstance();

	m_pSky = CCSprite::spriteWithTexture(resStore->getResourceWithString("Sky"));
	this->addChild(m_pSky);
	m_pSky->setPosition(ccp(320, 70));

	m_pBg = CCSprite::spriteWithTexture(resStore->getResourceWithString("townBg"));
	this->addChild(m_pBg);
	m_pBg->setAnchorPoint(ccp(0, 0));

	m_pHouse1 = CCSprite::spriteWithTexture(resStore->getResourceWithString("house1"));
	m_pHouse1->setPosition(ccp(400, 50));
	m_pHouse1->setAnchorPoint(ccp(0, 0));
	this->addChild(m_pHouse1);

	m_pHouse2 = CCSprite::spriteWithTexture(resStore->getResourceWithString("house2"));
	m_pHouse2->setPosition(ccp(100, 50));
	m_pHouse2->setAnchorPoint(ccp(0, 0));
	this->addChild(m_pHouse2);

	m_pHero = new Object_Hero;
	m_pHero->init(L"lenneth");
	this->addChild(m_pHero);

	m_pHero->setPassivePosition(ccp(100, 50));

	m_pMenu = new UI_Menu;
	m_pMenu->init();
	this->addChild(m_pMenu);

	m_pMenu->setAnchorPoint(ccp(0, 0));
	m_pMenu->setPosition(ccp(20, 100));

	m_pMenu->setIsVisible(false);
	m_pControllRight = m_pHero;

	return true;
}

void SceneTown::tick(ccTime dt)
{
	float newdt = Manager_Global::getInstance()->g_fBattleDT * dt;

	m_fTime += 2.f * newdt;
	if (m_fTime > 360.f)
		m_fTime = 0.f;

	m_iShadow = abs( 180 - m_fTime );


	int c = 255 - m_iShadow - m_iFade;
	int d = 255 - m_iFade * 2;
	m_pHouse2->setColor(ccc3(c, c, c));
	m_pHouse1->setColor(ccc3(c, c, c));
	m_pBg->setColor(ccc3(c, c, c));
	m_pHero->setColor(ccc3(d, d, d));
	m_pSky->setColor(ccc3(d, d, d));

	m_pSky->setRotation(m_fTime);
	//m_pFade->setOpacity(m_iFade);

	if (m_iFade != m_iDestFade)
	{
		int dif = m_iFade - m_iDestFade;
		m_iFade -= dif / 16;
	}
}

void SceneTown::ccTouchesBegan(NSSet *pTouches, UIEvent *pEvent)
{
	//잡는당
}
void SceneTown::ccTouchesMoved(NSSet *pTouches, UIEvent *pEvent)
{
	//끈당
}
void SceneTown::ccTouchesEnded(NSSet *pTouches, UIEvent *pEvent)
{
	//놓는당
}

void SceneTown::setControll(CCSprite *owner)
{
	m_pControllRight = owner;

}
CCSprite* SceneTown::getConstroll()
{
	return m_pControllRight;
}

int SceneTown::searchTown(CGPoint point)
{
	if (200 < point.x && point.x < 300)
	{
		return SPEECH_MENU;
	}

	if (500 < point.x && point.x < 600)
	{
		return SPEECH_STORE;
	}
	return 0;
}

void SceneTown::SwapMenuHero()
{
	if (m_pControllRight == m_pHero)
	{
		Manager_Global::getInstance()->g_fBattleDT = 0.f;
		m_pMenu->setIsVisible(true);
		m_iDestFade = 75;
		m_pControllRight = m_pMenu;
		m_pHero->m_pSpeech->setIsVisible(false);
	
	}
	else if (m_pControllRight == m_pMenu)
	{
		Manager_Global::getInstance()->g_fBattleDT = 1.f;
		m_iDestFade = 0;
		m_pMenu->setIsVisible(false);
		m_pControllRight = m_pHero;
		m_pHero->m_pSpeech->setIsVisible(true);
	}
}