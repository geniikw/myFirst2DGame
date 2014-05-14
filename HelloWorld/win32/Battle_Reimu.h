#pragma once

#include"Battle_Unit.h"


class Battle_Reimu : public Battle_Unit
{

public:

	Battle_Reimu(int cTag);
	virtual void doCard(const Action_Card &card);

};