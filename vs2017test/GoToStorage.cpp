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
		if (!support->scanAreaForEnemyGrenades())
		{
			if (support->isAtTarget())
			{
				support->takeHealthFromStorage();
				pn->setCurrentState(new SupplyToSoldier());
			}
			else
			{
				if (support->getHealth() < 25)
				{
					support->goToClosestHealthStorage();
				}
				else if (support->getAmmo() < 40)
				{
					support->goToClosestAmmoStorage();
				}
				else
				{
					support->takeHealthFromStorage();
					pn->setCurrentState(new SupplyToSoldier());
				}
			}
		}
		else
		{
			pn->setCurrentState(new GoToSafePlace());
			//pn->getCurrentState()->onEnter(pn);
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
