#pragma once

class Cell
{
private:
	int row, col;
	int targetRow, targetCol;
	Cell* parent;
	double f, g, h;

public:
	Cell();
	Cell(int r, int c, Cell* p, double g, int tr, int tc);
	~Cell();

	int getRow() { return this->row; }
	int getCol() { return this->col; }
	int getTargetRow() { return this->targetRow; }
	int getTargetCol() { return this->targetCol; }
	Cell* getParent() { return this->parent; }
	double getF() { return this->f; }
	double getG() { return this->g; }
	void setG(double g) { this->g = g; }
	void computeH();
	void computeF() { this->f = this->g + this->h; }
	bool operator==(const Cell& other) { return this->row == other.row && this->col == other.col; }
};
