#include <iostream>
#include <fstream>

size_t countOccurences(char ch, std::ifstream& inFile)
{
	size_t count = 0;
	while (true)
	{
		char curr = inFile.get();
		if (!inFile.eof())
		{
			break;
		}

		if (curr == ch)
		{
			count++;
		}
	}

	inFile.close();
	return count;
}

size_t countOccurences(char ch, const char* fileName)
{
	if (!fileName)
	{
		return 0;
	}

	std::ifstream inFile(fileName);
	if (!inFile.is_open())
	{
		return 0;
	}

	return countOccurences(ch, inFile);
}

int main() {

	std::ofstream outFile("text.txt");
	outFile << "fkaskxekxa" << std::endl << "daseqwa";
	outFile.close();

	char lookFor = 'a';
	const char* fileName = "text.txt";

	std::cout << countOccurences(lookFor, fileName);

	return 0;
}