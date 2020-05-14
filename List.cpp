#include "List.h"
#include "Utility.h"

#include <iostream>		// for std::cout


ListGraph::ListGraph(int vertices, int edges) {
	V = vertices;
	E = edges;
	succ = new std::list<int>[V];
	in = new int[V];
	out = new int[V];
}

ListGraph::ListGraph(const std::vector<std::pair<int, int>>& data) {
	V = data[0].first;
	E = data[0].second;
	succ = new std::list<int>[V];
	in = new int[V];
	out = new int[V];
	for (int i = 1; i <= E; ++i) {
		addEdge(data[i].first, data[i].second);
	}
}

ListGraph::~ListGraph() {
	delete[] succ;
	delete[] in;
	delete[] out;
}

void ListGraph::addEdge(int first, int second) {
	succ[first - 1].emplace_back(second - 1);
	in[second - 1]++;
	out[first - 1]++;
}

void ListGraph::printSuccList() {
	std::cout << "Printing representation of directed graph's succesors list: " << '\n';
	std::cout << '\n';
	for (int vertex = 0; vertex < V; ++vertex) {
		std::cout << vertex + 1 << ": ";
		for (const auto& suc : succ[vertex]) {
			std::cout << suc + 1 << ' ';
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

void ListGraph::DFS(int vertex, std::vector<bool>& visited) {
	visited[vertex] = true;
	std::list<int>::iterator it;
	for (it = succ[vertex].begin(); it != succ[vertex].end(); ++it) {
		if (!visited[*it]) {
			DFS(*it, visited);
		}
	}
}

// Function to check the conectivity whether a graph
// is connected or not - using DFS algoirithm
bool ListGraph::isConnected() {
	for (int vertex = 0; vertex < V; ++vertex) {
		std::vector<bool> visited(V, false);
		DFS(vertex, visited);
		if (std::find(visited.begin(), visited.end(), false) != visited.end()) {
			return false;
		}
	}
	return true;
}

void ListGraph::eulerUtil(int vertex, std::vector<int>& path) {
	while (!succ[vertex].empty()) {
		int current = succ[vertex].front();
		// Remove connection if hasnt been visisted
		succ[vertex].pop_front();
		eulerUtil(current, path);
	}
	path.emplace_back(vertex);
}

bool ListGraph::eulerCycle() {
	if (hasEulerianCircuit()) {
		std::vector<int> path;
		eulerUtil(0, path);
		std::cout << "Eulerian circuit: ";
		printPathEuler(path);
		return true;
	}
	std::cout << "Cannot find Eulerian circuit." << '\n';
	return false;
}

bool ListGraph::hasEulerianCircuit() {
	int startNodes = 0;
	int endNodes = 0;

	if (!isConnected()) 
		return false;

	for (int vertex = 0; vertex < V; ++vertex) {
		if (out[vertex] - in[vertex] > 1 || in[vertex] - out[vertex] > 1) return false;
		else if (out[vertex] - in[vertex] == 1) startNodes++;
		else if (in[vertex] - out[vertex] == 1) endNodes++;
	}
	// Has Eulerian circuit (not path) if all vertices has the same in/out degree
	return (endNodes == 0 && startNodes == 0);
}