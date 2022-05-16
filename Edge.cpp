#include "Edge.h"

/****************************************************/
/****                *** EDGE ***                ****/

/* Contsructor : initializes <id> of the object to the given integer
   and <password> of the object to the given Password object.
*/
Edge::Edge(int id, Password password) {

	this->id = id;
	this->password = password;
	this->matchingEdge = NULL;
}

/* Destructor  : It is NOT responsible of the destruction of the matchingEdge!
*/
Edge::~Edge() {

	if (this->matchingEdge)
		this->breakMatch();
}

/* Returns the <id> of the object
*/
int Edge::getId() const {

	return this->id;
}

/* Returns the pointer to the matching partner of the current edge.
   If the edge had not been matched before, it returns NULL.
*/
Edge* Edge::getMatchingEdge() const {

}

/* It tries to match the current Edge object with the one given in the argument.
   If the two edges are matchable then it does the matching by storing
   <matchingEdge> variables with each other, and returns true. Otherwise,
   it does not match and returns false.
   It applies the matching rules given in the pdf.
   Note that match operation is a mutual operation. Namely, if the current
   edge is matched, then its partner edge should be matched with the current
   one too.
   Hint: It may need matchWithHelper(Password) method.
*/
bool Edge::matchWith(Edge& edge) {

	if (edge.matchWithHelper(password)) {
		this->matchingEdge = &edge;
		if (edge.getMatchingEdge() != NULL && edge.getMatchingEdge()->getId() == this->id)
			;
		else
			edge.matchWith(*this);
		return true;
	}

	return false;
}

/* If the current edge was matched with some edge before, then this method
   breaks the match, i.e. there is no match between those two edges anymore.
   Note that breaking match operation is a mutual operation. Namely, if the
   matching of the current edge is broken, the matching recorded in its partner
   edge should be broken too.
*/
void Edge::breakMatch() {

	Edge* temp = this->matchingEdge;
	this->matchingEdge = NULL;

	if (temp)
		temp->breakMatch();
}

/****************************************************/
/****            *** STRAIGHT EDGE ***           ****/

/* Contsructor : initializes <id> of the object to the given integer
   and <password> of the object.
   Note that Password variable has a fixed value which is SEND_ME_STRAIGHT,
   therefore it is not given as an argument.
*/
StraightEdge::StraightEdge(int id) : Edge(id, SEND_ME_STRAIGHT) {
	
}

/* Destructor  : It is not responsible of the destruction of the matchingEdge!
*/
StraightEdge::~StraightEdge() {

}

/* This method clones the current object and returns the pointer to its clone.
   Cloning is actually a deep-copy operation, so you need to construct a new
   StraightEdge object.
   Note that if the current edge is matched with some other edge, then its
   matchingEdge should be cloned too and only the clones should be matched
   with each other.
*/
Edge* StraightEdge::clone() const {

	StraightEdge* edge = new StraightEdge(this->id);
	if (this->matchingEdge != NULL) {
		edge->matchingEdge = new StraightEdge(this->matchingEdge->getId());
		edge->matchingEdge->matchWith(*edge);
	}
	return edge;
}

/* This method may be needed as a helper for the operation of matchWith(Edge&).
*/
bool StraightEdge::matchWithHelper(Password password) {
	
	if (password == SEND_ME_STRAIGHT)
		return true;
	return false;
}

/****************************************************/
/****            *** INWARDS EDGE ***            ****/

/* Contsructor : initializes <id> of the object to the given integer
   and <password> of the object.
   Note that Password variable has a fixed value which is SEND_ME_OUTWARDS,
   therefore it is not given as an argument.
*/
InwardsEdge::InwardsEdge(int id) : Edge(id, SEND_ME_OUTWARDS) {

}

/* Destructor  : It is not responsible of the destruction of the matchingEdge!
*/
InwardsEdge::~InwardsEdge() {

}

/* This method clones the current object and returns the pointer to its clone.
   Cloning is actually a deep-copy operation, so you need to construct a new
   InwardsEdge object.
   Note that if the current edge is matched with some other edge, then its
   matchingEdge should be cloned too and only the clones should be matched
   with each other.
*/
Edge* InwardsEdge::clone() const {

	InwardsEdge* edge = new InwardsEdge(this->id);
	if (this->matchingEdge != NULL) {
		edge->matchingEdge = new OutwardsEdge(this->matchingEdge->getId());
		edge->matchingEdge->matchWith(*edge);
	}
	return edge;
}

/* This method may be needed as a helper for the operation of matchWith(Edge&).
*/
bool InwardsEdge::matchWithHelper(Password password) {

	if (password == SEND_ME_INWARDS)
		return true;
	return false;
}

/****************************************************/
/****            *** OUTWARDS EDGE ***           ****/

/* Contsructor : initializes <id> of the object to the given integer
   and <password> of the object.
   Note that Password variable has a fixed value which is SEND_ME_INWARDS,
   therefore it is not given as an argument.
*/
OutwardsEdge::OutwardsEdge(int id) : Edge(id, SEND_ME_INWARDS) {

}

/* Destructor  : It is not responsible of the destruction of the matchingEdge!
*/
OutwardsEdge::~OutwardsEdge() {

}

/* This method clones the current object and returns the pointer to its clone.
   Cloning is actually a deep-copy operation, so you need to construct a new
   OutwardsEdge object.
   Note that if the current edge is matched with some other edge, then its
   matchingEdge should be cloned too and only the clones should be matched
   with each other.
*/
Edge* OutwardsEdge::clone() const {

	OutwardsEdge* edge = new OutwardsEdge(this->id);
	if (this->matchingEdge != NULL) {
		edge->matchingEdge = new InwardsEdge(this->matchingEdge->getId());
		edge->matchingEdge->matchWith(*edge);
	}
	return edge;
}

/* This method may be needed as a helper for the operation of matchWith(Edge&).
*/
bool OutwardsEdge::matchWithHelper(Password password) {
	
	if (password == SEND_ME_OUTWARDS)
		return true;
	return false;
}

/****************************************************/
/****            *** COMPOSITE EDGE ***          ****/

/* Contsructor : initializes <id> of the object to the given integer
   and <password> of the object.
   Note that Password variable has a fixed value which is SEND_ME_COMPLETING_COMPOSITE,
   therefore it is not given as an argument.
   Note that you may need to initialize matchIndex variable with some value
   so that you may benefit from that during any match operation.
*/
CompositeEdge::CompositeEdge(int id) : Edge(id, SEND_ME_COMPLETING_COMPOSITE) {
	
	this->matchIndex = -1;
}

/* Destructor  : It is not responsible of the destruction of the matchingEdge!
*/
CompositeEdge::~CompositeEdge() {
	
	this->edges.clear();
}

/* This method clones the current object and returns the pointer to its clone.
   Cloning is actually a deep-copy operation, so you need to construct a new
   CompositeEdge object. During the construction, each member Edge object
   should be cloned too, and the clone of the current CompositeEdge should
   include only the clones of the member edges.
   Note that if the current edge is matched with some other edge, then its
   matchingEdge should be cloned too and only the clones should be matched
   with each other.
*/
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

/* This method may be needed as a helper for the operation of matchWith(Edge&).
*/
bool CompositeEdge::matchWithHelper(Password password) {
	
	if (password == SEND_ME_COMPLETING_COMPOSITE) {
		this->matchIndex++;
		return true;
	}
	return false;
}

/* It tries to match the current CompositeEdge object with the one given in the
   argument.
   If the two edges are matchable then it does the matching by storing
   <matchingEdge> variables with each other, and returns true. Otherwise,
   it does not match and returns false.
   It applies the matching rules given in the pdf.
   Note that match operation is a mutual operation. Namely, if the current
   edge is matched, then its partner edge should be matched with the current
   one too.
   Hint: It may need matchWithHelper(Password) method.
*/
bool CompositeEdge::matchWith(Edge& edge) {

	if (this->matchIndex < 0) {			// if this is the first time, do type control
		if (edge.matchWithHelper(password)) {		// if the types match (both are 'C')
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

/* If the current edge was matched with some edge before, then this method
   breaks the match, i.e. there is no match between those two edges anymore.
   Note that breaking match operation is a mutual operation. Namely, if the
   matching of the current edge is broken, the matching recorded in its partner
   edge should be broken too.
*/
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

/* This method pushes back the given edge in the argument into the end of the
   member edges vector.
*/
CompositeEdge* CompositeEdge::addEdge(Edge* edge) {
	
	this->edges.push_back(edge);
	this->matchIndex = -1;
	return this;
}