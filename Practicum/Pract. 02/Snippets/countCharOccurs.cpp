#include <iostream>
#include <fstream>

const char* FILE_NAME = "input.txt";

int countCharOccurs(std::ifstream& ifs, char ch)
{
	if (!ifs.is_open())
	{
		return -1;
	}

	int occurs = 0;

	while (true)
	{
		int currCh = ifs.get();

		if (ifs.eof())
		{
			return occurs;
		}

		if (currCh == ch)
		{
			occurs++;
		}
	}
}

int main()
{
	std::ifstream ifs(FILE_NAME);

	char ch = '2';

	std::cout << countCharOccurs(ifs, ch);
}
