#include "SupplyToSoldier.h"
#include "Support.h"

SupplyToSoldier::SupplyToSoldier()
{
}

SupplyToSoldier::~SupplyToSoldier()
{
}

void SupplyToSoldier::transform(NPC* pn)
{
	Support *support = dynamic_cast<Support*>(pn);
	if (support)
	{
		if (support->scanAreaForEnemyGrenades() && support->hpLastThanHalf())
			support->setCurrentState(new GoToSafePlace());
		else
			support->supplyToSoldier();
	}
}

void SupplyToSoldier::onEnter(NPC* pn)
{
	Support *support = dynamic_cast<Support*>(pn);
	if (support)
	{
		support->setIsMoving(true);
	}
}

void SupplyToSoldier::onExit(NPC* pn)
{
}
