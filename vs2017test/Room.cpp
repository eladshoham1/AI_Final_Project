#include "Room.h"

Room::Room()
{
}

Room::~Room()
{
}

void Room::addObstacles(int** maze)
{
	int roomSize, numOfObstacles, row, col, maxRow, minRow, maxCol, minCol;
	roomSize = height * width;
	numOfObstacles = rand() % ((int)ceil(roomSize * OBSTACLES_PRECENTAGE)) + MIN_OBSTACLES;
	maxRow = centerY + height / 2;
	minRow = centerY - height / 2;
	maxCol = centerX + width / 2;
	minCol = centerX - width / 2;

	for (int i = 0; i < numOfObstacles; i++)
	{
		row = minRow + (rand() % (maxRow - minRow));
		col = minCol + (rand() % (maxCol - minCol));
		maze[row][col] = OBSTACLE;
	}
}

void Room::addMeToMaze(int** maze)
{
	int i, j;

	for (i = centerY - height / 2; i <= centerY + height / 2; i++)
		for (j = centerX - width / 2; j <= centerX + width / 2; j++)
			maze[i][j] = SPACE;

	addObstacles(maze);
}
