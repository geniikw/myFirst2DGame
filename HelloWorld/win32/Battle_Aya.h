#pragma once

#include"Battle_Unit.h"


class Battle_Aya : public Battle_Unit
{

public:

	Battle_Aya(int cTag);
	virtual void doCard(const Action_Card &card);

};