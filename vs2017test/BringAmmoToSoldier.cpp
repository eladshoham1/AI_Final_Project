#include "BringAmmoToSoldier.h"
#include "Support.h"

BringAmmoToSoldier::BringAmmoToSoldier()
{
}

BringAmmoToSoldier::~BringAmmoToSoldier()
{
}

void BringAmmoToSoldier::transform(NPC* pn)
{
	Support *support = dynamic_cast<Support*>(pn);
	if (support)
	{
		if (support->isInDanger())
		{
			//support->setCurrentState(new GoToSafePlace());
		}
		else
		{
			Soldier* soldier = support->getSoldiers()[0]->hpLack() < support->getSoldiers()[1]->hpLack() ? support->getSoldiers()[0] : support->getSoldiers()[1];
			support->setTarget(soldier->getPosition(), static_cast<MapCell>(pn->getTeamId()));
		}
	}
}

void BringAmmoToSoldier::onEnter(NPC* pn)
{
	Support *support = dynamic_cast<Support*>(pn);
	if (support)
	{
		support->setIsMoving(true);
	}
}

void BringAmmoToSoldier::onExit(NPC* pn)
{
}
