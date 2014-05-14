#include"Battle_Unit.h"
#include"Manager_Global.h"
#include"kwSprite.h"
#include"BackGroundSprite.h"
#include"Battle_AttackBox.h"

#include"kwMsg_Ani.h"
#include"kwMsg_Action.h"

#include"kwOrderWaiting.h"
#include"kwMoving.h"
#include"kwMoving_Vector.h"

#include"kwOrder_Crash.h"

#include"header.h"

Battle_Unit::Battle_Unit()
:Status(),Animation()
{ 
	init();//kwSprite 초기화
}
Battle_Unit::~Battle_Unit()
{

}

bool Battle_Unit::init()
{
	//크기... ㅇㅇ; 필요하면 재설정해야함.
	if (!kwSprite::init(40,5,60)) return false;
	Manager_Global* MG = Manager_Global::getInstance();  //글로벌 변수... 게임코어..에 다 넣자.
	
	m_pMoving = NULL;
	m_iCAT = CAT_STAND;
	m_pMap = NULL;
	m_pCurOrder = NULL;
	m_StartPosition = CG3PointZero;
	schedule(schedule_selector(Battle_Unit::tick));
	m_iActionCount = 0;

	return true;
}

void Battle_Unit::tick(ccTime dt)
{
	//dt가 1초 이상이면 리턴.. -ㅁ-
	if (dt > 1.f)
		return;
	//globalDT 적용
	dt = dt * Manager_Global::getInstance()->g_fBattleDT;
	
	if (m_pMoving != NULL)
	{
		m_pMoving->doMove(dt);
	}
	doKwShadowInTick();
	doOrder(dt);//명령을 적용시킴 백그라운드로 옮김  //적도 행동해야지... ㅠㅜㅠ
	doAni(dt);//애니메이션 처리
	doAB(dt);

}

void Battle_Unit::doKeySet(const KeySet &set)
{
	//히어로 전용 함수 명령을 받을 수 있음
	//명령이 실행중이면 새로 명령을 받지 않음
	if (m_pCurOrder != NULL)
		return;
	
	CG3Point movePoint;
	if (this->get3DPosition().x - m_pMap->getCurrentTargetPointer()->get3DPosition().x < 0.f)
	{
		movePoint = m_pMap->getCurrentTargetPointer()->get3DLeftSide(1);
	}
	else
	{
		movePoint = m_pMap->getCurrentTargetPointer()->get3DRightSide(1);
	}

	CG3Point UnitVector = this->get3DPosition() >> m_pMap->getCurrentTargetPointer()->get3DPosition();
	/*문뜩 거대한 똥을 만들고 있는게 아닌가... 라는 생각이 들었다... 하핫.. 개판이군.*/

	m_listOrder.push_back(kwOrderMoveToPoint::makekwOrderMoveToPoint(this, this->getinitPosition(), 100.f, 100.f, 200.f, shared_ptr<kwMsg_Ani>(new kwMsg_Ani(CAT_RUN, 0, 2, 0, 0.1f))));

	
	
		
}
void Battle_Unit::doAni(ccTime dt)
{
	refreshPosition();
	this->getParent()->reorderChild(this, 100-m_pPosData->getPosition().y/10);
	
	if (m_bRender == false)
		return;

	Animation::doAni(dt);

}

void Battle_Unit::doOrder(ccTime dt)
{
	if (m_listOrder.size() != 0 && m_pCurOrder == NULL)
	{	//명령스택에 명령이 있고 현재 실행중인 명령이 없다면 실행한다.
		m_pCurOrder = m_listOrder.front();
		m_listOrder.pop_front();	//앞으로
	}

	///active action
	if (m_pCurOrder == NULL)//명령이 없으면 끝냄.
	{
		return;
	}

	if (m_pCurOrder->execute(dt))
	{
		delete m_pCurOrder;
		m_pCurOrder = NULL;
	}
}

void Battle_Unit::doAB(ccTime dt)
{
	list<st_AB*>::iterator it;
	for (it = m_listABPointer.begin(); it != m_listABPointer.end(); it++)
	{
		(*it)->remain -= dt;
		if ((*it)->remain < 0.f)
		{
			m_listABPointer.erase(it);
			break;
		}
	}
}

void Battle_Unit::addOrder(kwOrder* order)
{
	m_listOrder.push_back(order);
}

void Battle_Unit::addOrder(kwOrderHit* order)
{
	//damage가 일을 하고 있음
}

void Battle_Unit::damaged(Battle_AttackBox* box)
{
	//직접 대입해줌...
	m_pCurOrder = kwOrderHit::makeHitOrder(this, box->getMsgAction(),shared_ptr<kwMsg_Ani>(new kwMsg_Ani(CAT_GUARD,0,1,0,0.1f)));
	m_listOrder.clear();//뭐 일단 데미지를 받으면 모든 명령을 취소함...

	st_AB *st_ab = new st_AB;
	st_ab->pAB = box;
	st_ab->remain = 2.f; //일단 고정값... 이런게 많네..
	m_listABPointer.push_back(st_ab);
}
#include"Battle_Damage.h"
#include"Manager_Sound.h"
void Battle_Unit::damaged(CG3Point force, int damage)
{
	Manager_Sound::shareClass()->Play_Wall();
	Battle_Damage *pDamage = new Battle_Damage;
	pDamage->setUp(this->getDisplayPosition(), damage, ccc3(0, 100, 100));
	this->getParent()->addChild(pDamage);

	m_pCurOrder = kwOrder_Crash::makeCrashOrder(this, force,damage, shared_ptr<kwMsg_Ani>(new kwMsg_Ani(CAT_HIT, 0, 0, 0, 0.1f)));
}

bool Battle_Unit::checkAttackBox(Battle_AttackBox* box)
{
	list<st_AB*>::iterator it;
	for (it = m_listABPointer.begin(); it != m_listABPointer.end(); it++)
	{
		if ((*it)->pAB == box)
		{
			//하나라도 겹치면
			return false;
		}		
	}
	return true;
}

void Battle_Unit::initPosition(const CG3Point &pos)
{
	setPosition(pos);
	m_StartPosition = pos;
}

CCSpriteFrame*  Battle_Unit::getOwnerCurrentFrame()
{
	return this->displayedFrame();
}

BackGroundSprite*	Battle_Unit::getBackGround()
{
	return m_pMap;
}

void Battle_Unit::doKwShadowInTick()
{
	if (m_pShadow == NULL)
	{
		//NULL 이면 실행 안함...
		return;
	}
	if (this->displayedFrame() == NULL)
		return;

	//m_pShadow->setPosition(ccp(m_pPosData->getDisplayPosition().x, m_pPosData->getDisplayPosition().y));
	//m_pShadow->setPosition(getPosition());
	m_pShadow->setPosition(m_pPosData->getDisplayPosition(1));


	m_pShadow->setFlipX(this->m_bFlipX);
	m_pShadow->setScale(m_pPosData->getDisplayScale());
	//m_pShadow->setScaleY(m_pShadow->getScaleX() + m_pPosData->getPosition().z / 10);
	
	if (this->m_iTag == CT_OBJECT)
		m_pShadow->setOpacity(100 - m_pPosData->getPosition().z);
	else
		m_pShadow->setOpacity(200 - m_pPosData->getPosition().z);

	m_pShadow->setDisplayFrame(this->displayedFrame());
}

void Battle_Unit::doCard(const Action_Card &card)
{
	//카드에 따라서 명령을 달리줌 
	switch (card.getCardNumber())
	{
		//흐음...


	}
}

void Battle_Unit::doAction()
{
	if (m_iActionCount < 1 || m_iActionCount > 4)
		return;

	list<Action_Card>::iterator it;
	for (it = m_listCard[4-m_iActionCount].begin(); it != m_listCard[4-m_iActionCount].end(); it++)
	{
		doCard(*it);
	}
	m_iActionCount--;
}

void Battle_Unit::turnStart()
{
	m_iActionCount = 4;
}

void Battle_Unit::turnEnd()
{
	m_iActionCount = 0;
	m_listOrder.clear();
	m_pCurOrder = new kwOrderMoveToPoint(this, this->getinitPosition(), 100.f, 100.f, 300.f, shared_ptr<kwMsg_Ani>(new kwMsg_Ani(CAT_WALK, 0, 0, 0, 0.1f)));
}
