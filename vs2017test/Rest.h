#pragma once
#include "State.h"

class Rest : public State
{
public:
	Rest();
	~Rest();

	void transform(NPC* pn);
	void onEnter(NPC* pn);
	void onExit(NPC* pn);
};

