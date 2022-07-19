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
		//cout << "in SupplyToSoldier" << endl;
		if (support->scanAreaForEnemyGrenades())
		{
			//cout << "support->scanAreaForEnemyGrenades()" << endl;
			support->setCurrentState(new GoToSafePlace());
			support->getCurrentState()->onEnter(support);
		}
		else
		{
			support->supplyToSoldier();
			//Soldier* soldier = support->getSoldiers()[0]->hpLack() < support->getSoldiers()[1]->hpLack() ? support->getSoldiers()[0] : support->getSoldiers()[1];
			//support->setTarget(soldier->getPosition(), static_cast<MapCell>(pn->getTeamId()));
		}
	}
}

void SupplyToSoldier::onEnter(NPC* pn)
{
	Support *support = dynamic_cast<Support*>(pn);
	if (support)
	{
		Soldier* soldier = support->getSoldiers()[0]->hpLack() < support->getSoldiers()[1]->hpLack() ? support->getSoldiers()[0] : support->getSoldiers()[1];
		support->setTarget(soldier->getPosition());
		support->setIsMoving(true);
	}
}

void SupplyToSoldier::onExit(NPC* pn)
{
}
