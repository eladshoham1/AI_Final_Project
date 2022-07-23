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
	this->loadedBullets = MAX_BULLETS;
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
		if (this->loadedBullets + this->bulletsInStock > MAX_BULLETS)
		{
			this->bulletsInStock -= (MAX_BULLETS - this->loadedBullets);
			this->loadedBullets = MAX_BULLETS;
		}
		else
		{
			this->loadedBullets += this->bulletsInStock;
			this->bulletsInStock = 0;
		}
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
	NPC* enemy = this->findEnemy();
	if (enemy == nullptr)
	{
		return false;
	}
	Point* enemyPosition = &enemy->getPosition();

	row = this->position.getX();
	col = this->position.getY();
	targetRow = enemyPosition->getX();
	targetCol = enemyPosition->getY();
	directionAngle = atan2((double)targetRow - (double)row, (double)targetCol - (double)col);

	if (this->pBullet != nullptr)
	{
		delete this->pBullet;
	}
	this->setVisibilityMapToZero(); // rebuild VisibilityMap with grenade instead bullet
	this->pBullet = new Bullet(this->position, this->position.getY(), this->position.getX(), directionAngle);
	//this->pBullet = new Bullet(this->position, enemyPosition->getX(), enemyPosition->getY(), directionAngle);
	this->pBullet->fire();
	this->pBullet->simulateVisibility(this->maze, this->visibilityMap);
	/*if (this->distanceFromEnemy() < 2.0)
	{
		for (int i = 0; i < MSZ; i++)
		{
			for (int j = 0; j < MSZ; j++)
			{
				cout << this->visibilityMap[i][j] << " ";
			}
			cout << endl;
		}
	}*/
	//cout << this->distanceFromEnemy() << ", " << this->visibilityMap[enemy->getPosition().getY()][enemy->getPosition().getX()] << endl;
	return this->distanceFromEnemy() < 12.0
		&& this->visibilityMap[enemy->getPosition().getY()][enemy->getPosition().getX()] == 1;
}

void Soldier::attack()
{
	if (this->isEnemyVisible())
	{
		NPC* enemy = this->findEnemy();
		if (enemy)
		{
			if (this->distanceFromEnemy() < 5.0)
			{
				cout << "throwGrenade" << endl;
				this->throwGrenade(enemy);
			}
			else
			{
				cout << "shoot" << endl;
				this->shoot(enemy);
			}
		}
	}
}

bool Soldier::shoot(NPC* enemy)
{
	double directionAngle;
	if (enemy != nullptr && this->loadedBullets > 0)
	{
		directionAngle = atan2(this->position.getX() - enemy->getPosition().getX(), this->position.getY() - enemy->getPosition().getY());
		if (this->pBullet != nullptr && !this->pBullet->getIsMoving())
		{
			delete this->pBullet;
		}
		
		this->pBullet = new Bullet(this->position, enemy->getPosition().getX(), enemy->getPosition().getY(), directionAngle);
		this->pBullet->fire();
		if (this->pBullet != nullptr && this->pBullet->getIsMoving())
		{
			Point* point = this->pBullet->move(this->maze);
			if (point)
			{
				if (enemy->getPosition().euclideanDistance(point->getY(), point->getX()) < 2.0)
				{
					Point shootingPosition = this->pBullet->getShootingPosition();
					double distance = point->euclideanDistance(shootingPosition);
					enemy->hit(rand() % 10 + distance);
				}
			}
		}
		this->loadedBullets--;
		return true;
	}
	return false;
}

bool Soldier::throwGrenade(NPC* enemy)
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
				if (enemy->getPosition().euclideanDistance(point->getY(), point->getX()) < 2.0)
				{
					enemy->hit(rand() % 15);
				}
			}

		}
		this->loadedBullets -= Grenade::NUM_OF_BULLETS;
		return true;
	}
	return false;
}
