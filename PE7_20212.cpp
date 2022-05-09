#include "Edge.h"
#include "Piece.h"
#include "Puzzle.h"

#include <iostream>
#include <sstream>

ostream& operator<< (ostream& os, const Puzzle& puzzle) {

	if (puzzle.piece && !puzzle.top_left && !puzzle.bottom_left && !puzzle.bottom_right && !puzzle.top_right)
		os << puzzle.piece;
	else {
		string subpart = "";
		for (int lr = 0; lr < 2; lr++) {
			ostream& objOstream_left = cout;
			Puzzle* left = NULL, * right = NULL;
			if (lr == 0) {
				left = puzzle.top_left;
				right = puzzle.top_right;
			}
			else {
				left = puzzle.bottom_left;
				right = puzzle.bottom_right;
			}

			if (left)
				objOstream_left << *left << "\n";
			else
				objOstream_left << "\\  /" << "\n" << " \\/ " << "\n" << " /\\ " << "\n" << "/  \\" << "\n\n";

			ostream& objOstream_right = cout;
			if (right)
				objOstream_right << *right << "\n";
			else
				objOstream_right << "\\  /" << "\n" << " \\/ " << "\n" << " /\\ " << "\n" << "/  \\" << "\n\n";

			ostringstream oss_left, oss_right;
			oss_left << objOstream_left.rdbuf();
			oss_right << objOstream_right.rdbuf();
			string objString_left = oss_left.str(), objString_right = oss_right.str();
			for (int i = 0; i < 4; i++) {
				string subpart1_left = objString_left.substr(0, objString_left.find("\n"));
				string subpart2_left = objString_left.substr(objString_left.find("\n") + 1);
				string subpart1_right = objString_right.substr(0, objString_right.find("\n"));
				string subpart2_right = objString_right.substr(objString_right.find("\n") + 1);
				subpart += subpart1_left + "  " + subpart1_right + "\n";
				objString_left = subpart2_left;
				objString_right = subpart2_right;
			}
			subpart += "\n";
		}
		os << subpart;
	}
	return os;
}

int main() {

	//main1();
	main2();

	return 0;
}

void main1() {

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

}

void main2() {

}
