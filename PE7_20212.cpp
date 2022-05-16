#include "Edge.h"
#include "Piece.h"
#include "Puzzle.h"

#include <iostream>
#include <sstream>

ostream& operator<< (ostream& os, const Puzzle& puzzle) {

	if (puzzle.size == 1) {
		if (puzzle.piece)
			os << *puzzle.piece << "\n";
		else
			os << "\\  /" << "\n" << " \\/ " << "\n" << " /\\ " << "\n" << "/  \\" << "\n" << "\n";
	}
	else {
		string subpart = "";
		ostringstream objOstream[4] = { ostringstream(""), ostringstream(""), ostringstream(""), ostringstream("") };
		Puzzle* subpuzzles[4] = { puzzle.top_left, puzzle.bottom_left, puzzle.top_right, puzzle.bottom_right };
		
		for (int s = 0; s < 4; s++) {	// top_left bottom_left top_right bottom_right
			if (subpuzzles[s])
				objOstream[s] << *subpuzzles[s];
			else {
				int subsize = puzzle.size / 2;
				for (int i = 0; i < subsize; i++) {
					for (int j = 0; j < subsize; j++)
						objOstream[s] << "\\  /" << "  ";
					objOstream[s] << "\n";
					for (int j = 0; j < subsize; j++)
						objOstream[s] << " \\/ " << "  ";
					objOstream[s] << "\n";
					for (int j = 0; j < subsize; j++)
						objOstream[s] << " /\\ " << "  ";
					objOstream[s] << "\n";
					for (int j = 0; j < subsize; j++)
						objOstream[s] << "/  \\" << "  ";
					objOstream[s] << "\n" << "\n";
				}
			}
		}

		stringstream ss_left, ss_right;
		ss_left << objOstream[0].str() << objOstream[1].str();	// top_left, bottom_left
		ss_right << objOstream[2].str() << objOstream[3].str();	// top_right, bottom_right
		string s_left = ss_left.str(), s_right = ss_right.str();
		
		for (int i = 0; i < (puzzle.size)*4 + (puzzle.size - 1); i++) {
			string subpart_left = s_left.substr(0, s_left.find("\n"));
			s_left = s_left.substr(s_left.find("\n") + 1);
			string subpart_right = s_right.substr(0, s_right.find("\n"));
			s_right = s_right.substr(s_right.find("\n") + 1);
			subpart += subpart_left + subpart_right + "\n";
		}

		os << subpart << "\n";
	}

	return os;
}

void main1();
void main2();

int main() {

	//main1();
	main2();

	return 0;
}

void main1() {

	Edge* edge1 = new InwardsEdge(123456);
	Edge* edge2 = new OutwardsEdge(432157);
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
	Edge* edge5 = new OutwardsEdge(562258);
	Edge* edge6 = new InwardsEdge(957585);

	CompositeEdge* edge7 = new CompositeEdge(87653487);
	CompositeEdge* edge8 = new CompositeEdge(15121304);
	edge7->addEdge(edge1)->addEdge(edge3)->addEdge(edge5);
	edge8->addEdge(edge2)->addEdge(edge4)->addEdge(edge6);

	cout << (edge7->matchWith(*edge8) ? "true" : "false") << endl;		// true
	cout << edge7->getMatchingEdge()->getId() << endl;					// 15121304
	cout << edge8->getMatchingEdge()->getId() << endl;					// 87653487
	edge8->breakMatch();

	Edge* edge9 = new OutwardsEdge(561258);
	Edge* edge10 = new InwardsEdge(957515);
	Edge* edge11 = new StraightEdge(847199);
	Edge* edge12 = new InwardsEdge(448486);

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

	StraightEdge edge11(1111);
	InwardsEdge edge12(2222);
	InwardsEdge edge13(3333);
	OutwardsEdge edge14(4444);
	Edge* edges1[4] = {&edge11, &edge12, &edge13, &edge14};

	Piece* piece1 = new Piece(edges1);
	Piece* piece2 = new Piece(edges1);
	Piece* piece3 = new Piece(edges1);
	Piece* piece4 = new Piece(edges1);
	Piece* piece5 = new Piece(edges1);
	//cout << "Piece:\n" << *piece1 << "\n";
	
	Puzzle* puzzle = new Puzzle(8, 0, 0);
	int location1[2] = {6, 5};
	puzzle->placePiece(*piece1, location1);

	int location2[2] = { 2, 1 };
	puzzle->placePiece(*piece2, location2);

	int location3[2] = { 3, 3 };
	puzzle->placePiece(*piece3, location3);

	int location4[2] = { 0, 7 };
	puzzle->placePiece(*piece4, location4);

	int location5[2] = { 4, 4 };
	puzzle->placePiece(*piece5, location5);

	int loc1[2] = { 2, 2 };
	int loc2[2] = { 3, 3 };
	Puzzle cropped_part = puzzle->crop(loc1, loc2);
	cout << cropped_part;
	cout << *puzzle;

	Puzzle* patch = new Puzzle(2, 4, 3);
	Piece* piece6 = new Piece(edges1);
	int location6[2] = { 5, 3 };
	patch->placePiece(*piece6, location6);
	puzzle->patch(*patch);
	cout << endl << *puzzle;
	delete patch;

	delete piece1;
	delete piece2;
	delete piece3;
	delete piece4;
	delete piece5;
	delete piece6;
	delete puzzle;
}
