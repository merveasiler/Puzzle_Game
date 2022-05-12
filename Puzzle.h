#pragma once

#include "Edge.h"
#include "Piece.h"

class Puzzle {

	Puzzle* top_left;
	Puzzle* top_right;
	Puzzle* bottom_left;
	Puzzle* bottom_right;

	int size;
	int start_x, start_y;

	const Piece* piece;


public:
	Puzzle(int size, int start_x, int start_y);
	~Puzzle();
	Puzzle(const Puzzle& puzzle);
	Puzzle& operator=(const Puzzle& puzzle);
	void placePiece(const Piece& piece, int coords[2]);
	Puzzle crop(int from[2], int to[2]) const ;
	void patch(Puzzle puzzle);
	friend ostream& operator<< (ostream& os, const Puzzle& puzzle);

};