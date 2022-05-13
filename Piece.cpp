#include "Piece.h"

Piece::Piece(Edge* edges[4]) {

	for (int i = 0; i < 4; i++)
		this->edges[i] = edges[i]->clone();

}

Piece::~Piece() {

	for (int i = 0; i < 4; i++) {
		delete this->edges[i];
		this->edges[i] = NULL;
	}
}

Piece::Piece(const Piece& piece) {

	for (int i = 0; i < 4; i++)
		this->edges[i] = piece.edges[i]->clone();
}

ostream& operator<< (ostream& os, const Piece& piece) {

	for (int i = 0; i < 4; i++)
		os << piece.edges[i]->getId() << "  \n";
	return os;
}
