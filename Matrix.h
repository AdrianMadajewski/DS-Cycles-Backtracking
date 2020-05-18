#ifndef MATRIX_H
#define MATRIX_H

#include <vector>	// for std::vector
#include <utility>	// for std::pair
#include <stack>	// for std::stack

class MatrixGraph {
public:
	MatrixGraph(int vertices, int edges);
	MatrixGraph(const std::vector<std::pair<int, int>>& data);
	~MatrixGraph();
	void addEdge(int first, int second);
	void printMatrix();
	bool hamiltonCycle();
	bool eulerCycle();
private:
	int V;			// No. of vertices
	int E;			// No. of edges
	int** matrix;	// 2D-array to store connections
	int* degree;	// Array to store degree of each vertex

	// Hamilton
	bool canBeAdded(int vertex, std::vector<int>& path, int position);
	bool hamiltonUtil(std::vector<int> &path, int position);
	
	// Euler
	void eulerUtil(int vertex, std::vector<int>& path);
	bool isEulerian();
	bool isConnected();
	void DFS(int vertex, std::vector<bool> &visited);
};

#endif // !MATRIX_H
