#include "GameManager.h"

GameManager::GameManager()
{
	this->map = new Map();
	this->gameState = state::STOP_GAME;
}

GameManager::GameManager(const char* fileName)
{
	this->map = new Map(fileName);
	this->gameState = state::STOP_GAME;
}

GameManager::~GameManager()
{
	delete this->map;
}

void GameManager::idle()
{
	switch (this->gameState)
	{
	case state::START_GAME:
		play();
		break;
	case state::STOP_GAME:
		stop();
		break;
	default:
		cout << "Error, while tring to change the state of the game" << endl;
	}
}

void GameManager::play()
{
	this->map->play();
}

void GameManager::stop()
{
	//cout << "stop" << endl;
}

void GameManager::show()
{
	this->map->showMaze();
}
