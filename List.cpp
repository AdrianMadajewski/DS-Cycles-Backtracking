#include "List.h"
#include "Utility.h"

#include <iostream>		// for std::cout


ListGraph::ListGraph(int vertices, int edges) {
	V = vertices;
	E = edges;
	succ = new std::list<int>[V];
	in = new int[V]{};
	out = new int[V]{};
}

ListGraph::ListGraph(const std::vector<std::pair<int, int>>& data) {
	V = data[0].first;
	E = data[0].second;
	succ = new std::list<int>[V];
	in = new int[V]{};
	out = new int[V]{};
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

bool ListGraph::hamiltonUtil(std::vector<int>& path, int position) {
	int connection = path[position - 1];

	// If all vertices are included in the path
	if (position == V) {
		// Check if there exist a connection from the last
		// vertex inside the path to the first vertex (path[0])
		auto found = std::find(succ[connection].begin(), 
			succ[connection].end(), path[0]);

		if (found != succ[connection].end()) {
			return true;
		}
		else {
			return false;
		}
	}

	// For each vertex check if it can be added
	std::list<int>::iterator it;
	for (it = succ[connection].begin(); it != succ[connection].end(); ++it) {
		if (canBeAdded(*it, path, position)) {
			path[position] = *it;

			// Recur to construct the rest of the path
			if (hamiltonUtil(path, position + 1)) {
				return true;
			}

			// If added vertex does not lead to a solution - remove it
			path[position] = -1;
		}
	}

	// If no vertex can be added to 'path'
	return false;
}

// Utility function to check if the 'vertex'
// can be added at index 'position' in the 'path'
bool ListGraph::canBeAdded(int vertex, std::vector<int>& path, int position) {
	
	int connection = path[position - 1];

	// Check if the 'vertex' has connection to 
	// the previous one from the 'path'
	auto found = std::find(succ[connection].begin(), 
				succ[connection].end(), 
				vertex);

	if (found == succ[connection].end()) {
		return false;
	}

	// Check if the 'vertex' has already 
	// been included in the 'path'
	for (int i = 0; i < position; ++i) {
		if (path[i] == vertex) {
			return false;
		}
	}

	// If the 'vertex' can be added at 'position'
	return true;
}

bool ListGraph::hamiltonCycle() {
	std::vector<int> path(V, -1);
	// Mark path[0] with starting vertex 0
	path[0] = 0;
	// Traverse the graph with first empty position set to 1
	if (!hamiltonUtil(path, 1)) {
		std::cout << "Cannot find Hamiltonian circuit." << '\n';
		return false;
	}

	printPathHamilton(path);
	return true;
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
		auto connected = std::find(visited.begin(), visited.end(), false);
		if (connected != visited.end()) {
			return false;
		}
	}

	return true;
}

void ListGraph::eulerUtil(int vertex, std::vector<int>& path) {
	while (!succ[vertex].empty()) {
		int current = succ[vertex].front();
		// Remove connection from 'vertex'
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
	//if (!isConnected()) {
	//	return false;
	//}
		
	// Has Eulerian circuit if all vertices has the same in/out degree
	for (int vertex = 0; vertex < V; ++vertex) {
		if (out[vertex] != in[vertex]) {
			return false;
		}
	}
	
	return true;
}