#include"UI_Menu.h"
#include"SceneTown.h"

bool UI_Menu::init()
{
	m_fSeletedAngle = 0.f;
	m_iLeftKeyPress = 0;
	m_iRightKeyPress = 0;

	m_fDestAngle = 0.f;
	for (int n = 0; n < 4; n++)
	{
		m_pChar[n] = new UI_CharState;
		m_pChar[n]->init();
		m_pChar[n]->setAnchorPoint(ccp(0.5, 0.5));
		m_pChar[n]->setNumber(n);
		this->addChild(m_pChar[n]);
		m_pChar[n]->setOpacity(150);
	}

	m_pMenu = new UI_TownMenu;
	m_pMenu->init();
	this->addChild(m_pMenu);

	m_pMenu->setAnchorPoint(ccp(0, 0));
	schedule(schedule_selector(UI_Menu::tick));

	return true;
}

void UI_Menu::tick(ccTime dt)
{
	SceneTown *p = (SceneTown*)this->getParent();//컨트롤이 메뉴에 있을때만
	if (this == p->getConstroll())
	{
		if (GetAsyncKeyState(VK_RIGHT) && m_iRightKeyPress == 0)
		{
			m_iRightKeyPress = 1;
			m_fDestAngle += 90.f;
		}
		else if(!GetAsyncKeyState(VK_RIGHT))
		{
			m_iRightKeyPress = 0;
		}

		if (GetAsyncKeyState(VK_LEFT) && m_iLeftKeyPress == 0)
		{
			m_iLeftKeyPress = 1;
			m_fDestAngle -= 90.f;
		}
		else if (!GetAsyncKeyState(VK_LEFT))
		{
			m_iLeftKeyPress = 0;
		}


		if (GetAsyncKeyState(VK_RETURN))
		{
			SceneTown *p = (SceneTown*) this->getParent();
			p->SwapMenuHero();
		}
	}


	if (m_fDestAngle != m_fSeletedAngle)
	{
		float angle = m_fDestAngle - m_fSeletedAngle;
		angle = angle / 10;
		m_fSeletedAngle += angle;

	}

	//m_fSeletedAngle += dt * 50.f;
	//300x130 char window
	//200x300 menu
	static int x[4], y[4]; //클래스 안에서 static은 유일클래스일때만 쓰자
	static int cenX, cenY;
	cenX = 400;
	cenY = 150;
	
	static float f;
	f += dt;
	for (int n = 0; n < 4; n++)
	{
		x[n] = cenX + 130 * cosf((m_pChar[n]->getMenuAngle() + m_fSeletedAngle) * 3.1415 / 180);
		y[n] = cenY + 50 * sinf((m_pChar[n]->getMenuAngle() + m_fSeletedAngle) * 3.1415 / 180);
		this->reorderChild(m_pChar[n], -(int)y[n]);
		m_pChar[n]->setScale( 100.f/ y[n] );
		m_pChar[n]->setOpacity(100.f / y[n]*255);
	}

	for (int n = 0; n < 4; n++)
	{
		m_pChar[n]->setPosition(ccp(x[n], y[n]));
	}
}

void UI_Menu::semiInit()
{
	m_fSeletedAngle = 0.f;

}