#include "BringHealthToSoldier.h"
#include "Support.h"

BringHealthToSoldier::BringHealthToSoldier()
{
}

BringHealthToSoldier::~BringHealthToSoldier()
{
}

void BringHealthToSoldier::transform(NPC* pn)
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
			//Soldier* soldier = support->getSoldiers()[0]->hpLack() < support->getSoldiers()[1]->hpLack() ? support->getSoldiers()[0] : support->getSoldiers()[1];
			//support->setTarget(soldier->getPosition(), static_cast<MapCell>(pn->getTeamId()));
		}
	}
}

void BringHealthToSoldier::onEnter(NPC* pn)
{
	Support *support = dynamic_cast<Support*>(pn);
	if (support)
	{
		Soldier* soldier = support->getSoldiers()[0]->hpLack() < support->getSoldiers()[1]->hpLack() ? support->getSoldiers()[0] : support->getSoldiers()[1];
		support->setTarget(soldier->getPosition(), static_cast<MapCell>(pn->getTeamId()));
		support->setIsMoving(true);
	}
}

void BringHealthToSoldier::onExit(NPC* pn)
{
}
