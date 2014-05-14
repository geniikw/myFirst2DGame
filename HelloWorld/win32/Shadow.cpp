#include"Shadow.h"
#include"BackGroundSprite.h"

Shadow::Shadow()
{
	m_pShadow = NULL;
	m_fAngle  = 0.f;
	m_fYScale = 0.f;
}

bool Shadow::makeShadow(float anchor)
{
	m_pShadow = new CCSprite;
	if (!m_pShadow->init())
		return false;

	m_pShadow->autorelease();
	m_pShadow->setColor(ccc3(0, 0, 0));
	m_pShadow->setAnchorPoint(ccp(0.5, 0));
	m_pShadow->getCamera()->setCenterXYZ(0.f, 1.f, 0.f);

	getBackGround()->CCSprite::addChild(m_pShadow, -100);

	return true;
}

void Shadow::setShadowIsVisible(bool bv)
{
	if (m_pShadow == NULL)
	{
		MessageBoxA(NULL, "�׸��ڰ� �������� �ʾҽ��ϴ�.", "����", MB_OK);
	}
	m_pShadow->setIsVisible(bv);
}

Shadow::~Shadow()
{
	if (m_pShadow != NULL)
		delete m_pShadow;

}
	