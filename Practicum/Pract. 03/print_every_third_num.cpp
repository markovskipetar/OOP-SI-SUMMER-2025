#include <iostream>
#include <fstream>

namespace CONSTANTS
{
	constexpr size_t IGNORE_NUMBERS_SIZE = 2;
}

int* readArr(size_t size)
{
	int* numbers = new int[size];
	for (size_t i = 0; i < size; i++)
	{
		std::cin >> numbers[i];
	}

	return numbers;
}

void saveArrToBinary(std::ofstream& outFile, const int* numbers, size_t size)
{
	outFile.write((const char*)numbers, sizeof(int) * size);
}

void saveArrToBinary(const char* fileName, const int* numbers, size_t size)
{
	if (!fileName || !numbers || size == 0)
	{
		return;
	}

	std::ofstream outFile(fileName, std::ios::binary);
	if (!outFile.is_open())
	{
		return;
	}

	saveArrToBinary(outFile, numbers, size);
	outFile.close();
}

void printEveryThirdNum(std::ifstream& inFile)
{

	int buff[CONSTANTS::IGNORE_NUMBERS_SIZE]{};
	int third = 0;

	while (true)
	{
		inFile.read((char*)buff, sizeof(int) * CONSTANTS::IGNORE_NUMBERS_SIZE);
		inFile.read((char*)&third, sizeof(int));

		if (inFile.eof())
		{
			return;
		}

		std::cout << third << " ";
	}
}

void printEveryThirdNum(const char* fileName)
{
	if (!fileName)
	{
		return;
	}

	std::ifstream inFile(fileName, std::ios::binary);
	if (!inFile.is_open())
	{
		return;
	}

	printEveryThirdNum(inFile);
}

void freeArr(int*& numbers, size_t& size)
{
	delete[] numbers;
	numbers = nullptr;

	size = 0;
}

int main()
{
	size_t size;
	std::cin >> size;

	int* numbers = readArr(size);

	const char* fileName = "numbers.bin";
	saveArrToBinary(fileName, numbers, size);
	printEveryThirdNum(fileName);

	freeArr(numbers, size);
}