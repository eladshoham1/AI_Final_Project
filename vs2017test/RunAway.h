#pragma once
#include "State.h"

class RunAway : public State
{
public:
	RunAway();
	~RunAway();

	void transform(NPC* pn);
	void onEnter(NPC* pn);
	void onExit(NPC* pn);
};
