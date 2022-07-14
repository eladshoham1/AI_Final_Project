#include "Dead.h"
#include "NPC.h"

Dead::Dead()
{
}

Dead::~Dead()
{
}

void Dead::transform(NPC* pn)
{
}

void Dead::onEnter(NPC* pn)
{
	pn->setAsDead();
}

void Dead::onExit(NPC* pn)
{
}
