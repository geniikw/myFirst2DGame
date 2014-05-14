#pragma once
#include"kwSprite.h"


class Object_MiniCube : public kwSprite
{
	float m_fAngle;
public:
	bool init();
	void tick(ccTime dt);
};