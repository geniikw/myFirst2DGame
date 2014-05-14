#pragma once
#include"kwOrder.h"

#include<memory>
class kwMsg_Action;
class Battle_Unit;

//이 클래스는 액션 메세지를 받아서 총알을 만든다음 바로 지워진다.
class kwOrderMakeBullet : public kwOrder
{
	shared_ptr<kwMsg_Action> m_pActionMsg;
public:

	kwOrderMakeBullet(Battle_Unit *pOwner, shared_ptr<kwMsg_Action> pAction);
	virtual bool execute(ccTime dt);
};