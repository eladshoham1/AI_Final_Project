#include "Support.h"
#include "Team.h"

Support::Support()
{
}

Support::Support(const Point& position, Soldier** soldiers, int teamId, int** maze, double** securityMap) : NPC(position, teamId, maze, securityMap)
{
	this->soldiers = soldiers;
	this->closestHealthStorage = nullptr;
	this->closestAmmoStorage = nullptr;
	this->health = 0;
	this->ammo = 0;
	this->pCurrentState = new GoToHealthStorage();
	this->pCurrentState->onEnter(this);
}

Support::~Support()
{
	if (this->closestHealthStorage != nullptr) {
		delete this->closestHealthStorage;
	}
	if (this->closestAmmoStorage != nullptr) {
		delete this->closestAmmoStorage;
	}
}

void Support::show()
{
}

void Support::setClosestHealthStorage(HealthStorage* closestHealthStorage)
{
	this->closestHealthStorage = closestHealthStorage;
}

void Support::setClosestAmmoStorage(AmmoStorage* closestAmmoStorage)
{
	this->closestAmmoStorage = closestAmmoStorage;
}

void Support::bringHealthToSoldiers()
{
	for (int i = 0; i < Team::NUM_OF_SOLDIERS; i++)
	{
		if (this->soldiers[i]->hpLack() > 0)
		{
			this->setTarget(this->soldiers[i]->getPosition(), static_cast<MapCell>(this->teamId));
			return;
		}
	}
}

void Support::takeHealthFromStorage()
{
	double amount = 0.0;
	if (this->isAtTarget())
	{
		for (int i = 0; i < Team::NUM_OF_SOLDIERS; i++)
		{
			amount += this->soldiers[i]->hpLack();
		}
		this->health += this->closestHealthStorage->supply((int)ceil(amount));
	}
}

void Support::takeAmmoFromStorage()
{
	double amount = 0.0;
	if (this->isAtTarget())
	{
		for (int i = 0; i < Team::NUM_OF_SOLDIERS; i++)
		{
			amount += this->soldiers[i]->ammoLack();
		}
		this->ammo += this->closestAmmoStorage->supply((int)ceil(amount));
	}
}

void Support::goToClosestHealthStorage()
{
	if (this->closestHealthStorage != nullptr)
	{
		this->setTarget(this->closestHealthStorage->getPosition(), HEALTH);
	}
}

void Support::goToClosestAmmoStorage()
{
	if (this->closestAmmoStorage != nullptr)
	{
		this->setTarget(this->closestAmmoStorage->getPosition(), AMMO);
	}
}

void Support::goToSafePlace()
{
}
