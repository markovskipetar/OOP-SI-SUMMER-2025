// OOP_D1.cpp 

#include <iostream>
#include <fstream>;


//Задача 1: Да се напише функция, която проверява колко пъти се среща даден символ във файл
int symbolOcuurance(const char* textFile1, char targetChar)
{
	std::ifstream ifs(textFile1);
	if (!textFile1)
	{
		return -1;
	}
	int counter = 0;
	char ch;
	while (ifs.get(ch))
	{
		if (ch==targetChar)
		{
			counter++;
		}
	}
	ifs.close();
	ifs.clear();
	return counter;
}

//Задача 2: От стандартния вход се прочитат три числа. Запишете във файл "result.txt" сумата и произведението им. 
// Направете функция, която извежда на стандартния изход разликата на сумата и произведението, прочетени от файла "result.txt".
int operationsFile(int a, int b, int c, const char* result)
{
	std::ofstream ofs(result);
	if (!ofs.is_open())
	{
		return -1;
	}
	ofs << a + b + c;
	ofs << a * b * c;
	ofs.close();
	std::ifstream ifs(result);
	if (!ifs.is_open())
	{
		return -1;
	}
	int sum;
	int multiply;
	ifs >> sum;
	ifs >> multiply;
	ifs.close();
	ifs.clear();
	return (sum - multiply);
}

//Задача 3: Напишете програма, която чете масив от файл, като заделя точно толкова памет, колкото е нужна. 
// След това да се сортира възходящо и низходящо, като двата резултата да се запишат в два отделни резултатни файла. 
int* readFromFile(const char* textFile1)
{
	if (!textFile1)
	{
		return nullptr;
	}
	std::ifstream ifs(textFile1);
	if (!ifs)
	{
		return nullptr;
	}
	unsigned size;
	ifs >> size;
	if (size <= 0)
	{
		return nullptr;
	}
	int* arr =new int [size];
	for (int i = 0; i < size; i++)
	{
		ifs >> arr[i];
	}
	ifs.close();
	return arr;
}

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void selectionSortDescending (int* arr, int& size)
{
	if (!arr)
	{
		return;
	}
	for (int i = 0; i < size; i++)
	{
		int minIndex = i;
		for (int j = i+1; j < size; j++)
		{
			if (arr[minIndex] < arr[j])
			{
				minIndex = j;
			}
		}
		if (i != minIndex)
		{
			swap(arr[i], arr[minIndex]);
		}
	}
}

void selectionSortAscending(int* arr, int& size)
{
	if (!arr)
	{
		return;
	}
	for (int i = 0; i < size; i++)
	{
		int minIndex = i;
		for (int j = i+1; j < size; j++)
		{
			if (arr[minIndex] > arr[j])
			{
				minIndex = j;
			}
		}
		if (minIndex != i)
		{
			swap(arr[i], arr[minIndex]);
		}
	}
}

void writeSortedArrInFile(const char* textFile1, int* arr, int& size)
{
	if (!textFile1 || !arr)
	{
		return;
	}

	selectionSortDescending(arr, size);
	std::ofstream ofs1("descending.txt");
	if (!ofs1)
	{
		return;
	}
	for (int i = 0; i < size; i++)
	{
		ofs1 << arr[i]<<' ';
	}
	ofs1.close();

	selectionSortAscending(arr, size);
	std::ofstream ofs2("ascending.txt");
	if (!ofs2)
	{
		return;
	}
	for (int i = 0; i < size; i++)
	{
		ofs2 << arr[i]<<' ';
	}
	ofs2.close();
}

namespace CONSTANTS
{
	const int MAX_NAME = 50;
	const int MAX_MARKS = 100;
};

enum class Major
{
	SE,
	CS,
	IS,
	I
};

//Напишете структура FMIStudent, която в себе си има име с големина най-много 50, години, масив от оценки с големина 
// най-много 100 и специалност. Специалностите могат да са SE, CS, IS, I. Вашата задача е да напишете функциите 
// saveStudentToFile(const Student& s, std::ofstream& ofs), readStudentFromFile(Student& s, std::ifstream& ifs). 
// Също така напишете и функциите writeStudentArrayToFile(const char* filename, const Student* students, size_t size) и 
// readStudentArrayFromFile(const char* filename, size_t& size).

struct FMIStudent
{
	char name[CONSTANTS::MAX_NAME + 1]{};
	unsigned age;
	int marks[CONSTANTS::MAX_MARKS]{};
	Major major;
};

void saveStudentToFile(const FMIStudent& s, std::ofstream& ofs)
{
	if (!ofs)
	{
		return;
	}
	ofs << s.name<<'\n';
	ofs << s.age<<'\n';
	int marksCount = 0;
	for (int i = 0; i < CONSTANTS::MAX_MARKS; i++)
	{
		if (s.marks[i] != 0)
		{
			marksCount++;
		}
	}
	ofs << marksCount<<'\n';
	for (int i = 0; i < marksCount; i++)
	{
		ofs << s.marks[i];
	}
	ofs << '\n';
	ofs << (int)s.major;
	ofs << '\n';
}

void readStudentFromFile(FMIStudent& s, std::ifstream& ifs)
{
	if (!ifs)
	{
		return;
	}
	ifs.getline(s.name, CONSTANTS::MAX_NAME+1);
	ifs >> s.age;
	ifs.ignore();

	int marksCount;
	ifs >> marksCount;
	ifs.ignore();
	for (int i = 0; i < marksCount; i++)
	{
		ifs >> s.marks[i];
	}
	ifs.ignore();
	int majorInt = 0;
	ifs >> majorInt;
	s.major=(Major)majorInt;
	ifs.ignore();
}

void writeStudentArrayToFile(const char* textFile1, const FMIStudent* students, size_t size)
{
	std::ofstream ofs(textFile1);
	if (!ofs)
	{
		return;
	}
	ofs << size<<'\n';
	for (int i = 0; i < size; i++)
	{
		saveStudentToFile(students[i], ofs);
	}
	ofs << '\n';
	ofs.close();
}

FMIStudent* readStudentArrayFromFile(const char* textFile1, size_t& size)
{
	std::ifstream ifs(textFile1);
	if (!ifs)
	{
		return nullptr;
	}
	ifs >> size;
	ifs.ignore();
	FMIStudent* students = new FMIStudent[size];
	for (int i = 0; i < size; i++)
	{
		readStudentFromFile(students[i], ifs);
	}
	ifs.ignore();
	ifs.close();
	return students;
}

int main()
{
	//const char* inputFile = "textFile1.txt";
	//int size = 0;
	//int* arr = readFromFile(inputFile);
	//if (!arr) 
	//{
	//	return -1;
	//}
	//writeSortedArrInFile(inputFile, arr, size);
	//delete[] arr;
	//return 0;

	size_t size;
	FMIStudent* students = readStudentArrayFromFile("textFile1.txt", size);
	if (!students)
	{
		return -1;
	}
	if (students) 
	{
		for (size_t i = 0; i < size; i++)
		{
			std::cout << students[i].name << " " << students[i].age << std::endl;
			switch (students[i].major)
			{
			case Major::SE:std::cout << "SE"; break;
			case Major::CS:std::cout << "CS"; break;
			case Major::IS:std::cout << "IS"; break;
			case Major::I:std::cout << "I"; break;
			}
		}
	}
	delete[] students;
}

