#include <iostream>

#include "Input.h"
#include "Matrix.h"
#include "File.h"
#include "List.h"

int main()
{
	if (askUser("Enter user data ? : 1 = yes, 0 = no")) {
		const auto data = getUserPairs();

		MatrixGraph m(data);
		ListGraph l(data);

		m.printMatrix();
		m.eulerCycle();
		m.hamiltonCycle();

		l.printSuccList();
		l.eulerCycle();
		l.hamiltonCycle();
	}

	if (askUser("Enter file data? : 1 = yes, 0 = no")) {
		std::string filename;
		std::cout << "Enter a filename: ";
		std::cin >> filename;

		// Clear console buffer
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		const auto fileData = loadDataFromFile(filename);

		MatrixGraph m(fileData);
		ListGraph l(fileData);

		m.printMatrix();
		m.eulerCycle();
		m.hamiltonCycle();

		l.printSuccList();
		l.eulerCycle();
		l.hamiltonCycle();
	}
	
	return 0;
}