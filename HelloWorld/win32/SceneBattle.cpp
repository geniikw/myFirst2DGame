#include"SceneBattle.h"
#include"Manager_Resource.h"
#include"Object_MiniCube.h"
#include"header.h"
#include"Battle_MenuUI.h"


#include"Battle_Enermy.h"


CCScene* SceneBattle::scene()
{
	CCScene *pScene = CCScene::node();
	SceneBattle *pLayer = SceneBattle::node();
	pScene->addChild(pLayer);
	return pScene;
}

bool SceneBattle::init()
{
	if (!CCLayer::init()) return false;

	schedule(schedule_selector(SceneBattle::tick));

	this->addChild(&m_BG,-996);
	m_BG.init(800, 180, 0.57);
	m_BG.autorelease();

	//利阑 积己窃 しし;
	Battle_Enermy *enermy;
	for (int n = 0; n < 4; n++)
	{
		enermy = new Battle_Enermy(CT_ENERMY);
		m_BG.addChild(enermy);

		enermy->initPosition(getEnermyPositionByIndex(rand() % 420));
		//enermy->initPosition(CG3Point(500 +n*30,100,0));
		//enermy->initPosition(CG3Point(400.f + rand() % 40, 100.f + rand() % 40, 0.f));//苟摹霸 府哩...

		enermy->makeShadow(0.f);
		enermy->setFlipX(true);
		//enermy->refreshPosition();
	}

	vector<Battle_Unit*>* pList = m_BG.getArrayPointerByTag(CT_HERO);

	m_pMenuUI = new Battle_MenuUI(pList);
	this->addChild(m_pMenuUI);

	CGSize winSize = CCDirector::sharedDirector()->getWinSize();

	this->setAnchorPoint(ccp(0, 0));
	this->setPosition(ccp(0, 0));

	this->setScaleX(winSize.width / 640);
	this->setScaleY(winSize.height / 480);

	return true;
}

void SceneBattle::tick(ccTime dt)
{
	Manager_Global::getInstance()->globalTick(dt);
}
