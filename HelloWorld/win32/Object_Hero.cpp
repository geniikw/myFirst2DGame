#include"Object_Hero.h"
#include"Manager_Resource.h"
#include"Manager_Global.h"

#include"MotionSet.h"
#include"header.h"


//�θ�Ŭ������ �����ϱ� ����...
#include"SceneTown.h"

Object_Hero::Object_Hero()
{
	//���̳��� ����
	m_destPosition = ccp(0, 0);

	//�⺻
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

	//�̹��� ������ �ҷ���
	CCTexture2D *res = Manager_Resource::getInstance()->getResourceWithString(
		wstring2string(name));
	
	//�ִϸ��̼� �ڿ� 2�� ������ ������ add��.
	m_pDeco = new CObject_Deco;
	if(!m_pDeco->init()) return false;

	this->addChild(m_pDeco);

	//��������� �ҷ��ͼ� ����� ����;
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

	//��ǳ�� ���¸� �ʱ�ȭ��.
	m_pSpeech = new CObject_Deco;
	m_pSpeech->initWithTextureName("DecoSpeech");
	m_pSpeech->setPosition(ccp(30, 100));
	this->addChild(m_pSpeech);

	//vector<string> p = this->m_pAnimations->allKeys();  //�ȿ� ���ֳ�~

	this->schedule(schedule_selector(Object_Hero::tick));
	return true;
}
void Object_Hero::tick(ccTime dt)
{
	//������ �ۿ��� 
	SceneTown *p = (SceneTown*)this->getParent();
	m_iSpeech = (ENUM_SPEECH)p->searchTown(this->getPosition());
	//��ǳ��ǥ�� �ٲ���...

	if (p->getConstroll() == this)
	{
		//��Ʈ�ѱ����� ������϶��� ����
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
	//���̳��� ����.
	CGPoint pos = this->getPosition();
	if (pos.x != m_destPosition.x)
	{
		int dif = pos.x - m_destPosition.x;
		this->setPosition(ccp(pos.x - dif / 16, pos.y));
	}

	//�ִϸ��̼� �������� ������
	animation(dt);
	//������ �ִϸ��̼��� ������
	this->setDisplayFrame(m_szStateBuf, m_iFrameNumber);
}

void Object_Hero::animation(ccTime dt)
{
	if (m_iState != m_iprvState)
	{	
		m_fFrameTime = 0.f;
		m_iFrameNumber = 0;

		if (m_iState == CSTATE_IDLE && m_iprvState == CSTATE_RUN)
		{//�������� -> �޸�
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

	//������ Ÿ���� ������Ű�� �������� �Ѿ�� ������ �ѹ��� �ø���.
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
	p->SwapMenuHero();//��Ʈ�� ������...
}

void Object_Hero::setPassivePosition(CGPoint pos)
{
	CCSprite::setPosition(pos);
	m_destPosition = pos;
}