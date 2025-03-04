#include <iostream>
#include <fstream>

namespace Constants {
	const size_t START_POS = 0;
}

bool isDigit(char c) {
	return c >= '0' && c <= '9';
}

bool isWhiteSpace(char c) {
	return c == ' ' || c == '\n' || c == '\t';
}

size_t getArraySizeFromFile(std::ifstream& ifs) {
	size_t size = 0;
	bool inNumber = false;

	while (true) {
		if (ifs.eof()) {
			break;
		}
		char symbol = ifs.get();
		if ((isDigit(symbol) || symbol == '-') && !inNumber) {
			size++;
			inNumber = true;
		}
		else if (isWhiteSpace(symbol)) {
			inNumber = false;
		}
	}

	ifs.clear();
	ifs.seekg(Constants::START_POS, std::ios::beg);

	return size;
}

int* readArrayFromFile(const char* fileName, size_t& size) {
	std::ifstream ifs(fileName);

	if (!ifs.is_open()) {
		std::cout << "File not found" << std::endl;
		return nullptr;
	}

	size = getArraySizeFromFile(ifs);

	if (size == 0) {
		ifs.close();
		return nullptr;
	}

	int* array = new int[size];

	for (size_t i = 0; i < size; i++) {
		ifs >> array[i];
	}

	ifs.close();

	return array;
}

void selectionSort(int*& array, size_t size, bool(*predicate)(int, int)) {
	for (size_t i = 0; i < size - 1; i++) {
		int minIndex = i;
		for (size_t j = i + 1; j < size; j++) {
			if (predicate(array[j], array[minIndex])) {
				minIndex = j;
			}
		}
		if (minIndex != i) {
			std::swap(array[i], array[minIndex]);
		}
	}
}

bool ascending(int a, int b) {
	return a < b;
}

bool descending(int a, int b) {
	return a > b;
}

void saveSortedArrayToFile(const char* filename, size_t size, const int* array) {
	std::ofstream ofs(filename);
	if (!ofs.is_open()) {
		std::cout << "Something went wrong!" << std::endl;
		return;
	}

	for (size_t i = 0; i < size; i++) {
		ofs << array[i] << ' ';
	}

	ofs.close();
}

int main() {
	size_t size = 0;
	int* array = readArrayFromFile("File03.txt", size);

	if (array == nullptr) {
		std::cout << "Array is empty" << std::endl;
		return 0;
	}

	selectionSort(array, size, ascending);
	saveSortedArrayToFile("ascending.txt", size, array);

	selectionSort(array, size, descending);
	saveSortedArrayToFile("descending.txt", size, array);

	delete[] array;

	//In order to work properly, you need to create a file named "File03.txt" in the same directory as the .cpp file
	//Tested with the following content: 106 -56 2 3 9
}