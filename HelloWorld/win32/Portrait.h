#pragma once
#include"cocos2d.h"
using namespace cocos2d;

class Portrait : public CCSprite
{
	int			m_iCharacterName;

public:
	Portrait();//init


	void setPortrait(int CharacterName);

	//tick이 없이 tag를받아서 케릭터를 출력함.
	 
};