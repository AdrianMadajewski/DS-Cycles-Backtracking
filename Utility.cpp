#include "Utility.h"

void printPathHamilton(std::vector<int>& path) {
	std::cout << "Hamiltonian circuit: ";
	for (const auto& vertex : path) {
		std::cout << vertex + 1 << " -> ";
	}
	std::cout << path.front() + 1 << '\n';
}

void printPathEuler(std::vector<int>& path) {
	std::string printedArrow = " -> ";
	const int size = path.size();
	for (int i = 0; i < size - 1; ++i) {
		if (i == size - 2) {
			printedArrow = "";
		}
		std::cout << path.at(size - i - 1) + 1 << "--" << path.at(size - i - 2) + 1 << printedArrow;
	}
	std::cout << '\n';
}

