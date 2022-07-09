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
