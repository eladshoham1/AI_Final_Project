#pragma once
#include <iostream>
#include "Definitions.h"

using namespace std;

class Room
{
private:
	static constexpr float OBSTACLES_PRECENTAGE = 0.05;
	static constexpr int MIN_OBSTACLES = 5;
	int centerX, centerY;
	int width, height;

	void addObstacles(int** maze);
public:
	Room();
	~Room();

	void setWidth(int w) { width = w; }
	void setHeight(int h) { height = h; }
	void setCenterX(int x) { centerX = x; }
	void setCenterY(int y) { centerY = y; }

	int getWidth() { return width; }
	int getHeight() { return height; }
	int getCenterX() { return centerX; }
	int getCenterY() { return centerY; }

	void addMeToMaze(int** maze);
};
