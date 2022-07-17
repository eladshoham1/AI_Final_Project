#pragma once
#include "State.h"

class SupplyToSoldier : public State
{
public:
	SupplyToSoldier();
	~SupplyToSoldier();

	void transform(NPC* pn);
	void onEnter(NPC* pn);
	void onExit(NPC* pn);
};
