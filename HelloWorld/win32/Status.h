#pragma once

#include<vector>

class Status
{	//�⺻���� status�� ������ ����;;
protected:
	int m_iMaxHP; //MaxHitPoint
	int m_iHP; //HitPoint
	int m_iAA; //attack ability
	int m_iDA; //defence ability
	int m_iSR; //speed rank

	//version 1.01
	int m_iActionBasePoint; //������ �ൿ������ �⺻���� ������ �ִ� �⺻ ����Ʈ
	int m_iActionPlusPoint; //�⺻ ����Ʈ�� ���� ������� �߰��� �� �� �ִ� ����Ʈ 
	int m_iActionRank;      //�ൿ�� �� �ִ� �� 

public:
	Status();
	Status(int atk, int def, int agi, int abp, int app, int ar);

	void setStatus(int a,int d, int s,int abp,int app,int ar);//HP�� ���� 1000���� ����.. �ϴ� ������ ����;
};