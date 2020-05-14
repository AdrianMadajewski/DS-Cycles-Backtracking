#ifndef LIST_H
#define LIST_H

#include <list>		// for std::list
#include <vector>	// for std::vector
#include <utility>	// for std::pair

class ListGraph {
public:
	ListGraph(int vertices, int edges);
	ListGraph(const std::vector<std::pair<int, int>>& data);
	~ListGraph();
	void addEdge(int first, int second);
	void printSuccList();
	void eulerUtil(int vertex, std::vector<int>& path);
	bool eulerCycle();
	bool hasEulerianCircuit();
private:
	int V;					// No. of vertices
	int E;					// No. of edges
	std::list<int>* succ;	// Succesors list of each vertex
	int* in;				// in-degree of each vertex
	int* out;				// out-degree of each vertex

	void DFS(int vertex, std::vector<bool>& visited);
	bool isConnected();
};

#endif // !LIST_H
