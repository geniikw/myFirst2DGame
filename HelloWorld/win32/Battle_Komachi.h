#pragma once

#include"Battle_Unit.h"


class Battle_Komachi : public Battle_Unit
{

public:

	Battle_Komachi(int cTag);
	virtual void doCard(const Action_Card &card);

};