#pragma once
#include <iostream>
#include <fstream>
#include "Definitions.h"
#include "Point.h"
#include "AmmoStorage.h"
#include "HealthStorage.h"

using namespace std;

class Room
{
public:
	static constexpr int NUM_OF_AMMO_STORAGE = 2;
	static constexpr int NUM_OF_HEALTH_STORAGE = 2;
private:
	static constexpr float OBSTACLES_PRECENTAGE = 0.05f;
	static constexpr int MIN_OBSTACLES = 5;
	int width, height;
	Point center;
	AmmoStorage *ammoStorages[NUM_OF_AMMO_STORAGE];
	HealthStorage *healthStorages[NUM_OF_HEALTH_STORAGE];

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
	AmmoStorage** getAmmoStorages() { return this->ammoStorages; }
	HealthStorage** getHealthStorages() { return this->healthStorages; }
	void initRoom(int** maze);
	friend ostream& operator<<(ostream& os, const Room& room);
	friend istream& operator>>(istream& in, Room& room);
};
