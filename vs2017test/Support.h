#pragma once
#include "NPC.h"
#include "Soldier.h"
#include "Cell.h"
#include "HealthStorage.h"
#include "AmmoStorage.h"

class Support : public NPC
{
private:
	vector<const Soldier&> waitingForHP;
	vector<const Soldier&> waitingForAmmo;
	HealthStorage* closestHealthStorage;
	AmmoStorage* closestAmmoStorage;
	int health;
	int ammo;

public:
	Support();
	Support(const Point& position);
	~Support();

	HealthStorage* getClosestHealthStorage() { return this->closestHealthStorage; }
	AmmoStorage* getClosestAmmoStorage() { return this->closestAmmoStorage; }
	void setClosestHealthStorage(HealthStorage* closestHealthStorage);
	void setClosestAmmoStorage(AmmoStorage* closestAmmoStorage);
	int getHealth() const { return this->health; }
	int getAmmo() const { return this->ammo; }
	void addSoldierWithLowHP(const Soldier& soldier);
	void addSoldierWithLowAmmo(const Soldier& soldier);
	void takeHealthFromStorage();
	void goToClosestHealthStorage();
	void play(int** maze, double** securityMap);
	void show();
};

