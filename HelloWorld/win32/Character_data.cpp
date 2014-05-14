#include"Character_data.h"
#include"Battle_Unit.h"
#include"Manager_Resource.h"

Character_data::Character_data
(int index, string name, int atk, int def, int spd,const CG3Point &size)
{
	m_iIndex = index;  
	m_szName = name;
	m_iAA = atk;
	m_iDA = def;
	m_iSR = spd;



	//ĳ������ ũ��
	m_size = size;
}

Battle_Unit* Character_data::makeBU(int kind) const
{
	Battle_Unit* temp = new Battle_Unit();

	temp->setStatus(m_iAA, m_iDA, m_iSR,0,0,0);
	temp->reMakeCubeData(m_size);
	temp->setTag(kind);
	temp->autorelease();
	//�������� ���� ������ �ϴ� �����Ͱ� ����...
	

	return temp;
}