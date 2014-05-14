#pragma once

#include"Battle_Unit.h"


class Battle_Meiling : public Battle_Unit
{

public:

	Battle_Meiling(int cTag);
	virtual void doCard(const Action_Card &card);

};