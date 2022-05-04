#pragma once

#include "Edge.h"
#include "Piece.h"

class Puzzle {

	Puzzle* top_left;
	Puzzle* top_right;
	Puzzle* bottom_left;
	Puzzle* bottom_right;

public:
	Puzzle();
	~Puzzle();
	Puzzle crop(int[3], int[3]) const ;
	void patch(Puzzle);
};