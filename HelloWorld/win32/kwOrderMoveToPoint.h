#pragma once
#include"kwOrder.h"

#include<memory>

class Battle_Unit;
class kwMsg_Ani;
class kwMoving_Vector;

//정의를 확실히 해야한다. 이것은 목표지점을 설정하고 해당하는 목표지점으로
//해당하는 캐릭터가 가진속도로 이동하는 함수이다. 그런데 문제는 
//이런방식으로 하면 캐릭터가 빠른 속도로 이동할때를 판단할 수 없다는 것이다.
//따라서 본 필자(?)는 speed를 넣기로 했다.
//이렇게 처리하면 orderMove라는 객체가 status에서 종속되는걸 막을 수 있다.



//만약 가속도를 0으로 하면 해당 하는 가속도는 쓰지 않음
class kwOrderMoveToPoint : public kwOrder
{
//필요한 정보...
	
	int					  m_iPhase;// 0 가속 1최고속 2감속

	CG3Point			  m_dest;//목적지... 흠...-_-

	float				  m_fStartAcceleration;
	float				  m_fEndAccelaration;
	float				  m_fMaxSpeed;
	shared_ptr<kwMsg_Ani> m_pMsgAni;

private://내부에서 사용되는 정보...
	//이게 owner에서 실행되면서 owner를 실행시킴 명령이 끝나면 delete
	kwMoving_Vector *m_pMovingStragith;

public:
	kwOrderMoveToPoint(Battle_Unit *owner, 
		CG3Point dest, 
		float sa,float ea,float speed, 
		shared_ptr<kwMsg_Ani> pMsgAni);

	virtual bool execute(ccTime dt);

	static kwOrder* makekwOrderMoveToPoint(
		Battle_Unit* owner, 
		const CG3Point &dest,
		float sa, float ea, float speed,
		shared_ptr<kwMsg_Ani> pMsgAni);
};


