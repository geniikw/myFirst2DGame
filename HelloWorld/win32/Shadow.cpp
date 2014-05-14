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
		MessageBoxA(NULL, "그림자가 설정되지 않았습니다.", "에러", MB_OK);
	}
	m_pShadow->setIsVisible(bv);
}

Shadow::~Shadow()
{
	if (m_pShadow != NULL)
		delete m_pShadow;

}
	