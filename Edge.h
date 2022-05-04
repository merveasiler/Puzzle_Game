#pragma once

#include <string>
#include <vector>

using namespace std;

class Edge {

protected:
	char identity;
	Edge* matchingEdge;

public:
	Edge(char identity);
	~Edge();
	virtual bool matchWith(char code) = 0;
	virtual bool matchWith(Edge& edge);
	virtual void breakMatch();
};

class StraightEdge : public Edge {

protected:
	bool matchWith(char code);

public:
	StraightEdge();
	~StraightEdge();
};

class FemaleEdge : public Edge {

protected:
	bool matchWith(char code);

public:
	FemaleEdge();
	~FemaleEdge();
};

class MaleEdge : public Edge {

protected:
	bool matchWith(char code);

public:
	MaleEdge();
	~MaleEdge();
};

class CompositeEdge : public Edge {
	vector<Edge*> edges;
	unsigned int matchIndex;

protected:
	bool matchWith(char code);

public:
	CompositeEdge();
	~CompositeEdge();
	bool matchWith(Edge& edge);
	void breakMatch();
	CompositeEdge* addEdge(Edge* edge);
};

