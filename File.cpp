#include "File.h"

#include <fstream>	// for std::ifstream
#include <iostream>	

std::vector<std::pair<int, int>> loadDataFromFile(const std::string& filename) {
	if (filename.empty()) {
		std::cerr << "Empty filename - quiting." << '\n';
		std::cin.get();
		exit(1);
	}

	std::vector<std::pair<int, int>> data;
	std::ifstream file;
	file.open(filename);

	if (!file.is_open()) {
		std::cerr << "Couldn't find the file. Please restart." << '\n';
		std::cin.get();
		exit(1);
	}
	else {
		std::cout << "Succesfully read from file " << filename << '\n';
		
		while (!file.eof()) {
			int first{};
			int second{};
			file >> first >> second;
			data.emplace_back(std::make_pair(first, second));
		}
	}
	file.close();
	return data;
}
