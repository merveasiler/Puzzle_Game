#include "Puzzle.h"


/****************************************************/
/****              *** PUZZLE ***                ****/

/* Contsructor : It takes three integers in the following order:
	The first argument is size of the puzzle which is 2^N for some N >= 0.
	The second argument is the initial row id of the puzzle.
	The third argument is the initial column id of the puzzle.

	After initialization with the above arguments, the necessary
	pointers should be initialized to NULL.
	Note that the final row id in this puzzle is equal to:
	   initial_row_id + size - 1.
	Note that the final column id in this puzzle is equal to:
	   initial_column_id + size - 1.
*/
Puzzle::Puzzle(int size, int first_row, int first_column) {

	this->size = size;
	this->first_row = first_row;
	this->first_column = first_column;

	this->piece = NULL;

	this->top_left = NULL;
	this->top_right = NULL;
	this->bottom_left = NULL;
	this->bottom_right = NULL;
}

/* Destructor  : It should destruct its sub-puzzles, yet it is NOT responsible
   of the destruction of its Piece member.
*/
Puzzle::~Puzzle() {
	if (top_left)
		delete this->top_left;
	if (top_right)
		delete this->top_right;
	if (bottom_left)
		delete this->bottom_left;
	if (bottom_right)
		delete this->bottom_right;

	this->top_left = NULL;
	this->top_right = NULL;
	this->bottom_left = NULL;
	this->bottom_right = NULL;

	this->piece = NULL;
}

/* Copy constructor : It totally applies deep copy.
*/
Puzzle::Puzzle(const Puzzle& puzzle) {

	this->size = puzzle.size;
	this->first_row = puzzle.first_row;
	this->first_column = puzzle.first_column;

	this->piece = NULL;
	if (puzzle.piece)
		this->piece = new Piece(*puzzle.piece);

	this->top_left = NULL;
	this->top_right = NULL;
	this->bottom_left = NULL;
	this->bottom_right = NULL;

	if (puzzle.top_left)
		this->top_left = new Puzzle(*puzzle.top_left);
	if (puzzle.top_right)
		this->top_right = new Puzzle(*puzzle.top_right);
	if (puzzle.bottom_left)
		this->bottom_left = new Puzzle(*puzzle.bottom_left);
	if (puzzle.bottom_right)
		this->bottom_right = new Puzzle(*puzzle.bottom_right);

}

/* Assignment operator : It totally applies shallow copy.
*/
Puzzle& Puzzle::operator=(const Puzzle& puzzle) {
	
	if (top_left)
		delete this->top_left;
	if (top_right)
		delete this->top_right;
	if (bottom_left)
		delete this->bottom_left;
	if (bottom_right)
		delete this->bottom_right;

	this->top_left = puzzle.top_left;
	this->top_right = puzzle.top_right;
	this->bottom_left = puzzle.bottom_left;
	this->bottom_right = puzzle.bottom_right;

	this->piece = puzzle.piece;
	return *this;
}

/* This method directly assigns (without copying) the given Piece object to
   the corresponding sub-puzzle (cell) whose indices given in the second
   argument in array form as follows <row_id, column_id>.
*/
void Puzzle::placePiece(const Piece& piece, int coords[2]) {

	if (size == 1) {
		this->piece = &piece;
		return;
	}

	int subsize = size / 2;
	if (coords[0] < first_row + subsize) {
		if (coords[1] < first_column + subsize) {
			if (top_left == NULL)
				top_left = new Puzzle(subsize, first_row, first_column);
			top_left->placePiece(piece, coords);
		}
		else {
			if (top_right == NULL)
				top_right = new Puzzle(subsize, first_row, first_column + subsize);
			top_right->placePiece(piece, coords);
		}
	}
	else {
		if (coords[1] < first_column + subsize) {
			if (bottom_left == NULL)
				bottom_left = new Puzzle(subsize, first_row + subsize, first_column);
			bottom_left->placePiece(piece, coords);
		}
		else {
			if (bottom_right == NULL)
				bottom_right = new Puzzle(subsize, first_row + subsize, first_column + subsize);
			bottom_right->placePiece(piece, coords);
		}
	}

}

/* It returns directly the piece object located in the sub-puzzle (cell)
   whose row id and column id are given in the first and second elements of
   2D array as argument, respectively. If there is no piece in the requested
   indices, then this method throws an EmptyCellRequest exception defined in
   Exception.h file.
*/
const Piece& Puzzle::getPiece(int coords[2]) {
	if (size == 1)
		return *piece;

	int subsize = size / 2;
	if (coords[0] < first_row + subsize) {
		if (coords[1] < first_column + subsize) {
			if (top_left == NULL)
				throw EmptyCellRequest();
			else {
				try {
					return top_left->getPiece(coords);
				}
				catch (EmptyCellRequest e) {
					throw EmptyCellRequest();
				}
			}
		}
		else {
			if (top_right == NULL)
				throw EmptyCellRequest();
			else {
				try {
					return top_right->getPiece(coords);
				}
				catch (EmptyCellRequest e) {
					throw EmptyCellRequest();
				}
			}
		}
	}
	else {
		if (coords[1] < first_column + subsize) {
			if (bottom_left == NULL)
				throw EmptyCellRequest();
			else {
				try {
					return bottom_left->getPiece(coords);
				}
				catch (EmptyCellRequest e) {
					throw EmptyCellRequest();
				}
			}
		}
		else {
			if (bottom_right == NULL)
				throw EmptyCellRequest();
			else {
				try {
					return bottom_right->getPiece(coords);
				}
				catch (EmptyCellRequest e) {
					throw EmptyCellRequest();
				}
			}
		}
	}
}

/* This method returns the sub-puzzle whose initial and final row-column ids
   are given in the first and second arguments, respectively. The indices
   given in the arguments will be given as an exact correspondence to one of
   the sub-puzzles of the current puzzle object.
*/
Puzzle Puzzle::crop(int from[2], int to[2]) const {

	if (this->first_row == from[1] && this->first_column == from[0] && this->first_row + size - 1 == to[1] && this->first_column + size - 1 == to[0])
		return *this;

	int subsize = size / 2;

	if (from[1] < this->first_row + subsize) {
		if (from[0] < this->first_column + subsize)
			return top_left->crop(from, to);
		else
			return bottom_left->crop(from, to);
	}
	else {
		if (from[0] < this->first_column + subsize)
			return top_right->crop(from, to);
		else
			return bottom_right->crop(from, to);
	}

}

/*
	This method puts (patches) the given puzzle onto the corresponding part
	of the current puzzle object. To which part it will be patched on could
	be determined by just checking the initial row-column indices and the size
	of the puzzle given in the argument.
	Unlike crop() method, the puzzle given in the argument may not be an exact
	correspondence of some sub-puzzle. It is ensured that the given argument will
	be located on some sub-space of the current puzzle, yet it may *partially*
	overlap with some or more sub-puzzles (See the figure in the pdf).
	The patch operation requires deep-copy of the corresponding sub-puzzles
	whereas it requires shallow copy of the corresponding Piece objects.

	Hint: You may get benefit from placePiece() method and you may start your
	operation by clearing the corresponding parts of the current puzzle.
*/
void Puzzle::patch(const Puzzle& puzzle) {

	int from[2] = { puzzle.first_row, puzzle.first_column };
	int to[2] = { puzzle.first_row + puzzle.size - 1, puzzle.first_column + puzzle.size - 1 };
	this->clearParts(from, to);

	vector<pair> pieces = puzzle.getPieces();
	for (int i = 0; i < pieces.size(); i++) {
		int location[2] = { pieces[i].x, pieces[i].y };
		this->placePiece(*pieces[i].piece, location);
	}
}

vector<Puzzle::pair> Puzzle::getPieces() const {

	vector<pair> sub_part_pairs[4];
	vector<pair> pairs;

	if (size == 1) {
		pair p(this->piece, this->first_row, this->first_column);
		pairs.push_back(p);
		return pairs;
	}

	if (top_left)
		sub_part_pairs[0] = top_left->getPieces();
	if (top_right)
		sub_part_pairs[1] = top_right->getPieces();
	if (bottom_left)
		sub_part_pairs[2] = bottom_left->getPieces();
	if (bottom_right)
		sub_part_pairs[3] = bottom_right->getPieces();

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < sub_part_pairs[i].size(); j++)
			pairs.push_back(sub_part_pairs[i][j]);
		sub_part_pairs[i].clear();
	}

	return pairs;
}

void Puzzle::clearParts(int from[2], int to[2]) {

	int subsize = size / 2;
	if (from[0] < this->first_row + subsize) {
		if (from[1] < this->first_column + subsize) {		// does overlap with top_left?
			int sub_to[2] = { (to[0] < this->first_row + subsize) ? to[0] : this->first_row + subsize - 1,
								(to[1] < this->first_column + subsize) ? to[1] : this->first_column + subsize - 1 };
			if (this->top_left) {
				if (this->top_left->first_row == from[0] && this->top_left->first_column == from[1] &&
					this->top_left->size == sub_to[1] - from[1] + 1 && this->top_left->size == sub_to[0] - from[0] + 1) {
					delete this->top_left;
					this->top_left = NULL;
				}
				else
					this->top_left->clearParts(from, sub_to);
			}
		}
		if (this->first_column + subsize <= to[1]) {			// does overlap with top_right?
			int sub_from[2] = { from[0], (from[1] < this->first_column + subsize) ? this->first_column + subsize : from[1] };
			int sub_to[2] = { (to[0] < this->first_row + subsize) ? to[0] : this->first_row + subsize - 1, to[1] };
			if (this->top_right) {
				if (this->top_right->first_row == sub_from[0] && this->top_right->first_column == sub_from[1] &&
					this->top_right->size == sub_to[1] - sub_from[1] + 1 && this->top_right->size == sub_to[0] - sub_from[0] + 1) {
					delete this->top_right;
					this->top_right = NULL;
				}
				else
					this->top_right->clearParts(sub_from, sub_to);
			}
		}
	}
	if (this->first_row + subsize <= to[0]) {
		if (from[1] < this->first_column + subsize) {		// does overlap with bottom_left?
			int sub_from[2] = { (from[0] < this->first_row + subsize) ? this->first_row + subsize : from[0], from[1] };
			int sub_to[2] = { to[0], (to[1] < this->first_column + subsize) ? to[1] : this->first_column + subsize - 1 };
			if (this->bottom_left) {
				if (this->bottom_left->first_row == sub_from[0] && this->bottom_left->first_column == sub_from[1] &&
					this->bottom_left->size == sub_to[1] - sub_from[1] + 1 && this->bottom_left->size == sub_to[0] - sub_from[0] + 1) {
					delete this->bottom_left;
					this->bottom_left = NULL;
				}
				else
					this->bottom_left->clearParts(sub_from, sub_to);
			}
		}
		if (this->first_column + subsize <= to[1]) {			// does overlap with bottom_right?
			int sub_from[2] = { (from[0] < this->first_row + subsize) ? this->first_row + subsize : from[0],
								(from[1] < this->first_column + subsize) ? this->first_column + subsize : from[1] };
			if (this->bottom_right) {
				if (this->bottom_right->first_row == sub_from[0] && this->bottom_right->first_column == sub_from[1] &&
					this->bottom_right->size == to[1] - sub_from[1] + 1 && this->bottom_right->size == to[0] - sub_from[0] + 1) {
					delete this->bottom_right;
					this->bottom_right = NULL;
				}
				else
					this->bottom_right->clearParts(sub_from, to);
			}
		}
	}
}

