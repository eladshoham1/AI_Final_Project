#include "GoToAmmoStorage.h"
#include "Support.h"

GoToAmmoStorage::GoToAmmoStorage()
{
}

GoToAmmoStorage::~GoToAmmoStorage()
{
}

void GoToAmmoStorage::transform(NPC* pn)
{
	Support *support = dynamic_cast<Support*>(pn);
	if (support)
	{
		if (!support->isInDanger())
		{
			if (!support->isAtTarget())
			{
				support->goToClosestAmmoStorage();
			}
			else
			{
				support->takeAmmoFromStorage();
				pn->setCurrentState(new BringAmmoToSoldier());
			}
		}
		else
		{
			pn->setCurrentState(new GoToSafePlace());
			pn->getCurrentState()->onEnter(pn);
		}
	}
}

void GoToAmmoStorage::onEnter(NPC* pn)
{
	Support *support = dynamic_cast<Support*>(pn);
	if (support)
	{
		support->setIsMoving(true);
	}
}

void GoToAmmoStorage::onExit(NPC* pn)
{
}
