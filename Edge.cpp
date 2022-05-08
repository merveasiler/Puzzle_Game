#include "Edge.h"

#include <iostream>
/* ************************ Edge ************************ */
Edge::Edge(int id, char identity_password) {

	this->id = id;
	this->identity_password = identity_password;
	this->matchingEdge = NULL;
}

Edge::~Edge() {

	if (this->matchingEdge)
		this->breakMatch();
}

int Edge::getId() const {

	return this->id;
}

bool Edge::matchWith(Edge& edge) {

	if (edge.matchWithHelper(identity_password)) {
		this->matchingEdge = &edge;
		if (edge.getMatchingEdge() != NULL && edge.getMatchingEdge()->getId() == this->id)
			;
		else
			edge.matchWith(*this);
		return true;
	}

	return false;
}

bool Edge::matchWithHelper(Edge& edge) {
	
	return edge.matchWith(*this);
}

void Edge::breakMatch() {

	Edge* temp = this->matchingEdge;
	this->matchingEdge = NULL;

	if (temp)
		temp->breakMatch();
}

Edge* Edge::getMatchingEdge() const {

	return matchingEdge;
}

/* ************************ StraightEdge ************************ */
StraightEdge::StraightEdge(int id) : Edge(id, 'S') {
	
}

StraightEdge::~StraightEdge() {

}

Edge* StraightEdge::clone() const {

	StraightEdge* edge = new StraightEdge(this->id);
	if (this->matchingEdge != NULL) {
		edge->matchingEdge = new StraightEdge(this->matchingEdge->getId());
		edge->matchingEdge->matchWith(*edge);
	}
	return edge;
}

bool StraightEdge::matchWithHelper(char identity_password) {
	
	if (identity_password == 'S')
		return true;
	return false;
}

/* ************************ FemaleEdge ************************ */
FemaleEdge::FemaleEdge(int id) : Edge(id, 'F') {

}

FemaleEdge::~FemaleEdge() {

}

Edge* FemaleEdge::clone() const {

	FemaleEdge* edge = new FemaleEdge(this->id);
	if (this->matchingEdge != NULL) {
		edge->matchingEdge = new MaleEdge(this->matchingEdge->getId());
		edge->matchingEdge->matchWith(*edge);
	}
	return edge;
}

bool FemaleEdge::matchWithHelper(char identity_password) {

	if (identity_password == 'M')
		return true;
	return false;
}

/* ************************ MaleEdge ************************ */
MaleEdge::MaleEdge(int id) : Edge(id, 'M') {

}

MaleEdge::~MaleEdge() {

}

Edge* MaleEdge::clone() const {

	MaleEdge* edge = new MaleEdge(this->id);
	if (this->matchingEdge != NULL) {
		edge->matchingEdge = new FemaleEdge(this->matchingEdge->getId());
		edge->matchingEdge->matchWith(*edge);
	}
	return edge;
}

bool MaleEdge::matchWithHelper(char identity_password) {
	
	if (identity_password == 'F')
		return true;
	return false;
}

/* ************************ CompositeEdge ************************ */
CompositeEdge::CompositeEdge(int id) : Edge(id, 'C') {
	
	this->matchIndex = -1;
}

CompositeEdge::~CompositeEdge() {
	
	this->edges.clear();
}

Edge* CompositeEdge::clone() const {

	CompositeEdge* edge = new CompositeEdge(this->id);
	edge->matchIndex = this->matchIndex;
	for (unsigned int i = 0; i < edges.size(); i++)
		edge->edges.push_back(edges[i]->clone());

	if (this->matchingEdge != NULL) {
		CompositeEdge* copy_matchingEdge = new CompositeEdge(this->matchingEdge->getId());
		copy_matchingEdge->matchIndex = this->matchIndex;
		for (unsigned int i = 0; i < edges.size(); i++)
			copy_matchingEdge->edges.push_back(edges[i]->getMatchingEdge());
		edge->matchingEdge = copy_matchingEdge;
	}
	return edge;
}

bool CompositeEdge::matchWithHelper(char identity_password) {
	
	if (identity_password == 'C') {
		this->matchIndex++;
		return true;
	}
	return false;
}

bool CompositeEdge::matchWith(Edge& edge) {

	if (this->matchIndex < 0) {			// if this is the first time, do type control
		if (edge.matchWithHelper(identity_password)) {		// if the types match (both are 'C')
			this->matchIndex = 0;
			for (unsigned int i = 0; i < this->edges.size(); i++, this->matchIndex++) {
				if (edge.matchWith(*(this->edges[i])))	// if the corresponding edges match
					continue;
				this->breakMatch();						// there occurred some mismatch, so break the previous matches
				return false;
			}
			if (!edge.matchWith(*this)) {		// check whether the other composite edge has also finished
				this->matchingEdge = &edge;
				return true;
			}
			this->breakMatch();							// there occurred size inconsistency, so break each match
			return false;
		}
		else								// if types do not match
			return false;
	}
	else {		
		// if this is not the first time, then the argument is some member edge of the composite edge 
		if (this->matchIndex == this->edges.size()) {	// there is still an unmatched edge in the other CompositeEdge, yet this one finished.
			this->matchingEdge = &edge;	// even if this is a wrong matching, it will broken in the tail recursion
			return false;
		}
		if (this->edges[matchIndex]->matchWith(edge)) {	// if the corresponding member edges match
			this->matchIndex++;
			return true;
		}
		if (this->matchIndex + 1 == this->edges.size())
			return true;
		else 								// if the correspondig member edges do not match
			return false;
	}
}

void CompositeEdge::breakMatch() {

	if (this->matchIndex >= 0) {
		for (unsigned int i = 0; i < this->edges.size(); i++)
			this->edges[i]->breakMatch();

		this->matchIndex = -1;
		if (this->matchingEdge)
			this->matchingEdge->breakMatch();
		this->matchingEdge = NULL;
	}

}

CompositeEdge* CompositeEdge::addEdge(Edge* edge) {
	
	this->edges.push_back(edge);
	this->matchIndex = -1;
	return this;
}