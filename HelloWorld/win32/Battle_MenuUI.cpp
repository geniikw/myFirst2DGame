
#include"Battle_MenuUI.h"
#include"Manager_Global.h"
#include"Manager_Resource.h"

#include"Battle_CharUI.h"
#include"Battle_Unit.h"
#include"Action_Card.h"

Battle_MenuUI::Battle_MenuUI(vector<Battle_Unit*>* pList)
{
	m_iMenu = 0;
	m_iCurrentSelected = 0;
	m_fPortOpacity = 0.f;
	for (int n = 0; n < MAX_HERO_COUNT; n++)
	{
		m_pCharUI[n] = new Battle_CharUI((*pList)[n], &G_CHARMENU_VISIBLE_POSITION, G_CHARMENU_HIDE_POSITION[n]);
		m_pCharUI[n]->setAnchorPoint(ccp(0.5f, 0.5f));
		m_pCharUI[n]->setPosition(ccp(-200, -200));
		this->addChild(m_pCharUI[n]);
	}
	schedule(schedule_selector(Battle_MenuUI::tick));
	Manager_Global::getInstance()->g_pBattleMenuUI = this;

	m_pPortrait = new Portrait();
	m_pPortrait->setAnchorPoint(ccp(1, 0));
	m_pPortrait->setPosition(ccp(640, 0));
	m_pPortrait->setOpacity(200);
	this->addChild(m_pPortrait);

	//Action_Card *pCard = new Action_Card(1);
	//pCard->setPosition(ccp(100, 100));
	//this->addChild(pCard);
}

void Battle_MenuUI::tick(ccTime dt)
{
	doCtrl(dt);
	doMenu(dt);
}

void Battle_MenuUI::doCtrl(ccTime dt)
{
	if (Manager_Global::getInstance()->g_pControllPermission != this)
		return;

	m_Controller.getAsync();
	KeySet set = m_Controller.getKeySet();

	if (set & (1 << KK_T)) //t키가 눌렸으면...
	{
		m_iMenu = 0;
		m_iCurrentSelected = 0;
		m_fPortOpacity = 0.f;
		Manager_Global::getInstance()->g_pControllPermission = Manager_Global::getInstance()->g_pBattleSprite;
	}

	if (set & (1 << KK_RIGHT))
	{
		m_iCurrentSelected++;
		if (m_iCurrentSelected > 3)
			m_iCurrentSelected = 0;

		m_fPortOpacity = 0.f;
	}

	if (set & (1 << KK_LEFT))
	{
		m_iCurrentSelected--;
		if (m_iCurrentSelected < 0)
			m_iCurrentSelected = 3;

		m_fPortOpacity = 0.f;
	}

	if (set & (1 << KK_DOWN))
	{
		m_iMenu = 1;
	}
	if (set & (1 << KK_UP))
	{
		m_iMenu = 0;
	}
}

void Battle_MenuUI::doMenu(ccTime dt)
{
	if ( m_fPortOpacity < 200.f&& m_iMenu == 1)
	{
		m_fPortOpacity += dt * 50.f;
	}
	m_pPortrait->setOpacity(m_fPortOpacity);

	Manager_Global *pG = Manager_Global::getInstance();

	if (pG->g_pControllPermission == this)
	{
		if (m_iMenu == 1)//active skill menu
		{
			for (int n = 0; n < MAX_HERO_COUNT; n++)
			{
				if (n == m_iCurrentSelected)
				{
					m_pCharUI[n]->setMenuPosition(MP_ACTIVE);
					m_pPortrait->setPortrait(m_pCharUI[n]->getUnitP()->getCharacterName());
				}
				else
				m_pCharUI[n]->setMenuPosition(MP_HIDE);
			}
		}
		else
		{
			m_pPortrait->setPortrait(CN_NOTHING);
			Manager_Global::getInstance()->g_fBattleDT = 0.f;
			for (int n = 0; n < MAX_HERO_COUNT; n++)
			{
				int a = (n + m_iCurrentSelected) % 4 + 1;
				m_pCharUI[n]->setMenuPosition((4 + n - m_iCurrentSelected) % 4 + 1);
			}
		}
	}
	else
	{
		Manager_Global::getInstance()->g_fBattleDT = 1.f;
		for (int n = 0; n < MAX_HERO_COUNT; n++)
		{
			m_pCharUI[n]->setMenuPosition(MP_HIDE);
		}
	}	
}


void Battle_MenuUI::doCtrlMenu1(ccTime dt)
{

}
void Battle_MenuUI::doCtrlMenu2(ccTime dt)
{

}
void Battle_MenuUI::doCtrlMenu3(ccTime dt)
{

}