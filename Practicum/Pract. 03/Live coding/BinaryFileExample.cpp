#include <iostream>
#include <fstream>

namespace GLOBAL_CONSTANTS {
	constexpr int MAX_LEN = 20;
	const char* FILE_NAME = "person.dat";
}

struct Person {
	char name[GLOBAL_CONSTANTS::MAX_LEN];
	int age;
};

void savePersonArrayToFile(const char* fileName, const Person* arr, int size) {
	std::ofstream ofs(fileName, std::ios::binary);

	if (!ofs.is_open()) {
		return;
	}

	ofs.write((const char*)arr, size * sizeof(Person));

	ofs.close();
}

int getFileSize(std::ifstream& ifs) {
	int currPos = ifs.tellg();
	ifs.seekg(0, std::ios::end);
	int res = ifs.tellg();
	ifs.seekg(currPos, std::ios::beg);
	return res;
}

Person* readPersonArrayFromFile(const char* fileName, int& size) {
	std::ifstream ifs(fileName, std::ios::binary);

	if (!ifs.is_open()) {
		return nullptr;
	}

	int count = getFileSize(ifs);
	size = count / sizeof(Person);

	Person* res = new Person[size];

	ifs.read((char*)res, size * sizeof(Person));

	ifs.close();

	return res;
}

int main() {
	Person arr[] = { {"Boris", 20}, {"Momchil", 10} };
	int size = 2;

	savePersonArrayToFile(GLOBAL_CONSTANTS::FILE_NAME, arr, size);

	Person* res = readPersonArrayFromFile(GLOBAL_CONSTANTS::FILE_NAME, size);

	for (int i = 0; i < size; i++) {
		std::cout << res[i].name << " " << res[i].age << std::endl;
	}

	delete[] res;
}