#include "GoToHealthStorage.h"
#include "Support.h"

GoToHealthStorage::GoToHealthStorage()
{
}

GoToHealthStorage::~GoToHealthStorage()
{
}

void GoToHealthStorage::transform(NPC* pn)
{
	cout << "go to health storage" << endl;
	Support *support = dynamic_cast<Support*>(pn);
	if (support)
	{
		if (!support->isInDanger())
		{
			if (!support->isAtTarget())
			{
				support->goToClosestHealthStorage();
			}
			else
			{
				support->takeHealthFromStorage();
				pn->setCurrentState(new BringHealthToSoldier());
			}
		}
		else
		{
			pn->setCurrentState(new GoToSafePlace());
			pn->getCurrentState()->onEnter(pn);
		}
	}
}

void GoToHealthStorage::onEnter(NPC* pn)
{
	Support *support = dynamic_cast<Support*>(pn);
	if (support)
	{
		support->setIsMoving(true);
	}
}

void GoToHealthStorage::onExit(NPC* pn)
{
}
