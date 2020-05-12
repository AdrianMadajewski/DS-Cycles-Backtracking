#ifndef MATRIX_H
#define MATRIX_H

#include <vector>	// for std::vector
#include <utility>	// for std::pair

enum GraphType {
	NOT_EULER,
	SEMI_EULER,
	FULL_EULER,
};

class GraphAdjacencyMatrix {
public:
	GraphAdjacencyMatrix(int vertices, int edges);
	GraphAdjacencyMatrix(std::vector<std::pair<int, int>>& data);
	~GraphAdjacencyMatrix();
	void addEdge(int first, int second);
	void printMatrix();
	bool hamiltonCycle();
	bool eulerCycle();
private:
	size_t V;		// No. of vertices
	size_t E;		// No. of edges
	int** matrix;	// 2D-array to store connections

	// Hamilton
	bool hamiltonUtil(std::vector<int> &path, int position);
	
	// Euler
	bool canBeAdded(int vertex, std::vector<int>& path, int position);
	void eulerUtil(int vertex, std::vector<int>& path);
	GraphType checkGraphType();
	bool isConnected();
	void DFS(int source, std::vector<bool> &visited);

	// Utility
	void printPathHamilton(std::vector<int>& path);
	void printPathEuler(std::vector<int>& path);
};

#endif // !MATRIX_H
