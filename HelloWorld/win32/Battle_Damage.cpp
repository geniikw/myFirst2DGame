#include"Battle_Damage.h"
#include"Manager_Resource.h"
#include"Manager_Global.h"
#include"MotionSet.h"

Battle_Damage::Battle_Damage()
{
	CCSprite::init();
	Battle_Damage::init();

	this->setAnchorPoint(ccp(0, 0));
	schedule(schedule_selector(Battle_Damage::tick));

	CCAnimation *pAni = makeNumbersAnimation();

	for (int n = 0; n < G_MAX_DIGIT; n++)
	{
		m_pNumbers[n] = new CCSprite;
		m_pNumbers[n]->init();
		m_pNumbers[n]->setAnchorPoint(ccp(0.5f, 0.5f));
		m_pNumbers[n]->addAnimation(pAni);
		
		this->addChild(m_pNumbers[n]);
		m_pNumbers[n]->setPosition(ccp(n * 10, 0));
	}

	this->setScale(10.f);
	this->runAction(CCScaleTo::actionWithDuration(0.1f, 1.f, 1.f));
}

void Battle_Damage::init()
{
	m_fOpacity = 255;
	m_color = ccc3(255, 255, 255);

	m_fTimer = 0.f;
	m_Offset = CGPointZero;
}


void Battle_Damage::setUp(CGPoint pos, int Damage, ccColor3B color)
{
	if (Damage > 1000)
	{
		Damage = 1000;
	}
	if (Damage < 0)
	{
		Damage = 0;
	}
	m_bIsUsed = true;
	m_color = color;

	int count = 0;
	for (int n = 0; n < G_MAX_DIGIT; n++)
	{
		if (Damage != 0)
		{
			m_pNumbers[G_MAX_DIGIT - n - 1]->setDisplayFrame("numbers", Damage % 10);
			count++;
		}
		else
		{
			m_pNumbers[G_MAX_DIGIT - n - 1]->setDisplayFrame("numbers", 10);
		}
		Damage /= 10;
		m_pNumbers[G_MAX_DIGIT - n - 1]->setColor(m_color);
	}
	
	m_Offset = ccp(-34 * (3 - count), 120);
	this->setPosition(pos + m_Offset);
}

void Battle_Damage::tick(ccTime dt)
{
	dt = dt * Manager_Global::getInstance()->g_fBattleDT;

	m_fTimer += dt;
	CGPoint pos = getPosition();
	pos = pos + ccp(0, 100) * dt;
	this->setPosition(pos);

	m_fOpacity = m_fOpacity - 100 * dt;
	
	for (int n = 0; n < G_MAX_DIGIT; n++)
	{
		m_pNumbers[n]->setOpacity(m_fOpacity);
	}

	if (m_fTimer > 1.5f)
	{
		this->getParent()->removeChild(this, true);
	}
}

CCAnimation* Battle_Damage::makeNumbersAnimation()
{
	CCTexture2D *res = Manager_Resource::getInstance()->getResourceWithString("numbers");

	MotionSet set(&string2wstring("numbers"));
	gl2DFrame temp;
	CCAnimation* ani = NULL;
	WCHAR buf[64];
	
	temp = set.m_pMotions[0];
	ani = new CCAnimation;

	lstrcpy(buf, set.m_pMotions[0].motionName.c_str());
	char* tempBuf = wtoa(buf);
	ani->initWithName(tempBuf);
	ani->autorelease();
	
	delete tempBuf;

	for (int i = 0; i < temp.frame.size(); i++)
		ani->addFrameWithTexture(res, temp.frame[i]);

	return ani;
}