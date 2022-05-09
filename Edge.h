#pragma once

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Edge {

protected:
	int id;
	char identity_password;
	Edge* matchingEdge;

public:
	Edge(int id, char identity_password);
	~Edge();
	int getId() const;
	virtual Edge* clone() const = 0;
	/*
	virtual bool matchWith(StraightEdge& edge) = 0;
	virtual bool matchWith(FemaleEdge& edge) = 0;
	virtual bool matchWith(MaleEdge& edge) = 0;
	virtual bool matchWith(CompositeEdge& edge) = 0;
	*/
	virtual bool matchWith(Edge& edge);
	virtual bool matchWithHelper(char identity_password) = 0;	// double dispatch-1
	bool matchWithHelper(Edge& edge);							// double dispatch-2
	virtual void breakMatch();
	Edge* getMatchingEdge() const;
};

class StraightEdge : public Edge {

	bool matchWithHelper(char identity_password);

public:
	StraightEdge(int id);
	~StraightEdge();
	Edge* clone() const;
};

class FemaleEdge : public Edge {

	bool matchWithHelper(char identity_password);

public:
	FemaleEdge(int id);
	~FemaleEdge();
	Edge* clone() const;
};

class MaleEdge : public Edge {

	bool matchWithHelper(char identity_password);

public:
	MaleEdge(int id);
	~MaleEdge();
	Edge* clone() const;
};

class CompositeEdge : public Edge {
	vector<Edge*> edges;
	int matchIndex;

	bool matchWithHelper(char identity_password);

public:
	CompositeEdge(int id);
	~CompositeEdge();
	Edge* clone() const;
	bool matchWith(Edge& edge);
	void breakMatch();
	CompositeEdge* addEdge(Edge* edge);
};

