#include "Matrix.h"
#include "Utility.h"

#include <iostream>

MatrixGraph::MatrixGraph(int vertices, int edges) {
	V = vertices;
	E = edges;

	// Allocate memory and make each M[i, j] = 0
	matrix = new int* [V];
	for (size_t row{ 0 }; row < V; ++row) {
		matrix[row] = new int[V];
		for (size_t col{ 0 }; col < V; ++col) {
			matrix[row][col] = 0;
		}
	}

	// Allocate memory for each vertex degree
	degree = new int[V]{};
}

MatrixGraph::MatrixGraph(const std::vector<std::pair<int, int>>& data) {
	V = data[0].first;
	E = data[0].second;

	// Allocate memory for each vertex degree
	degree = new int[V]{};

	// Allocate memory and make each M[i, j] = 0
	matrix = new int* [V];
	for (size_t row{ 0 }; row < V; ++row) {
		matrix[row] = new int[V];
		for (size_t col{ 0 }; col < V; ++col) {
			matrix[row][col] = 0;
		}
	}

	// Add all the edges
	for (size_t i = 1; i <= E; ++i) {
		addEdge(data[i].first, data[i].second);
	}
}

MatrixGraph::~MatrixGraph() {
	for (size_t i{ 0 }; i < V; ++i) {
		delete[] matrix[i];
	}
	delete[] matrix;
	delete[] degree;
}

void MatrixGraph::addEdge(int first, int second) {
	matrix[first - 1][second - 1] = 1;
	matrix[second - 1][first - 1] = 1;
	degree[first - 1]++;
	degree[second - 1]++;
}

void MatrixGraph::printMatrix() {
	std::cout << "Printing 2D representation of undirected graph's adjacency matrix: " << '\n';
	std::cout << '\n';
	for (size_t row = 0; row < V; ++row) {
		for (size_t col = 0; col < V; ++col) {
			std::cout << matrix[row][col] << ' ';
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

// Utility function to check if the 'vertex' can be added at index 'position' in the 'path'
bool MatrixGraph::canBeAdded(int vertex, std::vector<int> &path, int position) {
	// Check if the vertex is adjacent
	// to the previous one from the 'path'
	if (matrix[path[position - 1]][vertex] == 0) {
		return false;
	}
	// Check if the vertex has already 
	// been included in the 'path'
	for (int i = 0; i < position; ++i) {
		if (path[i] == vertex) {
			return false;
		}
	}
	// If the 'vertex' can be added at 'position'
	return true;
}

bool MatrixGraph::hamiltonUtil(std::vector<int> &path, int position) {
	// If all vertices are included in the path
	if (position == V) {
		// Check if there exists an edge from the last 
		// vertex inside the path to the first vertex
		if (matrix[path[position - 1]][path[0]] == 1) {
			return true;
		}
		else {
			return false;
		}
	}

	// For each vertex check if it can be added
	// Starting from 1, beucase 0 was set as a starting point
	for (int vertex = 1; vertex < V; ++vertex) {
		if (canBeAdded(vertex, path, position)) {
			path[position] = vertex;

			// Recur to construct the rest of the path
			if (hamiltonUtil(path, position + 1)) {
				return true;
			}
			// If the added vertex does not help with finding the solution remove it
			path[position] = -1;
		}
	}

	// If no vertex can be added to 'path' return false
	return false;
}

bool MatrixGraph::hamiltonCycle() {
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

// Utility function to traverse the graph using DFS post-order method
void MatrixGraph::eulerUtil(int vertex, std::vector<int>& path) {
	// For each vertex check it's connection and then remove them
	for (int current = 0; current < V; ++current) {
		if (matrix[vertex][current] == 1) {
			// Remove connections
			matrix[vertex][current]--;
			matrix[current][vertex]--;
			eulerUtil(current, path);
		}
	}
	// Emplace vertex in the path
	path.emplace_back(vertex);
}

void MatrixGraph::DFS(int vertex, std::vector<bool>& visited) {
	visited[vertex] = true;
	for (int current = 0; current < V; ++current) {
		if (!visited[current] && matrix[vertex][current] == 1) {
			DFS(current, visited);
		}
	}
}

// Function to check the conectivity whether a graph
// is connected or not - using DFS algoirithm
bool MatrixGraph::isConnected() {
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

bool MatrixGraph::isEulerian() {
	// Check if the graph is connected
	if (!isConnected()) {
		return false;
	}
	// Undirected graph has Eulerian circuit only if
	// all the vertices have even degree
	for (int vertex = 0; vertex < V; ++vertex) {
		if (degree[vertex] & 1) {
			return false;
		}
	}
	return true;
}

bool MatrixGraph::eulerCycle() {
	if (isEulerian()) {
		std::vector<int> path;
		eulerUtil(0, path);
		std::cout << "Eulerian circuit: ";
		printPathEuler(path);
		return true;
	}
	else {
		std::cout << "Cannot find Eulerian circuit." << '\n';
		return false;
	}
}
