#pragma once
#include "State.h"

class BringHealthToSoldier : public State
{
public:
	BringHealthToSoldier();
	~BringHealthToSoldier();

	void transform(NPC* pn);
	void onEnter(NPC* pn);
	void onExit(NPC* pn);
};
