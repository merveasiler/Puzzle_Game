#pragma once

#include "Edge.h"

class Piece {

	Edge* edges[4];	// left bottom right top

public:
	Piece(Edge* edges[4]);
	~Piece();
	
};