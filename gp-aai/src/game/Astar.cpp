#include "Astar.h"
#include <limits>
#include <iostream>
#include <algorithm>

using std::cout, std::endl, std::numeric_limits, std::reverse;

Vertex::Vertex(Vector2D position, double heuristic) : position(position), heuristic(heuristic), distance(numeric_limits<double>::max() - 1000), visited(false), from(nullptr) {}

void Vertex::addEdge(Edge edge) {
	this->edges.push_back(edge);
}

Vector2D Vertex::getPosition() {
	return this->position;
}

vector<Edge> Vertex::getNeighbours() {
	return this->edges;
}

double Vertex::getHeuristic() {
	return this->heuristic;
}

bool Vertex::isVisited() {
	return this->visited;
}

void Vertex::setVisited(bool v) {
	this->visited = v;
}

Vertex* Vertex::getFrom() {
	return this->from;
}

void Vertex::setFrom(Vertex* v) {
	this->from = v;
}

double Vertex::getDistance() {
	return this->distance;
}

void Vertex::setDistance(double d) {
	this->distance = d;
}

void Vertex::print() {
	cout << "Vertex at " << this->position << " with " << this->edges.size() << " neighbours:" << endl;
	for(auto e : this->edges) {
		cout << "- Neighbour with weight " << e.weight << " at " << e.toVertex.getPosition() << endl;
	}
}

Graph::Graph() {}

void Graph::addVertex(Vertex* vertex) {
	this->vertices.push_back(vertex);
}

Vertex* Graph::findClosest(Vector2D pos) {
	Vertex* closest = nullptr;
	double distance = numeric_limits<double>::max();

	for(Vertex* v : this->vertices) {
		double d = (pos - v->getPosition()).length();

		if(d < distance) {
			closest = v;
			distance = d;
		}
	}

	return closest;
}

vector<Vector2D> Graph::shortestPathPoints(Vector2D from, Vector2D to) {
	Vertex* v_from = this->findClosest(from);
	Vertex* v_to = this->findClosest(to);

	vector<Vertex*> v_path = this->shortestPath(v_from, v_to);
	vector<Vector2D> a_path;
	for(Vertex* v : v_path)
		a_path.push_back(v->getPosition());

	return a_path;
}

vector<Vertex*> Graph::shortestPath(Vertex* from, Vertex* to) {
	Vertex* current_vertex = from;
	current_vertex->setDistance(0);

	while(current_vertex != to) {
		current_vertex->setVisited(true);

		// 1. Expand outwards
		for(auto edge : current_vertex->getNeighbours()) {
			double distance = current_vertex->getDistance() + edge.weight;
			if(edge.toVertex.getDistance() > distance) {
				edge.toVertex.setDistance(distance);
				edge.toVertex.setFrom(current_vertex);
			}
		}

		// 2. Find the vertex with the smallest value
		Vertex* smallest = nullptr;
		double smallest_value = numeric_limits<double>::max();
		for(auto vertex : this->vertices) {
			if(vertex->isVisited()) continue;

			double value = vertex->getDistance() + vertex->getHeuristic();
			if(value < smallest_value) {
				smallest_value = value;
				smallest = vertex;
			}
		}

		current_vertex = smallest;
	}

	vector<Vertex*> shortest_path;
	while(current_vertex != from) {
		shortest_path.push_back(current_vertex);
		current_vertex = current_vertex->getFrom();
	}
	shortest_path.push_back(from);
	reverse(shortest_path.begin(), shortest_path.end());
	return shortest_path;
}
