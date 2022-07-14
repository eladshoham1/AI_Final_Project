#include "GoToSafePlace.h"
#include "Soldier.h"

GoToSafePlace::GoToSafePlace()
{
}

GoToSafePlace::~GoToSafePlace()
{
}

void GoToSafePlace::transform(NPC* pn)
{
	pn->goToSafePlace();
}

void GoToSafePlace::onEnter(NPC* pn)
{
	Soldier *soldier = dynamic_cast<Soldier*>(pn);
	if (soldier)
	{
		soldier->setWaitingForSupport(soldier->isInDanger() && !soldier->hasBulletsInStock());
		soldier->setIsMoving(true);
	}
}

void GoToSafePlace::onExit(NPC* pn)
{
}
