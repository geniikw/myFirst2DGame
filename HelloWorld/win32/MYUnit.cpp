#include"MYUnit.h"
#include"myUnitHeader.h"
#include"header.h"

MYUnit::MYUnit()
{
	m_pMapData = NULL;
	m_pos = CG3Point(0.f, 0.f, 0.f);

	m_bMapDataMakerFlag = false;
	m_Anchor = CG3Point(0.f,0.f,0.f);
}

MYUnit::~MYUnit()
{	
	if (m_bMapDataMakerFlag == true)
		delete m_pMapData;
}

float MYUnit::getTilt(float anchor)
{
	if (m_pMapData == NULL)
		return 0.f;
	else
		return ((m_pMapData->fMapWidth - m_pMapData->fMapWidth * m_pMapData->fSizeRate)
									*anchor)
			/ m_pMapData->fMapHeight / m_pMapData->fSizeRate;
}

#include"Manager_Global.h"
CGPoint MYUnit::getDisplayPosition(int option)
{
	if (option == 0)
		return transDisplayPosition(m_pos.x, m_pos.y, m_pos.z) + Manager_Global::getInstance()->g_offsetGameScroll;
	if (option == 1)//그림자
		return transDisplayPosition(m_pos.x + m_pos.z / 2, m_pos.y + m_pos.z / 2, 0.f) + Manager_Global::getInstance()->g_offsetGameScroll;


}

float MYUnit::getDisplayScale()
{
	if (m_pMapData == NULL)
		return 1.f;//원본크기 리턴.

	return linear(1, m_pMapData->fSizeRate, m_pos.y, m_pMapData->fMapHeight);
}

CGPoint MYUnit::transDisplayPosition(float x, float y, float z)
{
	if (m_pMapData == NULL)
		return ccp(x, y);
	
	CGPoint temp;
	float tempRate = linear(1, 0, y, screenHeight);
	temp.x = 
		linear(
		getTilt(m_pMapData->fCenterTilt), 
		-getTilt(1 - m_pMapData->fCenterTilt), 
		x, 
		m_pMapData->fMapWidth) * tempRate * y + x;
	temp.y = (y + z) * tempRate;
	return temp;

	//ver 0.1
	//temp.x = linear(getTilt(), -getTilt(), x, m_pMapData->fMapWidth) * y * m_pMapData->fSizeRate + x;
	
	//ver 0.2
	//temp.y = m_pMapData->fSizeRate * y + linear(1, m_pMapData->fSizeRate, y, m_pMapData->fMapHeight) * z;
	//개선안...

	//ver 1.0
	//temp.y = linear(y, y*m_pMapData->fSizeRate, y, m_pMapData->fMapHeight * 2) 
	//		+ linear(1, m_pMapData->fSizeRate, y, m_pMapData->fMapHeight) * z;

	//통합 버젼 1
	//temp.x = linear(getTilt(), -getTilt(), x, m_pMapData->fMapWidth) * linear(y, y*m_pMapData->fSizeRate, y, m_pMapData->fMapHeight * 2) * m_pMapData->fSizeRate + x;

	//temp.y = linear(y, y*m_pMapData->fSizeRate, y, m_pMapData->fMapHeight * 2)
	//	+ linear(1, m_pMapData->fSizeRate, y, m_pMapData->fMapHeight)* z;
}

void MYUnit::addPosition(const CG3Point &add)
{
	m_pos.x += add.x;
	m_pos.y += add.y;
	m_pos.z += add.z;
}

void MYUnit::setSizeRate(float rate)
{
	//선언자 아니면 out
	if (m_bMapDataMakerFlag == 0)
		return;

	//혹시라도 NULL이면 out
	if (m_pMapData == NULL )
		return;

	m_pMapData->fSizeRate = rate;
}

void MYUnit::makeMapData(float w, float h, float rate,float anchor)
{
	m_pMapData = new mapData;

	if (m_pMapData == NULL)
		return;

	m_bMapDataMakerFlag = 1;
	m_pMapData->fMapHeight = h;
	m_pMapData->fMapWidth = w;
	m_pMapData->fSizeRate = rate;
	m_pMapData->fCenterTilt = anchor;
}
//static function
bool MYUnit::AABBCheck(const MYUnit& cube1, const MYUnit& cube2)
{
	return !(cube1.MYUnitGetMinX() > cube2.MYUnitGetMaxX() ||
		cube2.MYUnitGetMinX() > cube1.MYUnitGetMaxX() ||
		cube1.MYUnitGetMinY() > cube2.MYUnitGetMaxY() ||
		cube2.MYUnitGetMinY() > cube1.MYUnitGetMaxY() ||
		cube1.MYUnitGetMinZ() > cube2.MYUnitGetMaxZ() ||
		cube2.MYUnitGetMinZ() > cube1.MYUnitGetMaxZ());
}
bool MYUnit::AABBCheckByPoint(MYUnit* cube1, MYUnit* cube2)
{
	return !(cube1->MYUnitGetMinX() > cube2->MYUnitGetMaxX() ||
		cube2->MYUnitGetMinX() > cube1->MYUnitGetMaxX() ||
		cube1->MYUnitGetMinY() > cube2->MYUnitGetMaxY() ||
		cube2->MYUnitGetMinY() > cube1->MYUnitGetMaxY() ||
		cube1->MYUnitGetMinZ() > cube2->MYUnitGetMaxZ() ||
		cube2->MYUnitGetMinZ() > cube1->MYUnitGetMaxZ());
}

bool SphereCheck(const MYUnit& cube1, const MYUnit& cube2)
{
	return cube1.getRadius() + cube2.getRadius() > ccp3Distance(cube1.getPosition(), cube2.getPosition());
}
bool SphereSCheckByPoint(MYUnit* cube1, MYUnit* cube2)
{
	return cube1->getRadius() + cube2->getRadius() > ccp3Distance(cube1->getPosition(), cube2->getPosition());
}