#include "Matrix.h"

#include <iostream>

GraphAdjacencyMatrix::GraphAdjacencyMatrix(int vertices, int edges) {
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
}

GraphAdjacencyMatrix::GraphAdjacencyMatrix(std::vector<std::pair<int, int>>& data) {
	V = data[0].first;
	E = data[0].second;

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

GraphAdjacencyMatrix::~GraphAdjacencyMatrix() {
	for (size_t i{ 0 }; i < V; ++i) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

void GraphAdjacencyMatrix::addEdge(int first, int second) {
	matrix[first - 1][second - 1] = 1;
	matrix[second - 1][first - 1] = 1;
}

void GraphAdjacencyMatrix::printMatrix() {
	std::cout << "Printing 2D representation of a graph's adjacency matrix: " << '\n';
	std::cout << '\n';
	for (size_t row = 0; row < V; ++row) {
		for (size_t col = 0; col < V; ++col) {
			std::cout << matrix[row][col] << ' ';
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

bool GraphAdjacencyMatrix::hamiltonCycle() {
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

// Utility function to check if the 'vertex' can be added at index 'position' (1 to V)
bool GraphAdjacencyMatrix::canBeAdded(int vertex, std::vector<int> &path, int position) {
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

	return true;
}

bool GraphAdjacencyMatrix::hamiltonUtil(std::vector<int> &path, int position) {
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

	// For each vertices check if it can be added
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

// Utility function to print Hamiltonian path
void GraphAdjacencyMatrix::printPathHamilton(std::vector<int> &path) {
	for (const auto& vertex : path) {
		std::cout << vertex + 1 << " -> ";
	}
	std::cout << path.front() + 1 << '\n';
}

// Utility function to print Euler path
// Template is as follows
// i--j -> j--x -> x--i
void GraphAdjacencyMatrix::printPathEuler(std::vector<int>& path) {
	std::string printedArrow = " -> ";
	for (int i = 0; i < path.size() - 1; ++i) {
		if (i == path.size() - 2) {
			printedArrow = "";
		}
		std::cout << path.at(i) + 1 << "--" << path.at(i + 1) + 1 << printedArrow;
	}
	std::cout << '\n';
}

// Utility function to traverse the graph using DFS method
void GraphAdjacencyMatrix::eulerUtil(int current, std::vector<int>& path) {
	// For each vertex check it's connection and then remove them
	for (int vertex = 0; vertex < V; ++vertex) {
		if (matrix[current][vertex] == 1) {
			matrix[current][vertex] -= 1;
			matrix[vertex][current] -= 1;
			eulerUtil(vertex, path);
		}
	}
	// Emplace current path
	path.emplace_back(current);
}

void GraphAdjacencyMatrix::DFS(int vertex, std::vector<bool>& visited) {
	visited[vertex] = true;
	for (int current = 0; current < V; ++current) {
		if (visited[current] == false && matrix[current][vertex] == 1) {
			DFS(current, visited);
		}
	}
}

// Function to check the conectivity whether a graph
// is connected or not - using DFS algoirithm
bool GraphAdjacencyMatrix::isConnected() {
	std::vector<bool> visited(V, false);
	DFS(0, visited);

	return V == visited.size();
}

GraphType GraphAdjacencyMatrix::checkGraphType() {
	// Check if the graph is connected
	if (!isConnected()) {
		return NOT_EULER;
	}

	// Count vertices with odd degree
	int odd_count = 0;
	for (int row = 0; row < V; ++row) {
		int row_sum = matrix[row][0];
		for (int col = 1; col < V; ++col) {
			row_sum += matrix[row][col];
		}
		if (row_sum & 1) {
			odd_count++;
		}
	}

	// If odd_count is more than 2 then graph is not Eulerian
	if (odd_count > 2) {
		return NOT_EULER;
	}

	// Return SEMI_EULER if has exactly 2 odd degree vertices
	// Return FULL_EULER if has all of the vertices degrees are even
	return (odd_count) ? SEMI_EULER : FULL_EULER;
}

bool GraphAdjacencyMatrix::eulerCycle() {
	if (checkGraphType() == FULL_EULER) {
		std::vector<int> path;
		eulerUtil(0, path);
		printPathEuler(path);
		return true;
	}
	else {
		std::cout << "Cannot find Eulerian circuit." << '\n';
		return false;
	}
}
