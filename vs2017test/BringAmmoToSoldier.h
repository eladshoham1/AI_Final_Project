#pragma once
#include "State.h"

class BringAmmoToSoldier : public State
{
public:
	BringAmmoToSoldier();
	~BringAmmoToSoldier();

	void transform(NPC* pn);
	void onEnter(NPC* pn);
	void onExit(NPC* pn);
};
