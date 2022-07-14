#pragma once
#include "State.h"

class Dead : public State
{
public:
	Dead();
	~Dead();

	void transform(NPC* pn);
	void onEnter(NPC* pn);
	void onExit(NPC* pn);
};
