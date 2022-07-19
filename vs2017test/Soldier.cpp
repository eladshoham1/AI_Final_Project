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
	this->setSupporterAlive(true);
	this->setWaitingForSupport(false);
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
	int row, col, targetRow, targetCol;
	double directionAngle;
	Point* enemyPosition = &this->closestEnemy->getPosition();

	row = this->position.getX();
	col = this->position.getY();
	targetRow = enemyPosition->getX();
	targetCol = enemyPosition->getY();
	directionAngle = atan2((double)targetRow - (double)row, (double)targetCol - (double)col);

	if (this->pBullet != nullptr)
	{
		delete this->pBullet;
	}
	this->setVisibilityMapToZero();
	this->pBullet = new Bullet(this->position, enemyPosition->getX(), enemyPosition->getY(), directionAngle);
	this->pBullet->fire();
	this->pBullet->simulateVisibility(this->maze, this->visibilityMap);

	return this->closestEnemy != nullptr && this->distanceFromEnemy() < 12.0
		&& this->visibilityMap[this->closestEnemy->getPosition().getY()][this->closestEnemy->getPosition().getX()] == 1;
}

void Soldier::attack()
{
	if (this->isEnemyVisible())
	{
		if (this->distanceFromEnemy() < 5.0)
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

		this->pBullet = new Bullet(this->position, this->closestEnemy->getPosition().getX(), this->closestEnemy->getPosition().getY(), directionAngle);
		this->pBullet->fire();
		if (this->pBullet != nullptr && this->pBullet->getIsMoving())
		{
			Point* point = this->pBullet->move(this->maze);
			if (point)
			{
				cout << "closest enemy row: " << this->closestEnemy->getPosition().getX() << " col: " << this->closestEnemy->getPosition().getY() << endl;
				cout << "move row: " << point->getY() << " col: " << point->getX() << endl;
				if (this->closestEnemy->getPosition().euclideanDistance(point->getY(), point->getX()) < 2.0)
				{
					cout << "11hit11" << endl;
					Point shootingPosition = this->pBullet->getShootingPosition();
					double distance = point->euclideanDistance(shootingPosition);
					this->closestEnemy->hit(rand() % 10 + distance);
				}
			}
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
		this->pGrenade = new Grenade(this->position.getY(), this->position.getX());
		this->pGrenade->explode();
		if (this->pGrenade != nullptr && this->pGrenade->getIsExploded())
		{
			Point* point = this->pGrenade->exploding(this->maze);
			if (point)
			{
				if (this->closestEnemy->getPosition().euclideanDistance(point->getY(), point->getX()) < 2.0)
				{
					cout << "22hit22" << endl;
					this->closestEnemy->hit(rand() % 15);
				}
			}

		}
		this->loadedBullets -= Grenade::NUM_OF_BULLETS;
		return true;
	}
	return false;
}

void Soldier::goToSafePlace()
{
	if (this->moveToSafestPosition())
	{
		if (!this->hasLoadedBullets())
		{
			this->setCurrentState(new ReloadBullets());
			this->pCurrentState->onEnter(this);
		}
		else if (!this->hasBulletsInStock())
		{
			// check if support is alive
			this->setWaitingForSupport(true);
		}
		else
		{
			if (this->isEnemyVisible())
			{
				this->setCurrentState(new AttackEnemy());
				this->pCurrentState->onEnter(this);
			}
			else
			{
				this->setCurrentState(new SearchEnemy());
				this->pCurrentState->onEnter(this);
			}
		}
	}
}
