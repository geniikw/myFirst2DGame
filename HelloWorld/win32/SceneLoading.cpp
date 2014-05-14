#include"SceneLoading.h"
#include"Manager_Resource.h"
#include"MotionSet.h"
#include"Object_Hero.h"
#include"header.h"


//로딩후 나올씬들
#include"SceneTown.h"
#include"SceneBattle.h"


CCScene* SceneLoading::scene()
{
	CCScene *pScene = CCScene::node();
	SceneLoading *pLayer = SceneLoading::node();

	pScene->addChild(pLayer);

	return pScene;
}

bool SceneLoading::init()
{
	m_fLoadingCooltime = 0.f;
	m_r = 50;
	m_g = 50;
	m_b = 50;
	m_bR = 0;
	m_bG = 0;
	m_bB = 0;
	m_fLoadingTime = 0.f;
	
	Manager_Resource *ResManager = Manager_Resource::getInstance();
	ResManager->LoadingResourceWithFile("lenneth.png", "lenneth");
	CCTexture2D *res = ResManager->getResourceWithString("lenneth");
	//잠깐만 불러오자.. 미안...-_-
	m_pLoadingImage = new CCSprite;
	m_pLoadingImage->init();
	
	wstring name = L"lenneth";
	MotionSet set(&name);  //custom class for motion data file format
	gl2DFrame temp;
	wchar_t buf[64];
	CCAnimation *ani = NULL;
	for (int n = 0; n < set.m_pMotions.size(); n++)
	{
		temp = set.m_pMotions[n];
		ani = new CCAnimation;
		lstrcpy(buf, set.m_pMotions[n].motionName.c_str());
		
		char *tempBuf = wtoa(buf);
		ani->initWithName(tempBuf);
		delete tempBuf;

		for (int i = 0; i < temp.frame.size(); i++)
			ani->addFrameWithTexture(res, temp.frame[i]);

		m_pLoadingImage->addAnimation(ani);
	}

	//m_pLoadingImage->addAnimation(pHero->animationByName("RUNM"));
	//m_pLoadingImage->addAnimation(pHero->animationByName("RUNS"));
	//m_pLoadingImage->addAnimation(pHero->animationByName("RUNE"));

	m_pLoadingImage->setAnchorPoint(ccp(0, 0));
	this->addChild(m_pLoadingImage);

	m_pLoadingText = new CCSprite;
	m_pLoadingText->initWithFile("BVLoading/NowLoadingText.png");
	m_pLoadingText->setPosition(ccp(170, 100));
	m_pLoadingText->setAnchorPoint(ccp(0, 0));
	this->addChild(m_pLoadingText);

	m_pLoadingFileText = new CCLabelBMFont;
	m_pLoadingFileText->initWithString("loading Start" , "fonts/arial16.fnt");
	this->addChild(m_pLoadingFileText);
	m_pLoadingFileText->setPosition(ccp(200, 200));
	m_pLoadingFileText->setAnchorPoint(ccp(0, 0));

	CGSize winSize = CCDirector::sharedDirector()->getWinSize();

	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(0, 0));

	this->setScaleX(winSize.width / 640);
	this->setScaleY(winSize.height / 480);


	schedule(schedule_selector(SceneLoading::tick));
	return true;
}

void SceneLoading::tick(ccTime dt)
{
	LoadingAnimation(dt);
	m_fLoadingCooltime += dt;
	if (m_fLoadingCooltime > 0.f)
	{
		LoadingResult temp = Manager_Resource::getInstance()->LoadingTick();
		if (temp.result == false)
		{
			CCDirector::sharedDirector()->replaceScene(SceneBattle::scene());
		}
		m_fLoadingCooltime = 0.f;
		m_pLoadingFileText->setString(temp.filename.c_str());
	}
}
void SceneLoading::tick2(ccTime dt)
{
	
}

void SceneLoading::LoadingAnimation(ccTime dt)
{
	static char buf[6];
	strcpy(buf, "RUNM");

	if (m_bR == 0)
	{
		if (m_r > 245)
			m_bR = 1;
		else
			m_r += 6;
	}
	else
	{
		if (m_r < 50)
			m_bR = 0;
		else
			m_r -= 6;
	}

	if (m_bG == 0)
	{
		if (m_g > 245)
			m_bG = 1;
		else
			m_g += 5;
	}
	else
	{
		if (m_g < 50)
			m_bG = 0;
		else
			m_g -= 5;
	}

	if (m_bB == 0)
	{
		if (m_b > 245)
			m_bB = 1;
		else
			m_b += 4;
	}
	else
	{
		if (m_b < 50)
			m_bB = 0;
		else
			m_b -= 4;
	}


	if (sin(m_fLoadingTime*0.3) - sin(m_fLoadingTime*0.3 + 0.1f) < 0)
		m_pLoadingImage->setFlipX(true);
	else
		m_pLoadingImage->setFlipX(false);

	m_fLoadingTime += dt * 10;

	int n = (int)m_fLoadingTime % m_pLoadingImage->animationByName(buf)->getFrames()->count();
	
	
	m_pLoadingImage->setPosition(ccp(320 + 100 * sin(m_fLoadingTime*dt), 260));
	m_pLoadingImage->setDisplayFrame(buf, n);
	m_pLoadingText->setColor(ccc3(m_r, m_g, m_b));
}