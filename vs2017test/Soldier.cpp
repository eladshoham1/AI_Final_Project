#include "Soldier.h"

Soldier::Soldier()
{
}

Soldier::Soldier(const Point& position, int teamId, int** maze, double** securityMap, NPC* leader) : NPC(position, teamId, maze, securityMap, leader)
{
	this->pCurrentState = new SearchEnemy();
	this->pCurrentState->onEnter(this);
	this->pBullet = nullptr;
	this->pGrenade = nullptr;
	this->loadedBullets = 0;
	this->bulletsInStock = MAX_BULLETS;
	this->waitingForSupport = false;
}

Soldier::~Soldier()
{
}

void Soldier::show()
{
	if (this->pBullet != nullptr)
	{
		this->pBullet->show();
	}
	if (this->pGrenade != nullptr)
	{
		this->pGrenade->show();
	}
}

void Soldier::supplyBullets(int bullets)
{
	if (this->bulletsInStock + bullets > MAX_BULLETS)
	{
		this->bulletsInStock = MAX_BULLETS;
	}
	else
	{
		this->bulletsInStock += bullets;
	}
}

void Soldier::setVisibilityMap()
{
	for (int i = 0; i < MSZ; i++)
	{
		for (int j = 0; j < MSZ; j++)
		{
			this->visibilityMap[i][j] = 0;
		}
	}
	if (this->pGrenade != nullptr)
	{
		delete this->pGrenade;
	}
	this->pGrenade = new Grenade(position.getX(), position.getY());
	this->pGrenade->simulateVisibility(this->maze, this->visibilityMap);
}

void Soldier::loadBullets()
{
	if (this->bulletsInStock > 0)
	{
		this->loadedBullets += this->bulletsInStock;
		this->bulletsInStock = 0;
	}
}

void Soldier::addBulletsToStock(int numOfBullets)
{
	if (numOfBullets > 0)
	{
		if (this->bulletsInStock + numOfBullets <= MAX_BULLETS)
		{
			this->bulletsInStock += numOfBullets;
		}
		else
		{
			this->bulletsInStock = MAX_BULLETS;
		}
	}
}

bool Soldier::isEnemyVisible()
{
	return this->closestEnemy != nullptr && this->distanceFromEnemy() < 1.0;
}

void Soldier::attack()
{
	double distance = this->distanceFromEnemy();
	if (this->isEnemyVisible())
	{
		if (distance < 3.0)
		{
			this->throwGrenade();
		}
		else
		{
			this->shoot();
		}
	}
}

bool Soldier::shoot()
{
	double directionAngle;
	if (this->closestEnemy != nullptr && this->loadedBullets > 0)
	{
		directionAngle = atan2(this->position.getX() - this->closestEnemy->getPosition().getX(), this->position.getY() - this->closestEnemy->getPosition().getY());
		if (this->pBullet != nullptr)
		{
			delete this->pBullet;
		}
		this->pBullet = new Bullet(this->position.getX(), this->position.getY(), this->position, directionAngle);
		this->pBullet->fire();
		if (this->pBullet != nullptr && this->pBullet->getIsMoving())
		{
			this->pBullet->move(this->maze);
		}
		this->loadedBullets--;
		return true;
	}
	return false;
}

bool Soldier::throwGrenade()
{
	if (this->loadedBullets >= Grenade::NUM_OF_BULLETS)
	{
		if (this->pGrenade != nullptr)
		{
			delete this->pGrenade;
		}
		this->pGrenade = new Grenade(this->position.getX(), this->position.getY());
		this->pGrenade->explode();
		if (this->pGrenade != nullptr && this->pGrenade->getIsExploded())
			this->pGrenade->exploding(this->maze);
		this->loadedBullets -= Grenade::NUM_OF_BULLETS;
		return true;
	}
	return false;
}

void Soldier::goToSafePlace()
{
	cout << "in goToSafePlace" << endl;
	if (this->moveToSafestPosition())
	{
		if (!this->hasLoadedBullets())
		{
			cout << "GoToSafePlace !soldier->hasLoadedBullets()" << endl;
			this->setCurrentState(new ReloadBullets());
			this->pCurrentState->onEnter(this);
		}
		else if (!this->hasBulletsInStock())
		{
			cout << "GoToSafePlace !soldier->hasBulletsInStock()" << endl;
			// check if support is alive
			this->setWaitingForSupport(true);
		}
		else
		{
			if (this->isEnemyVisible())
			{
				cout << "GoToSafePlace !soldier->isEnemyVisible()" << endl;
				this->setCurrentState(new AttackEnemy());
				this->pCurrentState->onEnter(this);
			}
			else
			{
				cout << "GoToSafePlace else !soldier->isEnemyVisible()" << endl;
				this->setCurrentState(new SearchEnemy());
				this->pCurrentState->onEnter(this);
			}
		}
	}
}
