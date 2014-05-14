#pragma once
#include"Point.h"
#include<memory>
#include"header.h"

class Battle_Unit;
class kwMoving;

class kwMsg_Action
{
public:
	//��ǥŸ��... �̵��Ҷ��� �ʿ��ϱ� �ϴ�..?
	//���� �̵� �ϴ°�? �̵��� �� �ʿ��� ������? ��� �̵��ϴ°�?
	//�� �������� ���͸� �� Ȱ���ؾ� �� �� ����...
	//�ٽ� �ٲ��� �ƹ��� �����ص� �ʹ� �����ϴ°� ����. ���� ���¸� ������...
	//�̵�,���,��ɵ��� �����ϰ� �ٲܷ��� �̰� ��ü�� �����ϴ� ������ ����
	
	//������ Ÿ���� ������ ���⼭ ���ݴ���� tag, ��ġ ���� �����Ѵ�.	

	//animation���� ����.
	
	kwMoving                *m_pOwnerMoving;
		
	//Ÿ���� �����Ѵٸ� ���� �ؿ� ���� �־��ְ� ���ٸ� �״�� ���д�. 
	Battle_Unit				*m_pTarget;
	int						 m_iDamage;				
	
	//��Ʈ�������� �Ѵ� ������� 4,5 �����ӿ��� ���� ���ùڽ��� �����Ѵٸ� ..00011000 �̷������� ABFrame���� �����Ѵ�.
	//����� �Լ��� 
	cInt					 m_iABFrame;
	float					 m_fABRemainTime;
	kwMoving				*m_pABMoving;

	CG3Point				 m_vctABforce;
	CG3Point				 m_sizeAB;
	CG3Point				 m_offsetAB;

public:
	kwMsg_Action(
		kwMoving* pOwnerMoving = NULL,
		Battle_Unit* pTarget = NULL,
		int damage = 0 ,
		int abFrame = 0,
		float abRemain = 0.f,
		kwMoving* abMoving = NULL,
		CG3Point vct   = CG3PointZero,
		CG3Point abSize = CG3PointZero,
		CG3Point offset = CG3PointZero);

	~kwMsg_Action();

};