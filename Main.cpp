#include <iostream>

#include "Input.h"
#include "Matrix.h"
#include "File.h"
#include "List.h"

int main()
{
	auto data { loadDataFromFile("data4.txt") };
	MatrixGraph m(data);
	ListGraph l(data);

	m.printMatrix();
	m.hamiltonCycle();
	m.eulerCycle();

	l.printSuccList();
	l.eulerCycle();

	return 0;
}