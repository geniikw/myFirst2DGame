#pragma once
#include<string>
#include"Point.h"
using namespace std;

class Battle_Unit;

class Character_data
{
protected:
	int m_iIndex;		//�׳� �־����;
	string m_szName;
	int m_iAA;
	int m_iDA;
	int m_iSR;
protected:

	CG3Point m_size;//ĳ������ �浹 ũ��....?!
	Character_data(){ ; }	//�⺻ Ŭ���� �������� �ʴ´�.

public:
	Character_data(int n, string name, int atk, int def, int spd,const CG3Point &size);

	Battle_Unit* makeBU(int kind) const;
};