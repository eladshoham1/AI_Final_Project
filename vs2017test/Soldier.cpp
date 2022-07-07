#include "Soldier.h"

Soldier::Soldier()
{
}

Soldier::Soldier(const Point& position) : NPC(position)
{
	this->pCurrentState = new AttackEnemy();
	this->pCurrentState->onEnter(this);
	this->pBullet = new Bullet(position, 5.0);
	this->pGrenade = new Grenade(position);
	this->numOfBullets = MAX_BULLETS;
	this->numOfGrenades = MAX_GRENADES;
}

Soldier::~Soldier()
{
}

void Soldier::play(int** maze, double** securityMap)
{
	if (!this->isDead())
	{
		if (dynamic_cast<AttackEnemy*>(this->pCurrentState))
		{
			//shoot(maze);
			//throwGrenade(maze);
		}
	}
}

void Soldier::show()
{
	if (this->pBullet != nullptr)
		this->pBullet->show();
	if (this->pGrenade != nullptr)
		this->pGrenade->show();
}

void Soldier::shoot(int** maze)
{
	if (this->numOfBullets > 0)
	{
		cout << this->numOfBullets << endl;
		this->pBullet->fire();
		if (this->pBullet != nullptr && this->pBullet->getIsMoving())
			this->pBullet->move(maze);
		this->numOfBullets--;
	}
}

void Soldier::throwGrenade(int** maze)
{
	if (this->numOfGrenades > 0)
	{
		this->pGrenade->explode();
		if (this->pGrenade != nullptr && this->pGrenade->getIsExploded())
			this->pGrenade->exploding(maze);
		this->numOfGrenades--;
	}
}
