#pragma once
#include"cocos2d.h"
using namespace cocos2d;

class Portrait : public CCSprite
{
	int			m_iCharacterName;

public:
	Portrait();//init


	void setPortrait(int CharacterName);

	//tick�� ���� tag���޾Ƽ� �ɸ��͸� �����.
	 
};