#include "Edge.h"
#include "Piece.h"
#include "Puzzle.h"

#include <iostream>

int main() {

	Edge* edge1 = new FemaleEdge(123456);
	Edge* edge2 = new MaleEdge(432157);
	Edge* edge3 = new StraightEdge(513246);
	Edge* edge4 = new StraightEdge(654327);

	cout << (edge1->matchWith(*edge2) ? "true" : "false") << endl;		// true
	cout << edge1->getMatchingEdge()->getId() << endl;					// 432157
	cout << edge2->getMatchingEdge()->getId() << endl;					// 123465

	cout << (edge2->matchWith(*edge3) ? "true" : "false") << endl;		// false
	cout << (edge3->matchWith(*edge1) ? "true" : "false") << endl;		// true

	cout << (edge4->matchWith(*edge3) ? "true" : "false") << endl;		// true
	cout << edge3->getMatchingEdge()->getId() << endl;					// 654327
	cout << edge4->getMatchingEdge()->getId() << endl;					// 513246

	edge1->breakMatch();
	edge3->breakMatch();
	
	// CompositeEdge
	Edge* edge5 = new MaleEdge(562258);
	Edge* edge6 = new FemaleEdge(957585);

	CompositeEdge* edge7 = new CompositeEdge(87653487);
	CompositeEdge* edge8 = new CompositeEdge(15121304);
	edge7->addEdge(edge1)->addEdge(edge3)->addEdge(edge5);
	edge8->addEdge(edge2)->addEdge(edge4)->addEdge(edge6);

	cout << (edge7->matchWith(*edge8) ? "true" : "false") << endl;		// true
	cout << edge7->getMatchingEdge()->getId() << endl;					// 15121304
	cout << edge8->getMatchingEdge()->getId() << endl;					// 87653487
	edge8->breakMatch();

	Edge* edge9 = new MaleEdge(561258);
	Edge* edge10 = new FemaleEdge(957515);
	Edge* edge11 = new StraightEdge(847199);
	Edge* edge12 = new FemaleEdge(448486);

	cout << (edge7->matchWith(*edge10) ? "true" : "false") << endl;		// false
	edge8->addEdge(edge10);
	cout << (edge7->matchWith(*edge8) ? "true" : "false") << endl;		// false

	CompositeEdge* edge13 = new CompositeEdge(95785521);
	edge13->addEdge(edge9)->addEdge(edge12)->addEdge(edge11);
	cout << (edge7->matchWith(*edge13) ? "true" : "false") << endl;		// false
	
	delete edge13;
	edge13 = new CompositeEdge(95785521);
	edge13->addEdge(edge9)->addEdge(edge11)->addEdge(edge12);
	edge1->matchWith(*edge9);
	edge3->matchWith(*edge11);
	edge5->matchWith(*edge12);
	cout << (edge7->matchWith(*edge13) ? "true" : "false") << endl;		// true

	delete edge1;
	delete edge2;
	delete edge3;
	delete edge4;
	delete edge5;
	delete edge6;
	delete edge7;
	delete edge8;
	delete edge9;
	delete edge10;
	delete edge11;
	delete edge12;
	delete edge13;

	return 0;
}