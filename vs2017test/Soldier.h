#pragma once
#include "NPC.h"
#include "Bullet.h"
#include "Grenade.h"

class Soldier : public NPC
{
public:
	static constexpr int MAX_BULLETS = 100;

private:
	Bullet* pBullet;
	Grenade* pGrenade;
	int numOfBullets;

public:
	Soldier();
	Soldier(const Point& position, int teamId);
	~Soldier();

	int getNumOfBullets() { return this->numOfBullets; }
	int ammoLack() const { return MAX_BULLETS - this->numOfBullets; }
	bool needAmmo() { return this->numOfBullets < MAX_BULLETS / 2.0; }
	bool shoot(int** maze);
	bool throwGrenade(int** maze);
	void show();
};
