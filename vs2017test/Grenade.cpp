#include <math.h>
#include "Grenade.h"

Grenade::Grenade()
{
}

Grenade::Grenade(double x, double y)
{
	double teta = 2 * 3.14 / NUM_BULLETS;
	this->x = x;
	this->y = y;
	for (int i = 0; i < NUM_BULLETS; i++)
		this->bullets[i] = new Bullet(x, y, i*teta);

	this->isExploded = false;
}

Grenade::~Grenade()
{
}

void Grenade::explode()
{
	this->isExploded = true;
	for (int i = 0; i < NUM_BULLETS; i++)
		this->bullets[i]->fire();
}

void Grenade::exploding(int** maze)
{
	if (this->isExploded)
		for (int i = 0; i < NUM_BULLETS; i++)
			this->bullets[i]->move(maze);
}

void Grenade::show()
{
	for (int i = 0; i < NUM_BULLETS; i++)
		this->bullets[i]->show();
}

void Grenade::simulateExplosion(int** maze, double** securityMap, double damage)
{
	int i;

	for (i = 0; i < NUM_BULLETS; i++)
		this->bullets[i]->fire();

	for (i = 0; i < NUM_BULLETS; i++)
		this->bullets[i]->simulateMotion(maze, securityMap, damage);
}

void Grenade::simulateVisibility(int** maze, double** visibilityMap)
{
	int i;

	for (i = 0; i < NUM_BULLETS; i++)
		this->bullets[i]->fire();

	for (i = 0; i < NUM_BULLETS; i++)
		this->bullets[i]->simulateVisibility(maze, visibilityMap);
}
