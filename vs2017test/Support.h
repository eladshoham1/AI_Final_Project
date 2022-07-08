#pragma once
#include "NPC.h"
#include "Soldier.h"
#include "Cell.h"
#include "HealthStorage.h"
#include "AmmoStorage.h"
#include "GoToHealthStorage.h"
#include "GoToAmmoStorage.h"

class Support : public NPC
{
private:
	Soldier** soldiers;
	HealthStorage* closestHealthStorage;
	AmmoStorage* closestAmmoStorage;
	int health;
	int ammo;

public:
	Support();
	Support(const Point& position, Soldier** soldiers, int teamId);
	~Support();

	Soldier** getSoldiers() { return this->soldiers; }
	HealthStorage* getClosestHealthStorage() { return this->closestHealthStorage; }
	AmmoStorage* getClosestAmmoStorage() { return this->closestAmmoStorage; }
	void setClosestHealthStorage(HealthStorage* closestHealthStorage);
	void setClosestAmmoStorage(AmmoStorage* closestAmmoStorage);
	int getHealth() const { return this->health; }
	int getAmmo() const { return this->ammo; }
	void bringHealthToSoldiers();
	void takeHealthFromStorage();
	void goToClosestHealthStorage();
	void show();
};

