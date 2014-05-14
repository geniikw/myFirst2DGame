#include"SceneTitle.h"
#include"SceneLoading.h"

SceneTitle::SceneTitle()
{
	m_iStep = 0;
	m_fTitleOpasity = 0.f;
	m_iOffsetBG = 0.f;
	m_iOffsetIllust = 0.f;
	m_fLayerColor = 0.f;
}

CCScene* SceneTitle::scene()
{
	CCScene *pScene = CCScene::node();
	SceneTitle *pLayer = SceneTitle::node();

	pScene->addChild(pLayer);

	return pScene;
}

bool SceneTitle::init()
{
	if (!CCLayer::init()) return false;

	this->schedule(schedule_selector(SceneTitle::tick));

	m_pBack = CCSprite::spriteWithFile("BVtitle/titleBG.png");
	m_pIllust = CCSprite::spriteWithFile("BVtitle/titleModel.png");
	m_pTitle = CCSprite::spriteWithFile("BVtitle/title.png");
	m_pString = CCSprite::spriteWithFile("BVtitle/titleText.png");

	CGSize BG = m_pBack->getContentSize();
	CGSize MN = CCDirector::sharedDirector()->getWinSize();
	
	m_iGoalOffsetBG = BG.height * MN.width / BG.width - MN.height;

	m_pBack->setAnchorPoint(ccp(0, 0));
	m_pBack->setScale(MN.width / BG.width);
	
	m_pIllust->setAnchorPoint(ccp(0, 0));
	m_pIllust->setPosition(ccp(400, 90));

	m_pString->setOpacity(0.f);
	m_pString->setPosition(ccp(320, 110));

	m_pTitle->setScale(0.7);
	m_pTitle->setPosition(ccp(300, 320));
	m_pTitle->setOpacity(0.f);

	this->addChild(m_pBack);
	this->addChild(m_pIllust);
	this->addChild(m_pString);
	this->addChild(m_pTitle,1);
	

	m_pShadow = CCLayerColor::layerWithColor(ccc4(0, 0, 0, 0));
	this->addChild(m_pShadow);
	
	return true;
}

void SceneTitle::tick(ccTime dt)
{
	static int press = 0;
	static float time = 0.f;
	
	if (GetAsyncKeyState(VK_RETURN))
	{
		m_iStep = 3;
		m_fTitleOpasity = 254.f;
		m_iOffsetIllust = 220.f;
		m_iOffsetBG = m_iGoalOffsetBG;
	}

	if (m_iStep == 0)
	{
		m_iOffsetBG += 0.7f;
		m_iOffsetIllust += 1;

		if (m_iOffsetBG > m_iGoalOffsetBG)
			m_iStep++;
	}
	else if (m_iStep == 1)
	{
		m_fTitleOpasity += 5.f;
		if (m_fTitleOpasity > 254.f)
			m_iStep++;
	}
	else if (m_iStep == 2)
	{
		m_pString->setOpacity(254.f);
		time += dt;
		if (time > 1.f)
		{
			m_iStep++;
			time = 0.f;
		}
		if (GetAsyncKeyState(VK_RETURN))
			m_iStep = 4;
	}
	else if (m_iStep == 3)
	{
		m_pString->setOpacity(100.f);
		time += dt;
		if (time > 1.f)
		{
			m_iStep--;
			time = 0.f;
		}
		if (GetAsyncKeyState(VK_RETURN))
			m_iStep = 4;
	}
	else if (m_iStep == 4)
	{
		m_fLayerColor += 1.f;
		m_fTitleOpasity -= 2.f;
		if (m_fLayerColor >250.f)
			m_iStep++;
	}
	else if (m_iStep == 5)
	{
		CCDirector::sharedDirector()->replaceScene(SceneLoading::scene());
	}
	m_pBack->setPosition(ccp(0, 0 - m_iOffsetBG));
	m_pIllust->setPosition(ccp(400, 90 - m_iOffsetIllust));
	m_pTitle->setOpacity(m_fTitleOpasity);
	m_pShadow->setOpacity(m_fLayerColor);
}