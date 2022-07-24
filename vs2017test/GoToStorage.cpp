#include "GoToStorage.h"
#include "Support.h"

GoToStorage::GoToStorage()
{
}

GoToStorage::~GoToStorage()
{
}

void GoToStorage::transform(NPC* pn)
{
	Support *support = dynamic_cast<Support*>(pn);
	if (support)
	{
		if (support->scanAreaForEnemyGrenades())
			pn->setCurrentState(new GoToSafePlace());
		else
		{
			if (support->isAtTarget())
			{
				support->takeSupplyFromStorage();
				pn->setCurrentState(new SupplyToSoldier());
			}
			else
			{
				if (support->getHealth() < 25)
					support->goToClosestHealthStorage();
				else if (support->getAmmo() < 25)
					support->goToClosestAmmoStorage();
			}
		}
	}
}

void GoToStorage::onEnter(NPC* pn)
{
	Support *support = dynamic_cast<Support*>(pn);
	if (support)
	{
		support->setIsMoving(true);
	}
}

void GoToStorage::onExit(NPC* pn)
{
}
