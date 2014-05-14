#pragma once
#define NULL 0

#include<fmod.hpp>
#pragma comment(lib,"fmodex_vc.lib")

#include<fmod_errors.h>

using namespace FMOD;

class Manager_Sound
{
private:
	System	*m_pSystem;
	Channel	*m_pChannel;
	
	Sound     *m_pBlow;
	Sound     *m_pCut;
	Sound     *m_pWall;

	FMOD_RESULT res;
public:
	static Manager_Sound* instance;
	static Manager_Sound* shareClass()
	{
		if (instance == NULL)
		{
			instance = new Manager_Sound;
			instance->initFmod();
		}
		return instance;
	}

public:
	void initFmod();
	void Play_Blow();
	void Play_Cut();
	void Play_Wall();

private:
	void ErrorMsg(FMOD_RESULT res);
	void playSound(Sound *S);
};


