#pragma once
#include "State.h"

class GoToSoldier : public State
{
public:
	GoToSoldier();
	~GoToSoldier();

	void transform(NPC* pn);
	void onEnter(NPC* pn);
	void onExit(NPC* pn);
};

