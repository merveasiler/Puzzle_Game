#ifndef __PUZZLE_H__
#define __PUZZLE_H__

#include "Edge.h"
#include "Piece.h"
#include "Exception.h"

//////////////////////////////////////////////////////
//  DO NOT CHANGE *SPECIFIED PARTS* OF THIS FILE!   // 
//////////////////////////////////////////////////////
class Puzzle {

	/**/ /**************************/ /**/
	/**/ Puzzle* top_left;            /**/
	/**/ Puzzle* top_right;           /**/
	/**/ Puzzle* bottom_left;         /**/
	/**/ Puzzle* bottom_right;        /**/
	/**/ int size;                    /**/
	/**/ int first_row, first_column; /**/
	/**/ const Piece* piece;          /**/
	/**/ /**************************/ /**/
	// DO NOT MODIFY ABOVE

	// YOU CAN DEFINE YOUR OWN VARIABLES, METHODS, DATA STRUCTURES, etc. HERE!
	// ...
	struct pair {
		const Piece* piece;
		int x;
		int y;
		pair(const Piece* piece1, int x1, int y1) : piece(piece1), x(x1), y(y1) {};
	};
	void clearParts(int from[2], int to[2]);
	vector<pair> getPieces() const;

	// DO NOT MODIFY BELOW
public:
	Puzzle(int, int, int);
	~Puzzle();
	Puzzle(const Puzzle&);
	Puzzle& operator=(const Puzzle&);
	void placePiece(const Piece&, int[2]);
	const Piece& getPiece(int[2]);
	Puzzle crop(int[2], int[2]) const;
	void patch(const Puzzle&);
	friend ostream& operator<< (ostream&, const Puzzle&);

};

#endif
