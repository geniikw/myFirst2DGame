#include"kwMsg_Action.h"

#include"Battle_Unit.h"

kwMsg_Action::kwMsg_Action(
	kwMoving* pOwnerMoving,
	Battle_Unit* pTarget,
	int damage,
	int abFrame,
	float abRemain,
	kwMoving* abMoving,
	CG3Point vct,
	CG3Point abSize ,
	CG3Point offset)
:m_pOwnerMoving(pOwnerMoving),
m_pTarget(pTarget),
m_iDamage(damage),
m_iABFrame(abFrame),
m_fABRemainTime(abRemain),
m_pABMoving(abMoving),
m_vctABforce(vct),
m_sizeAB(abSize),
m_offsetAB(offset)
{
	
}


/*
이것은 스마트 포인터로 관리된다. 따라서 kwMsg_Action이 delete 될때는 rc가 0이 될 때인데
이것으로 지온은 10년은더 싸울 수 있다. 내부의 포인터에 할당된 구조체들은
이 메세지가 사라질때 delete 하면 별 문제가 없을 것이다.
*/
kwMsg_Action::~kwMsg_Action()
{
	if (m_pOwnerMoving != NULL)
		delete m_pOwnerMoving;

	if (m_pTarget != NULL)
		delete m_pTarget;

	if (m_pABMoving != NULL)
		delete m_pABMoving;
}

//{
//
//
//}