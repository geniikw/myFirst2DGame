#include"CObject_Deco.h"
#include"Object_Hero.h"
#include"Manager_Resource.h"

bool CObject_Deco::init()
{
	if (!CCSprite::init()) return false;

	m_PointOffset = ccp(0, 0);
	schedule(schedule_selector(CObject_Deco::tick));
	return true;
}

void CObject_Deco::tick(float dt)
{
	if (m_szWhat.size() == 0)
		return;
	
	Object_Hero *p = (Object_Hero*)this->getParent();
	//히어로에 종속되어버림...deco..
	
	int n = p->getiSpeech();
	this->setDisplayFrame(m_szWhat.c_str(), n);
}

bool CObject_Deco::initWithTextureName(string name)
{
	// Speech로 들어오면 Speech1 Speech2 Speech3 이런식으로 add 하다가 NULL이 나오면 종료
	if (!CObject_Deco::init()) return false;

	CCAnimation *ani = new CCAnimation;
	ani->initWithName(name.c_str());

	m_szWhat = name;

	CCTexture2D *res = (CCTexture2D*)1; //좀 위험한것 같다....
	CGRect rect = CGRectZero;
	char buf[3];
	for (int n=0 ; res != NULL;n++)
	{
		sprintf(buf, "%d", n);
		res = Manager_Resource::getInstance()->
			getResourceWithString(name.append(buf));
		if (res != NULL)
		{
			rect.size = res->getContentSize();
			ani->addFrameWithTexture(res, rect);
		}
		name.pop_back();
	}
	
	this->addAnimation(ani);
	return true;
}