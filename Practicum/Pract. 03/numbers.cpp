#include <iostream>
#include <sstream>

namespace CONSTANTS
{
	constexpr size_t BUFFER_MAX_SIZE = 1024;
}

int getSizeOfNumArr(const char* buff)
{
	if (!buff)
	{
		return -1;
	}
	
	std::stringstream ss(buff);
	int size = 0;

	while (!ss.eof())
	{
		int temp = 0;
		ss >> temp;
		size++;
	}

	return size;
}

void initArr(int* numbers, int numbersSize, const char* buff)
{
	std::stringstream ss(buff);

	size_t at = 0;
	while(!ss.eof())
	{
		ss >> numbers[at++];
	}
}

int* readArr(const char* buff)
{
	if (!buff)
	{
		return nullptr;
	}

	int numbersSize = getSizeOfNumArr(buff);
	if (numbersSize == -1)
	{
		return nullptr;
	}

	int* numbers = new int[numbersSize];
	initArr(numbers, numbersSize, buff);
	return numbers;
}

int getSumOfArr(const int* numbers, int size)
{
	if (!numbers || size == 0)
	{
		std::cerr << "error";
		return -1;
	}

	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += numbers[i];
	}

	return sum;
}

double getAvgOfArr(const int* numbers, int size)
{
	if (!numbers || size == 0)
	{
		std::cerr << "error";
		return -1;
	}

	return (double) getSumOfArr(numbers, size) / size;
}

int getMaxOfArr(const int* numbers, int size)
{
	if (!numbers || size == 0)
	{
		std::cerr << "error";
		return -1;
	}

	int maxNum = numbers[0];
	for (int i = 1; i < size; i++)
	{
		if (maxNum < numbers[i])
		{
			maxNum = numbers[i];
		}
	}

	return maxNum;
}

int getMinOfArr(const int* numbers, int size)
{
	if (!numbers || size == 0)
	{
		std::cerr << "error";
		return -1;
	}

	int minNum = numbers[0];
	for (int i = 1; i < size; i++)
	{
		if (minNum > numbers[i])
		{
			minNum = numbers[i];
		}
	}

	return minNum;
}

void freeArr(int*& numbers, int& size)
{
	delete[] numbers;
	numbers = nullptr;

	size = 0;
}

int main()
{
	char buff[CONSTANTS::BUFFER_MAX_SIZE]{};
	std::cin.getline(buff, CONSTANTS::BUFFER_MAX_SIZE);

	int size = getSizeOfNumArr(buff);
	//if (size == -1)
	//{
	//	return -1;
	//}

	int* numbers = readArr(buff);
	std::cout << getSumOfArr(numbers, size) << std::endl;
	std::cout << getAvgOfArr(numbers, size) << std::endl;
	std::cout << getMaxOfArr(numbers, size) << std::endl;
	std::cout << getMinOfArr(numbers, size) << std::endl;

	freeArr(numbers, size);
}