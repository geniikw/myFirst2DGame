#pragma once
#include"kwOrder.h"

#include<memory>

class Battle_Unit;
class kwMsg_Ani;
class kwMoving_Vector;

//���Ǹ� Ȯ���� �ؾ��Ѵ�. �̰��� ��ǥ������ �����ϰ� �ش��ϴ� ��ǥ��������
//�ش��ϴ� ĳ���Ͱ� �����ӵ��� �̵��ϴ� �Լ��̴�. �׷��� ������ 
//�̷�������� �ϸ� ĳ���Ͱ� ���� �ӵ��� �̵��Ҷ��� �Ǵ��� �� ���ٴ� ���̴�.
//���� �� ����(?)�� speed�� �ֱ�� �ߴ�.
//�̷��� ó���ϸ� orderMove��� ��ü�� status���� ���ӵǴ°� ���� �� �ִ�.



//���� ���ӵ��� 0���� �ϸ� �ش� �ϴ� ���ӵ��� ���� ����
class kwOrderMoveToPoint : public kwOrder
{
//�ʿ��� ����...
	
	int					  m_iPhase;// 0 ���� 1�ְ�� 2����

	CG3Point			  m_dest;//������... ��...-_-

	float				  m_fStartAcceleration;
	float				  m_fEndAccelaration;
	float				  m_fMaxSpeed;
	shared_ptr<kwMsg_Ani> m_pMsgAni;

private://���ο��� ���Ǵ� ����...
	//�̰� owner���� ����Ǹ鼭 owner�� �����Ŵ ����� ������ delete
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


