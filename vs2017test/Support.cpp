#include "Support.h"

Support::Support()
{
}

Support::Support(const Point& position) : NPC(position)
{
	this->closestHealthStorage = nullptr;
	this->closestAmmoStorage = nullptr;
	this->health = 0;
	this->ammo = 0;
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

void Support::play(int** maze, double** securityMap)
{
	if (!this->isDead())
	{
		this->goToTarget(maze, securityMap);
	}
}

void Support::show()
{
}

void Support::setClosestHealthStorage(HealthStorage* closestHealthStorage)
{
	if (this->closestHealthStorage != nullptr) {
		delete this->closestHealthStorage;
	}
	this->closestHealthStorage = closestHealthStorage;
}

void Support::setClosestAmmoStorage(AmmoStorage* closestAmmoStorage)
{
	if (this->closestAmmoStorage != nullptr) {
		delete this->closestAmmoStorage;
	}
	this->closestAmmoStorage = closestAmmoStorage;
}

void Support::addSoldierWithLowHP(const Soldier& soldier)
{
	this->waitingForHP.push_back(soldier);
}

void Support::addSoldierWithLowAmmo(const Soldier& soldier)
{
	this->waitingForAmmo.push_back(soldier);
}

void Support::takeHealthFromStorage()
{
	int amount = 0;
	if (this->isAtTarget())
	{
		for (const Soldier& ptr : this->waitingForHP)
		{
			amount += ptr.hpLack();
		}
		this->health += this->closestHealthStorage->supply(amount);
	}
}

void Support::goToClosestHealthStorage()
{
	this->setTarget(this->closestHealthStorage->getPosition(), HEALTH);
}
