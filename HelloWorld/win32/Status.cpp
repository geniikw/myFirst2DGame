#include"Status.h"

Status::Status()
{
	m_iMaxHP = 1000;
	m_iHP	 = 1000;
	m_iAA	 = 100;
	m_iDA	 = 10;
	m_iSR	 = 4;
}

Status::Status(int atk, int def, int agi, int abp, int app, int ar)
{
	m_iAA = atk;
	m_iDA = def;
	m_iSR = agi;
	m_iActionBasePoint = abp;
	m_iActionPlusPoint = app;
	m_iActionRank = ar;
}
void Status::setStatus(int atk, int def, int agi, int abp, int app, int ar)
{
	m_iAA = atk;
	m_iDA = def;
	m_iSR = agi;
	m_iActionBasePoint = abp;
	m_iActionPlusPoint = app;
	m_iActionRank = ar;
}