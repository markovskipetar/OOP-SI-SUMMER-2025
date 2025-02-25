#include <iostream>
#include <fstream>

int sumOf(int x, int y, int z)
{
	return x + y + z;
}

int mulOf(int x, int y, int z)
{
	return x * y * z;
}

void saveResults(std::ofstream& outFile, int sum, int mul)
{
	outFile << sum << " " << mul << std::endl;
}

void saveResults(const char* fileName, int sum, int mul)
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

	saveResults(outFile, sum, mul);
	outFile.close();
}

void readResults(std::ifstream& inFile, int& sum, int& mul)
{
	inFile >> sum >> mul;
}

void readResults(const char* fileName, int& sum, int& mul)
{
	if (!fileName)
	{
		return;
	}

	std::ifstream inFile(fileName);
	if (!inFile.is_open())
	{
		return;
	}

	readResults(inFile, sum, mul);
	inFile.close();
}

int main()
{

	int x, y, z;
	std::cin >> x >> y >> z;

	const char* fileName = "result.txt";
	int sum = sumOf(x, y, z);
	int mul = mulOf(x, y, z);
	saveResults(fileName, sum, mul);

	int sumInFile = 0;
	int mulInFile = 1;
	readResults(fileName, sumInFile, mulInFile);

	std::cout << sumInFile - mulInFile << std::endl;


	return 0;
}