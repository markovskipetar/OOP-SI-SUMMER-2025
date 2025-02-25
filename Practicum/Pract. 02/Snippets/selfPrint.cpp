#include <iostream>
#include <fstream>

constexpr int BUFFER_SIZE = 1024;

void selfPrint(const char* fileName) {
	std::ifstream ifs(fileName);
	if (!ifs.is_open()) {
		return;
	}

	char buffer[BUFFER_SIZE];

	while (!ifs.eof()) {
		ifs.getline(buffer, BUFFER_SIZE);
		std::cout << buffer << std::endl;
	}

	ifs.close();
}

int main()
{
	selfPrint("self.cpp");
}