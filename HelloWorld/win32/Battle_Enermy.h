#pragma once

#include"Battle_Unit.h"


class Battle_Enermy : public Battle_Unit
{

public:

	Battle_Enermy(int cTag);
	virtual void doCard(const Action_Card &card);

};