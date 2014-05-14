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
	init();//kwSprite �ʱ�ȭ
}
Battle_Unit::~Battle_Unit()
{

}

bool Battle_Unit::init()
{
	//ũ��... ����; �ʿ��ϸ� �缳���ؾ���.
	if (!kwSprite::init(40,5,60)) return false;
	Manager_Global* MG = Manager_Global::getInstance();  //�۷ι� ����... �����ھ�..�� �� ����.
	
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
	//dt�� 1�� �̻��̸� ����.. -��-
	if (dt > 1.f)
		return;
	//globalDT ����
	dt = dt * Manager_Global::getInstance()->g_fBattleDT;
	
	if (m_pMoving != NULL)
	{
		m_pMoving->doMove(dt);
	}
	doKwShadowInTick();
	doOrder(dt);//����� �����Ŵ ��׶���� �ű�  //���� �ൿ�ؾ���... �Ф̤�
	doAni(dt);//�ִϸ��̼� ó��
	doAB(dt);

}

void Battle_Unit::doKeySet(const KeySet &set)
{
	//����� ���� �Լ� ����� ���� �� ����
	//����� �������̸� ���� ����� ���� ����
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
	/*���� �Ŵ��� ���� ����� �ִ°� �ƴѰ�... ��� ������ �����... ����.. �����̱�.*/

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
	{	//��ɽ��ÿ� ����� �ְ� ���� �������� ����� ���ٸ� �����Ѵ�.
		m_pCurOrder = m_listOrder.front();
		m_listOrder.pop_front();	//������
	}

	///active action
	if (m_pCurOrder == NULL)//����� ������ ����.
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
	//damage�� ���� �ϰ� ����
}

void Battle_Unit::damaged(Battle_AttackBox* box)
{
	//���� ��������...
	m_pCurOrder = kwOrderHit::makeHitOrder(this, box->getMsgAction(),shared_ptr<kwMsg_Ani>(new kwMsg_Ani(CAT_GUARD,0,1,0,0.1f)));
	m_listOrder.clear();//�� �ϴ� �������� ������ ��� ����� �����...

	st_AB *st_ab = new st_AB;
	st_ab->pAB = box;
	st_ab->remain = 2.f; //�ϴ� ������... �̷��� ����..
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
			//�ϳ��� ��ġ��
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
		//NULL �̸� ���� ����...
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
	//ī�忡 ���� ����� �޸��� 
	switch (card.getCardNumber())
	{
		//����...


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
