#pragma once
#include<string>
#include"Point.h"
using namespace std;

class Battle_Unit;

class Character_data
{
protected:
	int m_iIndex;		//그냥 넣어놓음;
	string m_szName;
	int m_iAA;
	int m_iDA;
	int m_iSR;
protected:

	CG3Point m_size;//캐릭터의 충돌 크기....?!
	Character_data(){ ; }	//기본 클래스 정의하지 않는다.

public:
	Character_data(int n, string name, int atk, int def, int spd,const CG3Point &size);

	Battle_Unit* makeBU(int kind) const;
};