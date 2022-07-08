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
		this->play();
		break;
	case state::STOP_GAME:
		break;
	case state::GAME_OVER:
		this->gameOver();
		break;
	default:
		cout << "Error, while tring to change the state of the game" << endl;
	}
}

void GameManager::play()
{
	if (!this->map->play())
	{
		this->setGameState(GAME_OVER);
	}
}

void GameManager::gameOver()
{
	cout << "Game Over" << endl;
}

void GameManager::show()
{
	this->map->showMaze();
}
