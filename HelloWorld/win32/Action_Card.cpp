#include"Action_Card.h"
#include"header.h"
#include"Manager_Resource.h"

Action_Card::Action_Card(int CardNumber)
{
	init();
	CCAnimation *pAni = new CCAnimation;

	pAni->initWithName("CARD");
	
	for (int n = 0; n < MAX_CARD_NUMBER; n++)
	{
		pAni->addFrameWithTexture(Manager_Resource::getInstance()->getResourceWithString("ACardRes"), CGRect(70*n,0,70,100));
	}
	this->addAnimation(pAni);

	if (CardNumber < AC_NOCARD_BACK)
		setCardNumber(CardNumber);
}

void Action_Card::setCardAngle(float angle)
{

	if (angle < 90.f)
	{
		setDisplayFrame("CARD", m_iCardNumber);
		setScaleX(linear(1, 0, angle, 90.f));
	}
	else if (angle < 180.f)
	{
		setDisplayFrame("CARD", 0);
		angle = angle - 90.f;
		setScaleX(linear(0, 1, angle, 90.f));
	}
	else if (angle < 270.f)
	{
		setDisplayFrame("CARD", 0);
		angle = angle - 180.f;
		setScaleX(linear(1, 0, angle, 90.f));
	}
	else if (angle < 360.f)
	{
		setDisplayFrame("CARD", m_iCardNumber);
		angle = angle - 270.f;
		setScaleX(linear(0, 1, angle, 90.f));
	}
}

void Action_Card::setCardNumber(int CardNumber)
{
	if (m_iCardNumber == 0)
	{
		errorBOX("0번카드는 없다.-_-q");
	}
	m_iCardNumber = CardNumber;
	setDisplayFrame("CARD", m_iCardNumber);
}
