#include "Soldier.h"

Soldier::Soldier()
{
}

Soldier::Soldier(const Point& position, int teamId, int** maze, double** securityMap) : NPC(position, teamId, maze, securityMap)
{
	this->pBullet = nullptr;
	this->pGrenade = nullptr;
	this->loadedBullets = MAX_BULLETS;
	this->bulletsInStock = MAX_BULLETS;
	this->setSupporterAlive(true);
	this->setWaitingForSupport(false);
	this->setRandomBehavior();
}

Soldier::~Soldier()
{
}

void Soldier::show()
{
	if (this->pBullet != nullptr)
	{
		//cout << "show pBullet" << endl;
		this->pBullet->show();
	}
	if (this->pGrenade != nullptr)
	{
		//cout << "show pGrenade" << endl;
		this->pGrenade->show();
	}
}

void Soldier::setRandomBehavior()
{
	int choose = rand() % (NUM_OF_STATES + 1);
	switch (choose)
	{
	case 0:
		this->setCurrentState(new GoToSafePlace());
		break;
	case 1:
		this->setCurrentState(new SearchEnemy());
		break;
	case 2:
		this->setCurrentState(new AttackEnemy());
		break;
	case 3:
		this->setCurrentState(new ReloadBullets());
		break;
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
	delete this->pGrenade;
	this->pGrenade = nullptr;
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
	NPC* enemy = this->findEnemy();
	if (enemy == nullptr)
	{
		return false;
	}

	if (this->pGrenade != nullptr)
	{
		delete this->pGrenade;
		this->pGrenade = nullptr;
	}
	this->setVisibilityMapToZero();
	this->pGrenade = new Grenade(this->position.getX(), this->position.getY());
	this->pGrenade->simulateVisibility(this->maze, this->visibilityMap);
	delete this->pGrenade;
	this->pGrenade = nullptr;
	//cout << this->distanceFromEnemy() << ", " << this->visibilityMap[enemy->getPosition().getY()][enemy->getPosition().getX()] << endl;
	return this->distanceFromEnemy() < 10.0
		&& this->visibilityMap[enemy->getPosition().getY()][enemy->getPosition().getX()] == 1;
}

void Soldier::attack()
{
	if (this->isEnemyVisible())
	{
		NPC* enemy = this->findEnemy();
		if (enemy)
		{
			if (this->loadedBullets >= Grenade::NUM_OF_BULLETS && this->distanceFromEnemy() < 4.0)
			{
				this->throwGrenade(enemy);
			}
			else
			{
				this->shoot(enemy);
			}
		}
	}
}

bool Soldier::shoot(NPC* enemy)
{
	double directionAngle;
	//cout << "shoot this->loadedBullets: " << this->loadedBullets << endl;
	if (enemy != nullptr && this->loadedBullets > 0)
	{
		//cout << "shoot" << endl;
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
	//cout << "throwGrenade this->loadedBullets: " << this->loadedBullets << endl;
	if (this->loadedBullets >= Grenade::NUM_OF_BULLETS)
	{
		if (this->pGrenade != nullptr)
		{
			delete this->pGrenade;
			this->pGrenade = nullptr;
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
