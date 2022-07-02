#pragma once

class NPC;

class State
{
public:
	virtual void transform(NPC* pn) = 0; // to the next state
	virtual void onEnter(NPC* pn) = 0; // to the current state
	virtual void onExit(NPC* pn) = 0;  // from the current state
};
