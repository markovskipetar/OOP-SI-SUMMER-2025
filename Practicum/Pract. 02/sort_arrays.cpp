#include <iostream>
#include <fstream>

void readArray(std::ifstream& inFile, int*& arr, size_t& size)
{
	inFile >> size;
	arr = new int[size] {};

	for (int i = 0; i < size; i++)
	{
		inFile >> arr[i];
	}

	inFile.close();
}

void readArray(const char* inputFileName, int*& arr, size_t& size)
{
	if (!inputFileName)
	{
		return;
	}

	std::ifstream inFile(inputFileName);
	if (!inFile.is_open())
	{
		return;
	}

	readArray(inFile, arr, size);
}

bool ascOrder(int a, int b)
{
	return a > b;
}

bool descOrder(int a, int b)
{
	return a < b;
}

void saveArrToFile(std::ofstream& outFile, const int* arr, size_t size)
{
	outFile << size << std::endl;
	for (size_t i = 0; i < size; i++)
	{
		outFile << arr[i];

		if (i != size - 1)
		{
			outFile << " ";
		}
	}
}

void sortByCriteria(std::ofstream& outFile, int* arr, size_t size, bool(*criteria)(int, int))
{
	for (size_t i = 0; i < size - 1; i++)
	{
		size_t minIndex = i;
		for (size_t j = i + 1; j < size; j++)
		{
			if (criteria(arr[minIndex], arr[j]))
			{
				minIndex = j;
			}
		}

		if (minIndex != i)
		{
			std::swap(arr[i], arr[minIndex]);
		}
	}

	saveArrToFile(outFile, arr, size);
}

void sortByCriteria(const char* fileName, int* arr, size_t size, bool(*predicate)(int, int))
{
	if (!fileName)
	{
		return;
	}

	std::ofstream outFile(fileName);
	if (!outFile.is_open())
	{
		return;
	}

	sortByCriteria(outFile, arr, size, predicate);
	outFile.close();
}

void freeArr(int*& arr, size_t& size)
{
	delete[] arr;
	arr = nullptr;

	size = 0;
}
int main()
{
	const char* inputFileName = "input.txt";
	std::ofstream outFile(inputFileName);
	outFile << 5 << std::endl;
	outFile << 1 << " " << 6 << " " << 2 << " " << 3 << " " << 9 << std::endl;
	outFile.close();

	size_t size = 0;
	int* arr = nullptr;
	readArray(inputFileName, arr, size);

	const char* ascFileName = "ascending.txt";
	sortByCriteria(ascFileName, arr, size, ascOrder);

	const char* descFileName = "descending.txt";
	sortByCriteria(descFileName, arr, size, descOrder);

	freeArr(arr, size);

	return 0;
}