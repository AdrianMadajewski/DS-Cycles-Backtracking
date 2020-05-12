#include <iostream>

#include "Input.h"
#include "Matrix.h"
#include "File.h"

int main()
{
	auto data {loadDataFromFile("data.txt")};
	GraphAdjacencyMatrix graph(data);

	graph.printMatrix();
	graph.hamiltonCycle();
	graph.eulerCycle();

	return 0;
}