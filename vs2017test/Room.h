#pragma once
#include <iostream>
#include <fstream>
#include "Definitions.h"
#include "Point.h"

using namespace std;

class Room
{
private:
	static constexpr float OBSTACLES_PRECENTAGE = 0.05f;
	static constexpr int MIN_OBSTACLES = 5;
	static constexpr int NUM_OF_AMMO_STORAGE = 2;
	static constexpr int NUM_OF_HEALTH_STORAGE = 2;
	int width, height;
	Point center;

	void addObjects(int** maze, int numOfObjects, MapCell object);

public:
	Room() = delete;
	Room(int width, int height, Point&& center);
	Room(ifstream& in);
	~Room();

	int getWidth() { return this->width; }
	void setWidth(int w) { this->width = w; }
	int getHeight() { return this->height; }
	void setHeight(int h) { this->height = h; }
	Point getCenter() { return this->center; }
	void setCenter(Point center) { this->center = center; }
	void initRoom(int** maze);
	friend ostream& operator<<(ostream& os, const Room& room);
	friend istream& operator>>(istream& in, Room& room);
};
