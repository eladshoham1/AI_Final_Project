#pragma once
#include "NPC.h"
#include "Bullet.h"
#include "Grenade.h"

class Soldier : public NPC
{
public:
	static constexpr int MAX_BULLETS = 100;
	static constexpr int MAX_GRENADES = 3;
private:
	Bullet* pBullet;
	Grenade* pGrenade;
	int numOfBullets, numOfGrenades;

public:
	Soldier();
	Soldier(const Point& position);
	~Soldier();

	int getNumOfBullets() { return this->numOfBullets; }
	int getNumOfGrenades() { return this->numOfGrenades; }
	void shoot(int** maze);
	void throwGrenade(int** maze);
	int ammoLack() const { return MAX_BULLETS - this->numOfBullets; }
	void play(int** maze, double** securityMap);
	void show();
};
