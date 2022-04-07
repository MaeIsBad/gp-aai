#pragma once

#include <vector>
#include "../util/Vector2D.h"

using std::vector;

class Vertex;

struct Edge {
	Vertex& toVertex;
	int weight;
};

class Vertex {
	private:
		vector<Edge*> edges;
		Vector2D position;
};

class Graph {
	private:
		vector<Vertex*> vertices;

	public:
		Vertex& findClosest(Vector2D pos);
		vector<Vector2D> shortestPath(Vector2D from, Vector2D to);
		vector<Vertex*> shortestPath(Vertex* from, Vertex* to);
};

