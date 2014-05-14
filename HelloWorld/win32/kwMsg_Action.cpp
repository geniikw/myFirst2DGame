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
�̰��� ����Ʈ �����ͷ� �����ȴ�. ���� kwMsg_Action�� delete �ɶ��� rc�� 0�� �� ���ε�
�̰����� ������ 10������ �ο� �� �ִ�. ������ �����Ϳ� �Ҵ�� ����ü����
�� �޼����� ������� delete �ϸ� �� ������ ���� ���̴�.
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