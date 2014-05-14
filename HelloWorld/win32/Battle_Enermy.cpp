#include"Battle_Enermy.h"

#include"BackGroundSprite.h"
#include"kwMsg_Ani.h"
#include"kwMsg_Action.h"
#include"kwMoving_Vector.h"

Battle_Enermy::Battle_Enermy(int cTag)
{
	init();

	this->setStatus(100, 10, SR_A, 5, 5, 4);
	this->reMakeCubeData(CG3Point(40, 6, 80));
	setTag(cTag);
	this->autorelease();
	this->setResourceWithString("meirin");

	for (int n = 0; n < 4; n++)
	{
		m_listCard[n].push_back(Action_Card(AC_MOVE));
		m_listCard[n].push_back(Action_Card(AC_ATTACK1));
		m_listCard[n].push_back(Action_Card(AC_ATTACK1 + n + 1));
	}
}

void Battle_Enermy::doCard(const Action_Card &card)
{
	CG3Point moveFrontPoint;
	CG3Point moveBackPoint;
	Battle_Unit *pUnit = (*m_pMap->getArrayPointerByTag(CT_HERO))[rand() % m_pMap->getArrayPointerByTag(CT_HERO)->size()];

	bool isRight = this->get3DPosition().x - pUnit->get3DPosition().x < 0.f;
	float x;

	if (isRight)
	{
		x = 1;
		moveFrontPoint = pUnit->get3DLeftSide(1);
		moveBackPoint = pUnit->get3DRightSide(1);
	}
	else
	{
		x = -1;
		moveFrontPoint = pUnit->get3DRightSide(1);
		moveBackPoint = pUnit->get3DLeftSide(1);
	}

	switch (card.getCardNumber())
	{
		case AC_MOVE:
		{
						m_listOrder.push_back(kwOrderMoveToPoint::makekwOrderMoveToPoint(this, moveFrontPoint, 100.f, 200.f, 400.f, shared_ptr<kwMsg_Ani>(new kwMsg_Ani(CAT_RUN, 0, 2, 0, 0.1f))));
						break;
		}
		case AC_BACKSTEP:
		{
							m_listOrder.push_back(kwOrderMoveToPoint::makekwOrderMoveToPoint(
								this,
								moveBackPoint
								, 100.f, 200.f, 400.f, shared_ptr<kwMsg_Ani>(new kwMsg_Ani(CAT_RUN, 0, 2, 0, 0.1f))));

							break;
		}
		case AC_ATTACK1:
		{
						   m_listOrder.push_back(
							   kwOrderAction::makeActionOrder(
							   this,
							   shared_ptr<kwMsg_Action>(
							   new kwMsg_Action(
							   NULL,//new kwMoving_Vector(this, 100.f, CG3Point(1,0,0)),
							   pUnit,
							   10,
							   combineInt(1, 2),
							   1.f,
							   NULL,//new kwMoving_Vector(this, 100.f, CG3Point(1, 0, 0)),
							   CG3Point(x * 200, 0, 100),
							   CG3Point(20, 50, 40),
							   CG3Point(0, 0, 50.f)
							   )),
							   shared_ptr<kwMsg_Ani>(new kwMsg_Ani(CAT_ATTACK1, 0, 0, 0, 0.1f))
							   ));

						   break;
		}
		case AC_ATTACK2:
		{
						   m_listOrder.push_back(
							   kwOrderAction::makeActionOrder(
							   this,
							   shared_ptr<kwMsg_Action>(
							   new kwMsg_Action(
							   NULL,//new kwMoving_Vector(this, 100.f, CG3Point(1,0,0)),
							   pUnit,
							   20,
							   combineInt(1, 1),
							   1.f,
							   NULL,//new kwMoving_Vector(this, 100.f, CG3Point(1, 0, 0)),
							   CG3Point(x * 20, 0, 100),
							   CG3Point(20, 50, 40),
							   CG3Point(0, 0, 50.f)
							   )),
							   shared_ptr<kwMsg_Ani>(new kwMsg_Ani(CAT_ATTACK2, 0, 0, 0, 0.1f))
							   ));

						   break;
		}
		case AC_ATTACK3:
		{
						   m_listOrder.push_back(
							   kwOrderAction::makeActionOrder(
							   this,
							   shared_ptr<kwMsg_Action>(
							   new kwMsg_Action(
							   NULL,//new kwMoving_Vector(this, 100.f, CG3Point(1,0,0)),
							   pUnit,
							   30,
							   combineInt(1, 5),
							   1.f,
							   NULL,//new kwMoving_Vector(this, 100.f, CG3Point(1, 0, 0)),
							   CG3Point(x * 50, 0, 150),
							   CG3Point(20, 50, 40),
							   CG3Point(0, 0, 50.f)
							   )),
							   shared_ptr<kwMsg_Ani>(new kwMsg_Ani(CAT_ATTACK3, 0, 0, 0, 0.1f))
							   ));

						   break;
		}
		case AC_ATTACK4:
		{
						   m_listOrder.push_back(
							   kwOrderAction::makeActionOrder(
							   this,
							   shared_ptr<kwMsg_Action>(
							   new kwMsg_Action(
							   NULL,//new kwMoving_Vector(this, 100.f, CG3Point(1,0,0)),
							   pUnit,
							   40,
							   combineInt(1, 5),
							   0.1f,
							   NULL,//new kwMoving_Vector(this, 100.f, CG3Point(1, 0, 0)),
							   CG3Point(x * 10, 0, 50),
							   CG3Point(40, 80, 80),
							   CG3Point(0, 0, 50.f)
							   )),
							   shared_ptr<kwMsg_Ani>(new kwMsg_Ani(CAT_ATTACK4, 0, 0, 0, 0.04f))
							   ));
						   break;
		}
		case AC_ATTACK5:
		{

						   m_listOrder.push_back(
							   kwOrderAction::makeActionOrder(
							   this,
							   shared_ptr<kwMsg_Action>(
							   new kwMsg_Action(
							   NULL,//new kwMoving_Vector(this, 100.f, CG3Point(1,0,0)),
							   pUnit,
							   50,
							   combineInt(1, 8),
							   1.f,
							   new kwMoving_Vector(this, 500.f, CG3Point(x, 0, 0)),
							   CG3Point(x * 10, 0, 100),
							   CG3Point(40, 80, 80),
							   CG3Point(0, 0, 50.f)
							   )),
							   shared_ptr<kwMsg_Ani>(new kwMsg_Ani(CAT_ATTACK5, 0, 0, 0, 0.1f))
							   ));
						   break;
		}
		case AC_NOCARD_BACK:
		{
							   m_listOrder.push_back(kwOrderMoveToPoint::makekwOrderMoveToPoint(this, this->getinitPosition(), 100.f, 200.f, 400.f, shared_ptr<kwMsg_Ani>(new kwMsg_Ani(CAT_WALK, 0, 0, 0, 0.1f))));
							   break;
		}
	}
}