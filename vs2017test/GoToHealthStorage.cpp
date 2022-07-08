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
		if (!support->isAtTarget())
		{
			support->goToClosestHealthStorage();
		}
		else
		{
			support->takeHealthFromStorage();
			pn->setCurrentState(new GoToSoldier());
		}
	}
}

void GoToHealthStorage::onEnter(NPC* pn)
{
	/*Support *support = dynamic_cast<Support*>(pn);
	if (support)
	{
		support->setSearchForClose
	}*/
}

void GoToHealthStorage::onExit(NPC* pn)
{
}
