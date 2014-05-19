#include"Manager_Resource.h"
#include"Manager_Global.h"
#include"BackGroundSprite.h"
#include"Battle_Unit.h"
#include"Battle_Cursor.h"
#include"Battle_AttackBox.h"
#include"kwMsg_Action.h"
#include"Battle_Portrait.h"

#include"Battle_Meiling.h"
#include"Battle_Aya.h"
#include"Battle_Komachi.h"
#include"Battle_Reimu.h"

bool BackGroundSprite::init(float w, float h, float rate)
{
	if (!kwSprite::init(w,h))return false;

	m_pPosData->setAnchor(CG3Point(0.f, 0.f, 0.f));
	m_pPosData->setSizeRate(rate);
	m_pPosData->makeMapData(w, h, rate, 0.5f);

	m_pCursor = new Battle_Cursor(10.f, 20.f);
	this->addChild(m_pCursor);
	this->reorderChild(m_pCursor, EZ_UI);
	m_iCursorIndex = 0;
	m_iAttackBoxIndex = 0;

	m_iBattleTurn = 0;  //

	m_pRender = CCSprite::spriteWithSpriteFrame(Manager_Resource::getInstance()->getFrameWithString("grassTX"));
	m_pRender->getCamera()->setCenterXYZ(0, 0.01, 0);
	m_pRender->setAnchorPoint(ccp(0.f, 0.f));
	CCSprite::addChild(m_pRender, -1000);

	//히어로를 설정한다.
	
	Battle_Meiling *pMeiling = new Battle_Meiling(CT_HERO);
	Battle_Aya	   *pAya = new Battle_Aya(CT_HERO);
	Battle_Komachi *pKomachi= new Battle_Komachi(CT_HERO);
	Battle_Reimu   *pReimu = new Battle_Reimu(CT_HERO); 

	m_pControl[0] = pMeiling;
	m_pControl[1] = pAya;
	m_pControl[2] = pKomachi;
	m_pControl[3] = pReimu;


	for (int n = 0; n < MAX_HERO_COUNT; n++)
	{
		this->addChild(m_pControl[n]);
		//에드 차일드 후에 해야할것들...
		m_pControl[n]->makeShadow(0.f);
		m_pControl[n]->initPosition(G_POSITION_HERO_START[n]);

		m_pPortrait[n] = new Battle_Portrait;
		this->CCSprite::addChild(m_pPortrait[n]);
		m_pPortrait[n]->setPosition(ccp(n*150, 480));
		m_pPortrait[n]->setUnit(m_pControl[n]);
	}

	Battle_Unit *pObject;
	for (int n = 0; n < 10; n++)
	{
		pObject = g_WoodStake.makeBU(CT_OBJECT);

		if (n < 5)
		{
			pObject->setFlipX(true);
		}
		this->addChild(pObject);
		pObject->makeShadow(0.f);
		pObject->setPosition(G_POSITION_OBJECT_START[n]);
	}

	m_pAttackBoxArray = new Battle_AttackBox[g_MaxAttackBox];
	for (int n = 0; n < g_MaxAttackBox; n++)
	{
		addChild(&m_pAttackBoxArray[n]);
		reorderChild(&m_pAttackBoxArray[n], EZ_UI);
	}
	float Xoffset = 520;

	schedule(schedule_selector(BackGroundSprite::tick));
	Manager_Resource *pRes = Manager_Resource::getInstance();
	m_pSky = CCSprite::spriteWithSpriteFrame(pRes->getFrameWithString("BBgSky"));
	m_pSky->getCamera()->setCenterXYZ(0, -1, 0);
	m_pSky->setPosition(ccp(0, 563));
	m_pSky->setAnchorPoint(ccp(0, 0));
	m_pRender->addChild(m_pSky);

	Manager_Global::getInstance()->g_pBattleSprite = this;
	Manager_Global::getInstance()->g_pControllPermission = this;

	m_pDeepDark = CCLayerColor::layerWithColor(ccc4(0, 0, 0, 0));
	CCSprite::addChild(m_pDeepDark);

	this->CCSprite::addChild(&m_ATBHero);
	m_ATBHero.setAnchorPoint(ccp(0, 0));

	this->CCSprite::addChild(&m_ATBEnermy);
	m_ATBEnermy.setPosition(ccp(640,0));
	m_ATBEnermy.setAnchorPoint(ccp(1, 0));

	m_fHeroATBFacter = 50;
	m_fEnermyATBFacter = 40;
	m_fReduceATBFacter = 10;

	FILE *p;
	char buffer[5];
	fopen_s(&p, "gameSpeed.dat", "rt");
	fgets(buffer, 5, p);
	m_fHeroATBFacter = atoi(buffer);
	fgets(buffer, 5, p);
	m_fEnermyATBFacter = atoi(buffer);
	fclose(p);
	

	return true;
}
BackGroundSprite::~BackGroundSprite()
{
	delete[] m_pAttackBoxArray;
	delete m_pCursor;
}
#include"Manager_Global.h"

void BackGroundSprite::tick(ccTime dt)
{
	Manager_Global *pGM = Manager_Global::getInstance();

	dt = pGM->g_fBattleDT * dt;
	if (pGM->g_iDebugFlag == 1)
	{
		FILE *p;
		char buffer[5];
		fopen_s(&p, "gameSpeed.dat", "rt");
		fgets(buffer, 5, p);
		m_fHeroATBFacter = atoi(buffer);
		fgets(buffer, 5, p);
		m_fEnermyATBFacter = atoi(buffer);
		fclose(p);
	}

	//debug;;
	ctrlFunc(dt);
	
	doATB(dt);
	m_pRender->setPosition(Manager_Global::getInstance()->g_offsetGameScroll + ccp(-590, 0));
	m_pPosData->setCenterTilt(linear(0.f, 1.f, Manager_Global::getInstance()->g_offsetGameScroll.x,-800)+0.4f);
	//Manager_Global::getInstance()->g_offsetGameScroll;
}

void BackGroundSprite::addChild(Battle_Unit* child)
{
	kwSprite::addChild(child);

	child->setParentMap(this);
	switch (child->getTag())
	{
		case CT_HERO:
		{
					m_HeroArray.push_back(child); 		
					break;
		}
		case CT_ENERMY:m_EnermyArray.push_back(child); break;
		case CT_OBJECT:m_ObjectArray.push_back(child); break;
	}
}
void BackGroundSprite::addChild(kwSprite* child)
{
	kwSprite::addChild(child);
}
void BackGroundSprite::addChild(Battle_AttackBox *child)
{
	kwSprite::addChild(child);

	child->setParentsMap(this);
}


bool BackGroundSprite::isCollision(Battle_Unit *object, int tag)
{//어떤 target이 bgSprite안에 있는 tag와 충돌이 되었는지 검사함...
	vector<Battle_Unit*> *pList;
	
	switch (tag)
	{
		case CT_HERO: pList = &m_HeroArray; break;
		case CT_ENERMY:pList = &m_EnermyArray; break;
		case CT_OBJECT:pList = &m_ObjectArray; break;
	}
	
	for (int n = 0; n < pList->size(); n++)
	{
		if (MYUnit::AABBCheckByPoint((*pList)[n]->getPosData(), object->getPosData()))
		{//여기에 만약 object
			return true;
		}
	}
	return false;
}

bool BackGroundSprite::isCollision(My3DCube *pos, int tag)
{
	for (int n = 0; n < m_ObjectArray.size(); n++)
	{
		if (MYUnit::AABBCheckByPoint(m_ObjectArray[n]->getPosData(), pos))
		{//
			return true;
		}
	}
	return false;
}

CG3Point BackGroundSprite::moveRayCast(My3DCube pos, const CG3Point &movingData, int tag)
{
	//pos가 movingData 만큼 이동하고 싶은데 tag의 object들이랑 raycast를 함
	//target이 원래위치에서 moving
	float len = CG3PointLenght(movingData);
	CG3Point vector = movingData / len;
	int n = 0;
	for (n = 0; n < len; n++)
	{
		pos.addPosition(vector);
		if (isCollision(&pos, tag))
		{
			//충돌 됬으면
			pos.addPosition(-vector);
			break;
		}
	}
	return vector * n;
}

Battle_Unit* BackGroundSprite::getCurrentTargetPointer()
{
	return m_EnermyArray[m_iCursorIndex];
}

void BackGroundSprite::ctrlFunc(ccTime dt)
{
	Manager_Global *pG = Manager_Global::getInstance();
	
	dt = pG->g_fBattleDT * dt;
	if (pG->g_pControllPermission != this)
	{
		m_pDeepDark->setOpacity(200.f);
		return;
	}
	else
	{
		m_pDeepDark->setOpacity(0.f);
	}
	
	m_ctrl.getAsync();
	KeySet set = m_ctrl.getKeySet();
	
	if (set & (1 << 10))//f7 누르면
	{
		pG->g_iDebugFlag = !pG->g_iDebugFlag;
	}
	if (set & (1 << 11))//f8 누르면
	{
		pG->g_iRenderFlag = !pG->g_iRenderFlag;
	}

	switch (m_iBattleTurn)
	{
		case BT_NOHING:

		break;
		case BT_HERO:
		AttackControll(set);

		break;
		case BT_ENERMY:

		DefenceControll(set);
		break;
	}
	m_pCursor->setTarget(m_EnermyArray[m_iCursorIndex]);
	
}
void BackGroundSprite::requestUseAttackBox(shared_ptr<kwMsg_Action> msg, Battle_Unit*owner)
{
	if (m_pAttackBoxArray[m_iAttackBoxIndex].getIsUsed() == true)
	{
		//20개를 쓰는데 이런 경우는 없을 거라고 생각한다.
		MessageBoxA(NULL, "공격박스를 전부 다 사용함...--손나빠가나-- ", "error", MB_OK);
		return;
	}

	m_pAttackBoxArray[m_iAttackBoxIndex].setUp(msg);
	
	if (owner->get3DPosition().x > msg->m_pTarget->get3DPosition().x)
	{
		m_pAttackBoxArray[m_iAttackBoxIndex].setPosition(owner->get3DLeftSide() + msg->m_offsetAB);
	}
	else
	{
		m_pAttackBoxArray[m_iAttackBoxIndex].setPosition(owner->get3DRightSide() + msg->m_offsetAB);
	}
	m_iAttackBoxIndex++;

	if (m_iAttackBoxIndex >= g_MaxAttackBox)
		m_iAttackBoxIndex = 0;

	//message를 분석한다.
}

vector<Battle_Unit*>* BackGroundSprite::getArrayPointerByTag(int tag)
{
	switch (tag)
	{
		case CT_HERO: return &m_HeroArray; break;
		case CT_ENERMY:return &m_EnermyArray; break;
		case CT_OBJECT:return &m_ObjectArray; break;
	}
	return NULL;
}

void BackGroundSprite::AttackControll(KeySet set)
{
	for (int n = 0; n < 4; n++)
	{
		if (set & (1 << n))
		{
			m_pControl[n]->doAction();
		}
	}

	if (set & (1 << 6))//up
	{
		m_iCursorIndex++;
		if (m_iCursorIndex >= m_EnermyArray.size())
			m_iCursorIndex = 0;
	}
	if (set & (1 << 7))//down
	{
		m_iCursorIndex--;
		if (m_iCursorIndex < 0)
			m_iCursorIndex = m_EnermyArray.size() - 1;
	}
	Manager_Global *pG = Manager_Global::getInstance();
	if (set & (1 << 12))//t키를 누르면
	{
		pG->g_pControllPermission = pG->g_pBattleMenuUI;
	}

}
void BackGroundSprite::DefenceControll(KeySet key)
{
	for (int n = 0; n < m_EnermyArray.size(); n++)
		m_EnermyArray[n]->doAction();

}

void BackGroundSprite::doATB(ccTime dt)
{

	if (m_iBattleTurn == BT_NOHING)
	{
		m_ATBHero.getProgressRef() += dt * m_fHeroATBFacter;
		m_ATBEnermy.getProgressRef() += dt * m_fEnermyATBFacter;
		if (m_ATBHero.getProgressRef() > 100.f)
		{
			m_iBattleTurn = BT_HERO;
			for (int n = 0; n < 4; n++)
			{
				m_HeroArray[n]->turnStart();
			}
		}
		if (m_ATBEnermy.getProgressRef() > 100.f)
		{
			m_iBattleTurn = BT_ENERMY;

			for (int n = 0; n < m_EnermyArray.size(); n++)
			{
				m_EnermyArray[n]->turnStart();

			}

		}
	}

	if (m_iBattleTurn == BT_HERO)
	{
		if (m_ATBHero.reduceTick(dt))
		{
			m_iBattleTurn = 0;
			for (int n = 0; n < 4; n++)
			{
				m_HeroArray[n]->turnEnd();
			}
		}
	}
	if (m_iBattleTurn == BT_ENERMY)
	{
		m_ATBEnermy.getProgressRef() -= dt * 5;
		if (m_ATBEnermy.reduceTick(dt))
		{
			m_iBattleTurn = 0;

			for (int n = 0; n < m_EnermyArray.size(); n++)
			{
				m_EnermyArray[n]->turnEnd();

			}
		}
	}
}