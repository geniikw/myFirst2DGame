#pragma once

#include<vector>

class Status
{	//기본적인 status를 관리함 ㅇㅇ;;
protected:
	int m_iMaxHP; //MaxHitPoint
	int m_iHP; //HitPoint
	int m_iAA; //attack ability
	int m_iDA; //defence ability
	int m_iSR; //speed rank

	//version 1.01
	int m_iActionBasePoint; //각각의 행동슬롯이 기본으로 가지고 있는 기본 포인트
	int m_iActionPlusPoint; //기본 포인트가 전부 사용한후 추가로 쓸 수 있는 포인트 
	int m_iActionRank;      //행동할 수 있는 수 

public:
	Status();
	Status(int atk, int def, int agi, int abp, int app, int ar);

	void setStatus(int a,int d, int s,int abp,int app,int ar);//HP는 전부 1000으로 고정.. 일단 말이지 ㅇㅇ;
};