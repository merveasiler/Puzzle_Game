#include "Piece.h"

/****************************************************/
/****               *** PIECE ***                ****/

/* Contsructor : initializes <edges> of the object to the those given in the
   argument. The edges given in the argument array should be cloned first,
   and its clones should be reserved, not the edges themselves.
   Note that the ordering of the given edges will always be as follows:
   edges[0]: Left side edge,
   edges[1]: Bottom side edge,
   edges[2]: Right side edge,
   edges[3]: Top side edge.
*/
Piece::Piece(Edge* edges[4]) {

	for (int i = 0; i < 4; i++)
		this->edges[i] = edges[i]->clone();

}

/* Destructor  : It should destruct its edges too.
*/
Piece::~Piece() {

	for (int i = 0; i < 4; i++) {
		delete this->edges[i];
		this->edges[i] = NULL;
	}
}

/* Copy constructor : Apply deep copy.
*/
Piece::Piece(const Piece& piece) {

	for (int i = 0; i < 4; i++)
		this->edges[i] = piece.edges[i]->clone();
}

// This is already implemented for you, do NOT change it!
ostream& operator<< (ostream& os, const Piece& piece) {

	for (int i = 0; i < 4; i++)
		os << piece.edges[i]->getId() << "  \n";
	return os;
}
