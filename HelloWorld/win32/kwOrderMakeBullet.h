#pragma once
#include"kwOrder.h"

#include<memory>
class kwMsg_Action;
class Battle_Unit;

//�� Ŭ������ �׼� �޼����� �޾Ƽ� �Ѿ��� ������� �ٷ� ��������.
class kwOrderMakeBullet : public kwOrder
{
	shared_ptr<kwMsg_Action> m_pActionMsg;
public:

	kwOrderMakeBullet(Battle_Unit *pOwner, shared_ptr<kwMsg_Action> pAction);
	virtual bool execute(ccTime dt);
};