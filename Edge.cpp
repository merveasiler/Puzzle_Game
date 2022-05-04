#include "Edge.h"

/* ************************ Edge ************************ */
Edge::Edge(char identity) {

	this->identity = identity;
	this->matchingEdge = NULL;
}

Edge::~Edge() {

	this->matchingEdge = NULL;
}

bool Edge::matchWith(Edge& edge) {

	if (edge.matchWith(identity)) {
		this->matchingEdge = &edge;
		edge.matchWith(*this);
	}

	return false;
}

void Edge::breakMatch() {

	Edge* temp = this->matchingEdge;
	this->matchingEdge = NULL;

	if (temp)
		temp->breakMatch();
}

/* ************************ StraightEdge ************************ */
StraightEdge::StraightEdge() : Edge('S') {
	
}

StraightEdge::~StraightEdge() {

}

bool StraightEdge::matchWith(char code) {
	
	if (code == 'S')
		return true;
	return false;
}

/* ************************ FemaleEdge ************************ */
FemaleEdge::FemaleEdge() : Edge('F') {

}

FemaleEdge::~FemaleEdge() {

}

bool FemaleEdge::matchWith(char code) {

	if (code == 'M')
		return true;
	return false;
}

/* ************************ MaleEdge ************************ */
MaleEdge::MaleEdge() : Edge('M') {

}

MaleEdge::~MaleEdge() {

}

bool MaleEdge::matchWith(char code) {
	
	if (code == 'F')
		return true;
	return false;
}

/* ************************ CompositeEdge ************************ */
CompositeEdge::CompositeEdge() : Edge('C') {
	
	this->matchIndex = -1;
}

CompositeEdge::~CompositeEdge() {
	
	this->edges.clear();
}

bool CompositeEdge::matchWith(char code) {
	
	if (code == 'C') {
		this->matchIndex++;
		return true;
	}
	return false;
}

bool CompositeEdge::matchWith(Edge& edge) {

	if (this->matchIndex < 0) {			// if this is the first time, do type control
		if (edge.matchWith(identity)) {		// if the types match (both are 'C')
			for (unsigned int i = 0; i < this->edges.size(); i++) {
				if (edge.matchWith(*(this->edges[i])))	// if the corresponding edges matches
					continue;
				this->breakMatch();						// there occurred some mismatch, so break the previous matches
				return false;
			}
			if (!edge.matchWith(*this))			// check whether the other composite edge has also finished
				return true;
			this->breakMatch();							// there occurred size inconsistency, so break each match
			return false;
		}
		else								// if types do not match
			return false;
	}
	else {								// if this is not the first time, then the argument is some member edge of the composite edge 
		if (this->matchIndex == this->edges.size()) {
			this->matchIndex = -1;
			return false;
		}
		if (this->edges[matchIndex]->matchWith(edge)) {	// if the corresponding member edges matches
			this->matchIndex++;
			return true;
		}
		else {								// if the correspondig member edges do not match
			this->matchIndex = -1;
			return false;
		}
	}
}

void CompositeEdge::breakMatch() {

	for (unsigned int i = 0; i < this->edges.size(); i++)
		this->edges[i]->breakMatch();

}

CompositeEdge* CompositeEdge::addEdge(Edge* edge) {
	
	this->edges.push_back(edge);
	this->matchIndex = -1;
}