#pragma once
#include "State.h"

class GoToSafePlace : public State
{
public:
	GoToSafePlace();
	~GoToSafePlace();

	void transform(NPC* pn);
	void onEnter(NPC* pn);
	void onExit(NPC* pn);
};
