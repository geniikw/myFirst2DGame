#include"Manager_Sound.h"

#include<Windows.h>
void Manager_Sound::initFmod()
{
	res = FMOD::System_Create(&m_pSystem);
	res = m_pSystem->init(100, FMOD_INIT_NORMAL, NULL);
	res = m_pSystem->createSound("Sounds/blow.ogg", FMOD_DEFAULT, NULL, &m_pBlow);
	res = m_pSystem->createSound("Sounds/cut.ogg", FMOD_DEFAULT, NULL, &m_pCut);
	res = m_pSystem->createSound("Sounds/wall.ogg", FMOD_DEFAULT, NULL, &m_pWall);
}

void Manager_Sound::playSound(Sound *S)
{
	res = m_pSystem->playSound(FMOD_CHANNEL_FREE, S, false, &m_pChannel);
	m_pSystem->update();
}

void Manager_Sound::ErrorMsg(FMOD_RESULT res)
{
	wchar_t buf[64];
	mbstowcs(buf, FMOD_ErrorString(res), 64);
	if (res != FMOD_OK)
		MessageBox(NULL, buf, L"error", MB_OK);
}

void Manager_Sound::Play_Blow()
{
	playSound(m_pBlow);
}

void Manager_Sound::Play_Cut()
{
	playSound(m_pCut);
}

void Manager_Sound::Play_Wall()
{
	playSound(m_pWall);
}