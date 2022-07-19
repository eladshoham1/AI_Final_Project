#pragma once
#include "Ammo.h"
#include "Bullet.h"

class Grenade : public Ammo
{
public:
	static constexpr int NUM_OF_BULLETS = 30;

private:
	Bullet* bullets[NUM_OF_BULLETS];
	bool isExploded;

public:
	Grenade();
	Grenade(double x, double y);
	~Grenade();

	bool getIsExploded() { return this->isExploded; }
	void explode();
	Point* exploding(int** maze);
	void show();
	void simulateExplosion(int** maze, double** securityMap, double damage);
	void simulateVisibility(int** maze, double** visibilityMap);
};
