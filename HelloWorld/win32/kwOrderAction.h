#pragma once
#include<memory>
using namespace std;

#include"kwOrder.h"
#include"Point.h"

class kwMsg_Action;
class kwMsg_Ani;
class Battle_Unit;


//�׼��� ���� ������ �ִϸ��̼��� ���� ����Ǵ°��̴�.
class kwOrderAction : public kwOrder
{
	 shared_ptr<kwMsg_Action> m_pActionMsg; 
	 shared_ptr<kwMsg_Ani>	  m_pAniMsg;	

public:
	kwOrderAction(
		Battle_Unit *,
		shared_ptr<kwMsg_Action>,
		shared_ptr<kwMsg_Ani>);

	~kwOrderAction();
	bool execute(ccTime dt);

	static kwOrderAction* makeActionOrder(
		Battle_Unit *,
		shared_ptr<kwMsg_Action>,
		shared_ptr<kwMsg_Ani>);
};