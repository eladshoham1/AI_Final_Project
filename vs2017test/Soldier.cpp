#include "Soldier.h"

Soldier::Soldier()
{
}

Soldier::Soldier(const Point& position, int teamId) : NPC(position, teamId)
{
	this->pCurrentState = new AttackEnemy();
	this->pCurrentState->onEnter(this);
	this->pBullet = new Bullet(position, 5.0);
	this->pGrenade = new Grenade(position);
	this->numOfBullets = MAX_BULLETS;
}

Soldier::~Soldier()
{
}

void Soldier::show()
{
	if (this->pBullet != nullptr)
		this->pBullet->show();
	if (this->pGrenade != nullptr)
		this->pGrenade->show();
}

bool Soldier::shoot(int** maze)
{
	if (this->numOfBullets > 0)
	{
		this->pBullet->fire();
		if (this->pBullet != nullptr && this->pBullet->getIsMoving())
			this->pBullet->move(maze);
		this->numOfBullets--;
		return true;
	}
	return false;
}

bool Soldier::throwGrenade(int** maze)
{
	if (this->numOfBullets >= Grenade::NUM_OF_BULLETS)
	{
		this->pGrenade->explode();
		if (this->pGrenade != nullptr && this->pGrenade->getIsExploded())
			this->pGrenade->exploding(maze);
		this->numOfBullets -= Grenade::NUM_OF_BULLETS;
		return true;
	}
	return false;
}
