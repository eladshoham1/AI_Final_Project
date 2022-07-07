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
	Support *support = dynamic_cast<Support*>(pn);
	if (support)
	{
		if (support->isAtTarget())
		{
			support->takeHealthFromStorage();
			support->setCurrentState(new GoToSoldier());
		}
	}
}

void GoToHealthStorage::onEnter(NPC* pn)
{
	Support *support = dynamic_cast<Support*>(pn);
	if (support)
	{
		support->goToClosestHealthStorage();
	}
}

void GoToHealthStorage::onExit(NPC* pn)
{
}
