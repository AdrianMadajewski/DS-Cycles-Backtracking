#include <iostream>

#include "Input.h"
#include "Matrix.h"
#include "File.h"
#include "List.h"

int main()
{
	if (askUser("Enter user data ? : 1 = yes, 0 = no")) {
		const auto data = getUserPairs();

		MatrixGraph matrix(data);
		ListGraph list(data);

		matrix.printMatrix();
		matrix.hamiltonCycle();
		matrix.eulerCycle();

		list.printSuccList();
		list.hamiltonCycle();
		list.eulerCycle();
	}

	if (askUser("Enter file data? : 1 = yes, 0 = no")) {
		std::string filename;
		std::cout << "Enter a filename: ";
		std::cin >> filename;

		// Clear console buffer
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		const auto fileData = loadDataFromFile(filename);

		MatrixGraph matrix(fileData);
		ListGraph list(fileData);

		matrix.printMatrix();
		matrix.hamiltonCycle();
		matrix.eulerCycle();

		list.printSuccList();
		list.hamiltonCycle();
		list.eulerCycle();
	}
	
	return 0;
}