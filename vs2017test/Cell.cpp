#include <math.h>
#include "Cell.h"

Cell::Cell()
{
}

// gets row, column, parent, g, target row and target column
Cell::Cell(int r, int c, Cell *p, double g, int tr, int tc)
{
	this->row = r;
	this->col = c;
	this->parent = p;
	this->g = g;
	this->targetRow = tr;
	this->targetCol = tc;
	this->ComputeH();
	this->ComputeF();
}

Cell::~Cell()
{
}

void Cell::ComputeH()
{
	this->h = sqrt(pow(row - targetRow, 2) + pow(col - targetCol, 2));
}

