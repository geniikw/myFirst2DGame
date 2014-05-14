#include"Object_Hero.h"
#include"Manager_Resource.h"
#include"Manager_Global.h"

#include"MotionSet.h"
#include"header.h"


//부모클래스로 접근하기 위한...
#include"SceneTown.h"

Object_Hero::Object_Hero()
{
	//다이나믹 무빙
	m_destPosition = ccp(0, 0);

	//기본
	m_fSpeed = 200.f;
	m_iState = CSTATE_IDLE;
	m_iprvState = CSTATE_VOID;
	m_iSpeech = SPEECH_VOID;
	
	memset(m_szStateBuf, NULL, sizeof(m_szStateBuf));
	strcpy(m_szStateBuf, "IDLE1");
	
	m_pDeco = NULL;
	
	m_fFrameTime = 0.f;
	m_fFrameMaxTime = 0.0f;
	
	m_iFrameNumber = 0.f;
	m_iFrameMaxNumber = 0;
}

bool Object_Hero::init(wstring name)
{
	if (!CCSprite::init()) return false;

	//이미지 파일을 불러옴
	CCTexture2D *res = Manager_Resource::getInstance()->getResourceWithString(
		wstring2string(name));
	
	//애니메이션 뒤에 2가 있으면 얘한테 add함.
	m_pDeco = new CObject_Deco;
	if(!m_pDeco->init()) return false;

	this->addChild(m_pDeco);

	//모션파일을 불러와서 사용함 ㅇㅇ;
	MotionSet set(&name);  //custom class for motion data file format
	gl2DFrame temp;
	wchar_t buf[64];
	CCAnimation *ani = NULL;
	for (int n = 0; n < set.m_pMotions.size(); n++)
	{
		temp = set.m_pMotions[n];
		ani = new CCAnimation;
		lstrcpy(buf,set.m_pMotions[n].motionName.c_str());
		
		char *tempBuf = wtoa(buf);
		ani->initWithName(tempBuf);
		delete tempBuf;

		for (int i = 0; i < temp.frame.size(); i++)
				ani->addFrameWithTexture(res,temp.frame[i]);

		if (wcschr(buf, '2'))
		{
			m_pDeco->addAnimation(ani);
		}
		else
		{
			this->addAnimation(ani);
		}
	}

	//말풍선 상태를 초기화함.
	m_pSpeech = new CObject_Deco;
	m_pSpeech->initWithTextureName("DecoSpeech");
	m_pSpeech->setPosition(ccp(30, 100));
	this->addChild(m_pSpeech);

	//vector<string> p = this->m_pAnimations->allKeys();  //안에 뭐있나~

	this->schedule(schedule_selector(Object_Hero::tick));
	return true;
}
void Object_Hero::tick(ccTime dt)
{
	//동작은 밖에서 
	SceneTown *p = (SceneTown*)this->getParent();
	m_iSpeech = (ENUM_SPEECH)p->searchTown(this->getPosition());
	//말풍선표를 바꿔줌...

	if (p->getConstroll() == this)
	{
		//컨트롤권한이 히어로일때만 동작
		m_iState = CSTATE_IDLE;
		if (GetAsyncKeyState(VK_RIGHT))
		{
			m_destPosition.x += dt * m_fSpeed;
			m_iState = CSTATE_RUN;
			this->setFlipX(true);
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			m_destPosition.x -= dt * m_fSpeed;
			m_iState = CSTATE_RUN;
			this->setFlipX(false);
		}

		if (GetAsyncKeyState(VK_UP))
		{
			if (m_iSpeech != SPEECH_VOID && m_iState == CSTATE_IDLE)
			{
				if (m_iSpeech == SPEECH_STORE)
					popUpStore();

				if (m_iSpeech == SPEECH_MENU)
					popUpMenu();
			}
		}
	}
	//다이나믹 무빙.
	CGPoint pos = this->getPosition();
	if (pos.x != m_destPosition.x)
	{
		int dif = pos.x - m_destPosition.x;
		this->setPosition(ccp(pos.x - dif / 16, pos.y));
	}

	//애니메이션 프레임을 설정함
	animation(dt);
	//설정된 애니메이션을 세팅함
	this->setDisplayFrame(m_szStateBuf, m_iFrameNumber);
}

void Object_Hero::animation(ccTime dt)
{
	if (m_iState != m_iprvState)
	{	
		m_fFrameTime = 0.f;
		m_iFrameNumber = 0;

		if (m_iState == CSTATE_IDLE && m_iprvState == CSTATE_RUN)
		{//서있을때 -> 달림
			m_iprvState = m_iState;
			strcpy_s(m_szStateBuf, "RUNE");
			m_fFrameMaxTime = 0.1f;
			m_iFrameMaxNumber = this->animationByName("RUNE")->getFrames()->count() - 1;
			return;
		}

		m_iprvState = m_iState;

		switch (m_iState)
		{
		case CSTATE_IDLE:
		{
							strcpy_s(m_szStateBuf, "IDLE1");
							m_fFrameMaxTime = 0.1f;
							m_iFrameMaxNumber = this->animationByName("IDLE1")->getFrames()->count() - 1;
							return;
		}
		case CSTATE_RUN:
		{
						   strcpy_s(m_szStateBuf, "RUNS");
						   m_fFrameMaxTime = 0.04f;
						   m_iFrameMaxNumber = this->animationByName("RUNS")->getFrames()->count() - 1;
						   return;
		}
		}
	}

	//프레임 타임을 증가시키고 일정수가 넘어가면 프레임 넘버를 올린다.
	m_fFrameTime += dt;
	if (m_fFrameTime > m_fFrameMaxTime)
	{
		if (++m_iFrameNumber > m_iFrameMaxNumber)
		{
			if (!strcmp(m_szStateBuf, "RUNS"))
			{
				m_fFrameTime = 0.f;
				strcpy_s(m_szStateBuf, "RUNM");
				m_fFrameMaxTime = 0.1f;
				m_iFrameMaxNumber = this->animationByName("RUNM")->getFrames()->count() - 1;
			}

			if (!strcmp(m_szStateBuf, "RUNE"))
			{
				m_fFrameTime = 0.f;
				strcpy(m_szStateBuf, "IDLE1");
				m_fFrameMaxTime = 0.1f;
				m_iFrameMaxNumber = this->animationByName("IDLE1")->getFrames()->count() - 1;
			}
				

			m_iFrameNumber = 0;
		}
		m_fFrameTime = 0.f;
	}
}

void Object_Hero::popUpStore()
{
	//SceneTown *p = (SceneTown*) this->getParent();
	//p->setFade(200);
	
}

void Object_Hero::popUpMenu()
{
	SceneTown *p = (SceneTown*) this->getParent();
	p->SwapMenuHero();//컨트롤 가져감...
}

void Object_Hero::setPassivePosition(CGPoint pos)
{
	CCSprite::setPosition(pos);
	m_destPosition = pos;
}