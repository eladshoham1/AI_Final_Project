#include "Soldier.h"

Soldier::Soldier()
{
}

Soldier::Soldier(const Point& position, int teamId, int** maze, double** securityMap) : NPC(position, teamId, maze, securityMap)
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
		this->pBullet->show();
	if (this->pGrenade != nullptr)
		this->pGrenade->show();
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
	return this->closestEnemy != nullptr && this->distanceFromEnemy() < 10.0;
}

void Soldier::attack()
{
	cout << "Soldier attack" << endl;
	double distance = this->distanceFromEnemy();
	if (this->isEnemyVisible())
	{
		if (distance < 3.0)
		{
			cout << "Soldier this->throwGrenade();" << endl;
			this->throwGrenade();
		}
		else
		{
			cout << "Soldier this->shoot();" << endl;
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
		this->pBullet = new Bullet(this->position.getX(), this->position.getY(), directionAngle);
		this->pBullet->fire();
		cout << "Soldier this->pBullet->fire();" << endl;
		if (this->pBullet != nullptr && this->pBullet->getIsMoving())
		{
			this->pBullet->move(this->maze);
			cout << "Soldier this->pBullet->move(this->maze);" << endl;
		}
		this->loadedBullets--;
		cout << "Soldier loadedBullets: " << this->loadedBullets << endl;
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
	if (!this->hasLoadedBullets()) {
		if (this->hasBulletsInStock())
		{
			this->setCurrentState(new ReloadBullets());
			this->getCurrentState()->onEnter(this);
		}
		else
		{
			this->setWaitingForSupport(true);
		}
	}
	else
	{
		if (!this->isInDanger())
		{
			if (this->isEnemyVisible())
			{
				this->setCurrentState(new AttackEnemy());
				this->getCurrentState()->onEnter(this);
			}
			else
			{
				this->setCurrentState(new SearchEnemy());
				this->getCurrentState()->onEnter(this);
			}
		}
		else
		{
			this->setWaitingForSupport(true);
		}
	}
}
