#include <iostream>
#include <sstream>
#include <fstream>

namespace Constants
{
	constexpr size_t MAX_LEN = 20;
	constexpr size_t BUFFER_SIZE = 1024;
	const char DELIM = '-';
	const char OBJ_DELIM = ' ';
}

struct Person
{
	char name[Constants::MAX_LEN];
	int age;
};

size_t getFileSize(std::stringstream& ifs)
{
	size_t currPos = ifs.tellg();
	ifs.seekg(0, std::ios::end);
	size_t size = ifs.tellg();
	ifs.seekg(currPos, std::ios::beg);
	return size;
}
int countCharOccurs(std::stringstream& ifs, char ch)
{
	int occurs = 0;

	while (true)
	{
		int currCh = ifs.get();

		if (ifs.eof())
		{
			ifs.clear();
			ifs.seekg(0, std::ios::beg);
			return occurs;
		}

		if (currCh == ch)
		{
			occurs++;
		}
	}
}

void readPersonFromSS(Person& person, std::stringstream& ss)
{
	ss.getline(person.name, Constants::MAX_LEN, Constants::DELIM);
	ss >> person.age;
	ss.ignore();
}

void printPerson(const Person& person)
{
	std::cout << person.name << ' ' << person.age << std::endl;
}

void printPersonArr(const Person* arr, size_t arrSize)
{
	for (int i = 0; i < arrSize; i++)
	{
		printPerson(arr[i]);
	}
}

Person* getPersonArrayFromStr(const char* str, size_t& arrSize)
{
	std::stringstream ss(str);

	size_t fileSize = getFileSize(ss);

	if (fileSize == 0)
	{
		return nullptr;
	}

	arrSize = countCharOccurs(ss, Constants::OBJ_DELIM) + 1;
	Person* arr = new Person[arrSize];

	for (int i = 0; i < arrSize; i++)
	{
		readPersonFromSS(arr[i], ss);
	}

	return arr;

}

int main()
{
	char buffer[Constants::BUFFER_SIZE];

	std::cin.getline(buffer, Constants::BUFFER_SIZE);

	size_t arrSize = 0;

	Person* arr = getPersonArrayFromStr(buffer, arrSize);

	printPersonArr(arr, arrSize);

	delete[] arr;
}