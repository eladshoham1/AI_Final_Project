#pragma once
#include "Definitions.h"
#include "Map.h"
#include "Team.h"

class GameManager
{
public:
	enum state { START_GAME, STOP_GAME };
private:
	Map* map;
	state gameState;

public:
	GameManager();
	GameManager(const char* fileName);
	~GameManager();

	Map* getMap() const { return this->map; }
	void setGameState(state gameState) { this->gameState = gameState; }
	void idle();
	void play();
	void stop();
	void show();
};
