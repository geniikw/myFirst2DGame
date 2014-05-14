#include"kwSprite.h"
#include"Manager_Resource.h"
#include"Manager_Global.h"
#include"MotionSet.h"

bool kwSprite::init()
{
	if (!CCSprite::init())return false;

	CCSprite::setAnchorPoint(ccp(0.f, 0.f));
	m_pPosData = NULL;
	m_iTag = CT_UI;
	m_bRender = false;

	return true;
}
bool kwSprite::init(float x, float y, float z)
{
	if (!kwSprite::init())return false;

	m_pPosData = new My3DCube(CG3Point(x, y, z));
	return true;
}
bool kwSprite::init(const CG3Point &size)
{
	 if (!kwSprite::init())return false;
	 
	 m_pPosData = new My3DCube(size);
	 return true;
}

//bool kwSprite::init(float r)
//{
//	if (!kwSprite::init())return false;
//
//	m_pPosData = new My3DEllipse(r);
//	return true;
//}

kwSprite::~kwSprite()
{
	if (m_pPosData != NULL)
		delete m_pPosData;
}

void kwSprite::reMakeCubeData(const CG3Point &shape)
{
	if (m_pPosData != NULL)
		delete m_pPosData;

	m_pPosData = new My3DCube(shape);
}

void kwSprite::refreshPosition()
{
	if (m_pPosData == NULL)
		return;

	//연동시켜 놓자...
	//CGPoint temp = m_pPosData->getDisplayPosition();
	//float temp2 = m_pPosData->getDisplayScale();

	CCSprite::setPosition(m_pPosData->getDisplayPosition() - ccp(m_pPosData->transDisplayUnit(getContentSize().width)/2.f,0));
	CCSprite::setScale(m_pPosData->getDisplayScale());
}

void kwSprite::addPosition(const CG3Point &pos)
{
	m_pPosData->addPosition(pos);
}

void kwSprite::setPosition(const CG3Point &pos)
{
	m_pPosData->setPosition(pos);
}

bool kwSprite::AABBCheck(const kwSprite &target) const
{   //충돌체크를 한닷...
	return MYUnit::AABBCheckByPoint(m_pPosData, target.getPosData());
}

//override
void kwSprite::draw()
{
	if (Manager_Global::getInstance()->g_iRenderFlag == true)
		CCSprite::draw();

	if (Manager_Global::getInstance()->g_iDebugFlag == 0)
	{
		return;
	}

	if (m_pPosData != NULL)
	{
		m_pPosData->cc3dDrawInSP(getPosition() - Manager_Global::getInstance()->g_offsetGameScroll, getScale());
	}
}

void kwSprite::addChild(kwSprite *child)
{
	CCSprite::addChild(child);

	if (this->m_pPosData->getMapData() != NULL)
	{
		child->m_pPosData->setMapData(this->m_pPosData->getMapData());
	}
}

CG3Point kwSprite::get3DRightSide(int option) const
{//미완성
	if (m_pPosData == NULL)
		return CG3Point(0.f, 0.f, 0.f);

	return get3DPosition(option) + CG3Point(m_pPosData->getXLength(), 0.f, 0.f) / 2 + CG3Point(30.f, 0.f, 0.f);
}

CG3Point kwSprite::get3DLeftSide(int option) const
{//미완성
	if (m_pPosData == NULL)
		return CG3Point(0.f, 0.f, 0.f);

	return get3DPosition(option) - CG3Point(m_pPosData->getXLength(), 0.f, 0.f) / 2 - CG3Point(30.f, 0.f, 0.f);
}

///ANIMAION FUNCTION///
void kwSprite::setResourceWithString(string resName)
{
	CCTexture2D *res = Manager_Resource::getInstance()->getResourceWithString(resName);

	MotionSet set(&string2wstring(resName));
	gl2DFrame temp;
	CCAnimation* ani = NULL;
	WCHAR buf[64];
	m_bRender = true;
	for (int n = 0; n < set.m_pMotions.size(); n++)
	{
		temp = set.m_pMotions[n];
		ani = new CCAnimation;
		lstrcpy(buf, set.m_pMotions[n].motionName.c_str());
		
		char* tempBuf = wtoa(buf);
		ani->initWithName(tempBuf);
		delete tempBuf;

		for (int i = 0; i < temp.frame.size(); i++)
			ani->addFrameWithTexture(res, temp.frame[i]);

		this->addAnimation(ani);	
	}
}

CG3Point kwSprite::get3DPosition(int option) const
{	
	CG3Point res = m_pPosData->getPosition();
	
	if (option == 1)
		res.z = 0.f;

	return res;
}

CG3Point operator>>(const kwSprite& start, const kwSprite &dest)
{
	CG3Point vect = dest.get3DPosition() - start.get3DPosition();
	vect = vect.getUnitVector();
	return vect;
}

CG3Point kwSprite::getInsideRandPosition()
{
	return CG3Point(0, 0, 0);
}