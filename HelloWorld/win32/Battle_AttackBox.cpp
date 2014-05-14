#include"Battle_AttackBox.h"
#include"BackGroundSprite.h"
#include"Battle_Unit.h"
#include"kwMsg_Action.h"
#include"Battle_Damage.h"
#include"Manager_Global.h"
#include"kwMoving.h"
#include"kwMoving_Vector.h"

#include"Battle_HitEffect.h"
#include"Battle_CutEffect.h"

Battle_AttackBox::Battle_AttackBox()
{
	m_bIsUsed = false;
	m_pMap = NULL;
	m_pMsgAction = NULL;
	m_fRemainTime = 0.f;
	m_iHitedNumber = 0;
	m_pPosData = new My3DCube(CG3Point(10, 10, 10));
	srand(870403);

	this->setIsVisible(false);

	schedule(schedule_selector(Battle_AttackBox::tick));
}

Battle_AttackBox::~Battle_AttackBox()
{
	//kw에서 pos데이터를 지워주기 때문에 이중 삭제가 되었다.. 조심하자 헷갈리네예...
}

void Battle_AttackBox::tick(ccTime dt)
{
	if (m_bIsUsed == false)
		return;
	
	Manager_Global *pG = Manager_Global::getInstance();
	dt = pG->g_fBattleDT * dt;

	if (m_pMap == NULL)
	{
		MessageBoxA(NULL, "부모맵 정보가 없습니다.", "에러", MB_OK);
		return;
	}
	if (m_pPosData == NULL)
	{
		MessageBoxA(NULL, "자신의 모형정보가 없습니다.", "에러", MB_OK);
		return;
	}
	if (m_pMsgAction == NULL)
	{
		MessageBoxA(NULL, "메세지 포인터가 없습니다.", "에러", MB_OK);
		return;
	}

	if (m_pMoving != NULL)
		m_pMoving->doMove(dt);

	m_fRemainTime -= dt;
	
	vector<Battle_Unit*> *pList;
	CT tag;

	for (int n = 0; n < 3; n++)
	{
		if (n == 0)
			tag = CT_OBJECT;
		if (n == 1)
			tag = CT_ENERMY;
		if (n == 2)
			tag = CT_HERO;
		
		if (m_pMsgAction->m_pTarget->getTag() & tag)
		{
			pList = m_pMap->getArrayPointerByTag(tag);
			for (int n = 0; n < pList->size(); n++)
			{
				if (MYUnit::AABBCheckByPoint(this->getPosData(), (*pList)[n]->getPosData()))
				{
					if ((*pList)[n]->checkAttackBox(this))
					{
						(*pList)[n]->damaged(this);

						Battle_Damage *pDamageText = new Battle_Damage;
						m_pMap->CCSprite::addChild(pDamageText, EZ_UI);
						pDamageText->setUp(
							(*pList)[n]->getDisplayPosition() + ccp(m_iHitedNumber * 20, m_iHitedNumber * 20),
							m_pMsgAction->m_iDamage,
							ccc3(255, 0, 0)
							);

						/*	Battle_CutEffect *pHE = new Battle_CutEffect(ccc3(255,255,255));
						pHE->setPosition(this->getDisplayPosition());
						m_pMap->CCSprite::addChild(pHE, EZ_UI);*/
						Battle_HitEffect *pHE = new Battle_HitEffect();
						pHE->setPosition(this->getDisplayPosition());
						m_pMap->CCSprite::addChild(pHE, EZ_UI);


						m_iHitedNumber++;
					}
				}
			}
		}

	}

	



	if (m_fRemainTime < 0.f)
	{
		setDown();
	}
	doAni(dt);
}

void Battle_AttackBox::doAni(ccTime dt)
{

}

void Battle_AttackBox::setUp(shared_ptr<kwMsg_Action> msg)
{	
	m_pMoving = msg->m_pABMoving;
	if (m_pMoving != NULL)
		m_pMoving->setOwner(this);
	
	//크기 재설정, 남은 시간 설정, 보이게 설정, 사용중 설정
	m_bIsUsed = true;
	this->setIsVisible(m_bIsUsed);
	m_fRemainTime = msg->m_fABRemainTime;
	m_pMsgAction = msg;
	
	if (m_pPosData != NULL)
		delete m_pPosData;

	m_pPosData = new My3DCube(msg->m_sizeAB);
	m_pPosData->setMapData(m_pMap->getPosData()->getMapData());
}

void Battle_AttackBox::setDown()
{
	m_pMoving = NULL;
	m_bIsUsed = false;
	setIsVisible(m_bIsUsed);
	m_pMsgAction = NULL;  //이러면 레퍼런스 카운트가 줄어든다.
	m_iHitedNumber = 0;
}

void Battle_AttackBox::setParentsMap(BackGroundSprite* map)
{
	m_pMap = map;
}
