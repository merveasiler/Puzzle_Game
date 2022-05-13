#include "Puzzle.h"

Puzzle::Puzzle(int size, int start_x, int start_y) {

	this->size = size;
	this->start_x = start_x;
	this->start_y = start_y;

	this->piece = NULL;

	this->top_left = NULL;
	this->top_right = NULL;
	this->bottom_left = NULL;
	this->bottom_right = NULL;
}

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

Puzzle::Puzzle(const Puzzle& puzzle) {

	this->size = puzzle.size;
	this->start_x = puzzle.start_x;
	this->start_y = puzzle.start_y;

	if (puzzle.piece)
		this->piece = new Piece(*puzzle.piece);

	if (puzzle.top_left)
		this->top_left = new Puzzle(*puzzle.top_left);
	if (puzzle.top_right)
		this->top_right = new Puzzle(*puzzle.top_right);
	if (puzzle.bottom_left)
		this->bottom_left = new Puzzle(*puzzle.bottom_left);
	if (puzzle.bottom_right)
		this->bottom_right = new Puzzle(*puzzle.bottom_right);

}

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

void Puzzle::placePiece(const Piece& piece, int coords[2]) {

	if (size == 1) {
		this->piece = &piece;
		return;
	}

	int subsize = size / 2;
	if (coords[1] < start_x + subsize) {
		if (coords[0] < start_y + subsize) {
			if (top_left == NULL)
				top_left = new Puzzle(subsize, start_x, start_y);
			top_left->placePiece(piece, coords);
		}
		else {
			if (bottom_left == NULL)
				bottom_left = new Puzzle(subsize, start_x, start_y + subsize);
			bottom_left->placePiece(piece, coords);
		}
	}
	else {
		if (coords[0] < start_y + subsize) {
			if (top_right == NULL)
				top_right = new Puzzle(subsize, start_x + subsize, start_y);
			top_right->placePiece(piece, coords);
		}
		else {
			if (bottom_right == NULL)
				bottom_right = new Puzzle(subsize, start_x + subsize, start_y + subsize);
			bottom_right->placePiece(piece, coords);
		}
	}

}

Puzzle Puzzle::crop(int from[2], int to[2]) const {

	if (this->start_x == from[1] && this->start_y == from[0] && this->start_x + size - 1 == to[1] && this->start_y + size - 1 == to[0])
		return *this;

	int subsize = size / 2;

	if (from[1] < this->start_x + subsize) {
		if (from[0] < this->start_y + subsize)
			return top_left->crop(from, to);
		else
			return bottom_left->crop(from, to);
	}
	else {
		if (from[0] < this->start_y + subsize)
			return top_right->crop(from, to);
		else
			return bottom_right->crop(from, to);
	}

}

void Puzzle::patch(Puzzle puzzle) {

	if (this->start_x == puzzle.start_x && this->start_y == puzzle.start_y && this->size == puzzle.size)
		*this = puzzle;

	else {
		int subsize = size / 2;
		if (puzzle.start_x < this->start_x + subsize) {
			if (puzzle.start_y < this->start_y + subsize) {						// does overlap with top_left?
				int from[2] = {puzzle.start_x, puzzle.start_y };
				int to[2] = { (puzzle.start_x + puzzle.size <= this->start_x + subsize) ? puzzle.start_x + puzzle.size - 1 : this->start_x + subsize - 1,
							  (puzzle.start_y + puzzle.size <= this->start_y + subsize) ? puzzle.start_y + puzzle.size - 1 : this->start_y + subsize - 1 };
				this->top_left->patch(puzzle.crop(from, to));
			}
			if (this->start_y + subsize <= puzzle.start_y + puzzle.size - 1) {	// does overlap with bottom_left?
				int from[2] = { (puzzle.start_x), 
								(puzzle.start_y < this->start_y + subsize) ? this->start_y + subsize : puzzle.start_y };
				int to[2] = { (puzzle.start_x + puzzle.size <= this->start_x + subsize) ? puzzle.start_x + puzzle.size - 1 : this->start_x + subsize - 1,
							  (puzzle.start_y + puzzle.size - 1) };
				this->bottom_left->patch(puzzle.crop(from, to));
			}
		}
		if (this->start_x + subsize <= puzzle.start_x + puzzle.size - 1) {
			if (puzzle.start_y < this->start_y + subsize) {						// does overlap with top_right?
				int from[2] = { (puzzle.start_x >= this->start_x + subsize) ? puzzle.start_x : this->start_x + subsize,
								(puzzle.start_y) };
				int to[2] = { (puzzle.start_x + puzzle.size - 1),
							  (puzzle.start_y + puzzle.size - 1 < this->start_y + subsize) ? puzzle.start_y + puzzle.size - 1 : this->start_y + subsize - 1 };
				this->top_right->patch(puzzle.crop(from, to));
			}
			if (this->start_y + subsize <= puzzle.start_y + puzzle.size - 1) {	// does overlap with bottom_right?
				int from[2] = { (puzzle.start_x >= this->start_x + subsize) ? puzzle.start_x : this->start_x + subsize,
								(puzzle.start_y >= this->start_y + subsize) ? puzzle.start_y : this->start_y + subsize };
				int to[2] = { puzzle.start_x + puzzle.size - 1, puzzle.start_y + puzzle.size - 1 };
				this->bottom_right->patch(puzzle.crop(from, to));
			}
		}
	}

}

