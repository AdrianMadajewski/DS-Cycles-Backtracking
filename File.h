#ifndef FILE_H
#define FILE_H

#include <vector>	// for std::vector
#include <utility>	// for std::pair
#include <string>	// for std::string

std::vector<std::pair<int, int>> loadDataFromFile(const std::string& filename);

#endif // !FILE_H
