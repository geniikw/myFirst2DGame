#include"kwController.h"

KwController::KwController()
{
	m_KeySet = NULL;
	m_bWKeyPress = false;
	m_bAKeyPress = false;
	m_bSKeyPress = false;
	m_bDKeyPress = false;

	m_bRKeyPress = false;
	m_bLKeyPress = false;
	m_bUKeyPress = false;
	m_bDKeyPress = false;

	m_bFunc5Press = false;
	m_bFunc6Press = false;
	m_bFunc7Press = false;
	m_bFunc8Press = false;

	m_bTKeyPress = false;
}

void KwController::getAsync()
{
	m_KeySet = NULL;
	if (GetAsyncKeyState('W') && m_bWKeyPress == false)
	{
		m_bWKeyPress = true;
		m_KeySet = 1 | m_KeySet;
	}
	else if (!GetAsyncKeyState('W'))
	{
		m_bWKeyPress = false;
	}

	if (GetAsyncKeyState('A') && m_bAKeyPress == false)
	{
		m_bAKeyPress = true;
		m_KeySet = (1 << KK_A) | m_KeySet;
	}
	else if (!GetAsyncKeyState('A'))
	{
		m_bAKeyPress = false;
	}

	if (GetAsyncKeyState('S') && m_bSKeyPress == false)
	{
		m_bSKeyPress = true;
		m_KeySet = (1 << KK_S) | m_KeySet;
	}
	else if (!GetAsyncKeyState('S'))
	{
		m_bSKeyPress = false;
	}

	if (GetAsyncKeyState('D') && m_bDKeyPress == false)
	{
		m_bDKeyPress = true;
		m_KeySet = (1 << KK_D) | m_KeySet;
	}
	else if (!GetAsyncKeyState('D'))
	{
		m_bDKeyPress = false;
	}

	if (GetAsyncKeyState(VK_RIGHT) && m_bRKeyPress == false)
	{
		m_bRKeyPress = true;
		m_KeySet = (1 << KK_RIGHT) | m_KeySet;
	}
	else if (!GetAsyncKeyState(VK_RIGHT))
	{
		m_bRKeyPress = false;
	}

	if (GetAsyncKeyState(VK_LEFT) && m_bLKeyPress == false)
	{
		m_bLKeyPress = true;
		m_KeySet = (1 << KK_LEFT) | m_KeySet;
	}
	else if (!GetAsyncKeyState(VK_LEFT))
	{
		m_bLKeyPress = false;
	}

	if (GetAsyncKeyState(VK_UP) && m_bUKeyPress == false)
	{
		m_bUKeyPress = true;
		m_KeySet = (1 << KK_UP) | m_KeySet;
	}
	else if (!GetAsyncKeyState(VK_UP))
	{
		m_bUKeyPress = false;
	}

	if (GetAsyncKeyState(VK_DOWN) && m_bDoKeyPress == false)
	{
		m_bDoKeyPress = true;
		m_KeySet = (1 << KK_DOWN) | m_KeySet;
	}
	else if (!GetAsyncKeyState(VK_DOWN))
	{
		m_bDoKeyPress = false;
	}

	if (GetAsyncKeyState(VK_F5) && m_bFunc5Press == false)
	{
		m_bFunc5Press = true;
		m_KeySet = (1 << KK_F5) | m_KeySet;
	}
	else if (!GetAsyncKeyState(VK_F5))
	{
		m_bFunc5Press = false;
	}

	if (GetAsyncKeyState(VK_F6) && m_bFunc6Press == false)
	{
		m_bFunc6Press = true;
		m_KeySet = (1 << KK_F6) | m_KeySet;
	}
	else if (!GetAsyncKeyState(VK_F6))
	{
		m_bFunc6Press = false;
	}

	if (GetAsyncKeyState(VK_F7) && m_bFunc7Press == false)
	{
		m_bFunc7Press = true;
		m_KeySet = (1 << KK_F7) | m_KeySet;
	}
	else if (!GetAsyncKeyState(VK_F7))
	{
		m_bFunc7Press = false;
	}

	if (GetAsyncKeyState(VK_F8) && m_bFunc8Press == false)
	{
		m_bFunc8Press = true;
		m_KeySet = (1 << KK_F8) | m_KeySet;
	}
	else if (!GetAsyncKeyState(VK_F8))
	{
		m_bFunc8Press = false;
	}
	
	if (GetAsyncKeyState('T') && m_bTKeyPress == false)
	{
		m_bTKeyPress = true;
		m_KeySet = (1 << KK_T) | m_KeySet;
	}
	else if (!GetAsyncKeyState('T'))
	{
		m_bTKeyPress = false;
	}

}