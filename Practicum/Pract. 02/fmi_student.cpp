#include <iostream>
#include <fstream>

namespace CONSTANTS
{
	constexpr int NAME_MAX_SIZE = 50;
	constexpr int GRADES_MAX_SIZE = 100;
}

enum class Major
{
	SE,
	CS,
	IS,
	I,
	NONE,
};

struct FMIStudent
{
	char name[CONSTANTS::NAME_MAX_SIZE]{};
	unsigned age = 0;

	unsigned grades[CONSTANTS::GRADES_MAX_SIZE]{};
	size_t gradesCount = 0;

	Major major = Major::NONE;
};

void saveStudentToFile(const FMIStudent& s, std::ofstream& ofs)
{
	ofs << s.name << std::endl;
	ofs << s.age << std::endl;

	ofs << s.gradesCount << " ";
	for (size_t i = 0; i < s.gradesCount; i++)
	{
		ofs << s.grades[i];

		if (i != s.gradesCount - 1)
		{
			ofs << " ";
		}
	}
	ofs << std::endl;

	ofs << int(s.major) << std::endl;
}

void saveStudentToFile(const FMIStudent& s, const char* fileName)
{
	if (!fileName)
	{
		return;
	}

	std::ofstream ofs(fileName);
	if (!ofs.is_open())
	{
		return;
	}

	saveStudentToFile(s, ofs);
}

void readStudentFromFile(FMIStudent& s, std::ifstream& ifs)
{
	ifs.getline(s.name, CONSTANTS::NAME_MAX_SIZE);
	ifs >> s.age;

	ifs >> s.gradesCount;
	for (int i = 0; i < s.gradesCount; i++)
	{
		ifs >> s.grades[i];
	}

	int major;
	ifs >> major;
	s.major = Major(major);
}

void readStudentFromFile(FMIStudent& s, const char* fileName)
{
	if (!fileName)
	{
		return;
	}

	std::ifstream ifs(fileName);
	if (!ifs.is_open())
	{
		return;
	}

	readStudentFromFile(s, ifs);
}

void writeStudentArrayToFile(std::ofstream& ofs, const FMIStudent* students, size_t size)
{
	ofs << size << std::endl;
	for (int i = 0; i < size; i++)
	{
		saveStudentToFile(students[i], ofs);
	}

	ofs.close();
}

void writeStudentArrayToFile(const char* fileName, const FMIStudent* students, size_t size)
{
	if (!fileName)
	{
		return;
	}

	std::ofstream ofs(fileName);
	if (!ofs.is_open())
	{
		return;
	}

	writeStudentArrayToFile(ofs, students, size);
}

void readStudentArrayFromFile(std::ifstream& ifs, FMIStudent*& students, size_t& size)
{
	ifs >> size;
	ifs.ignore();

	for (int i = 0; i < size; i++)
	{
		readStudentFromFile(students[i], ifs);
		ifs.ignore();
	}

	ifs.close();
}

void readStudentArrayFromFile(const char* fileName, FMIStudent*& students, size_t& size)
{
	if (!fileName)
	{
		return;
	}

	std::ifstream ifs(fileName);
	if (!ifs.is_open())
	{
		return;
	}

	readStudentArrayFromFile(ifs, students, size);
}

const char* convertToStr(Major major)
{
	switch (major)
	{
	case Major::SE:
		return "SE";
	case Major::CS:
		return "CS";
		break;
	case Major::I:
		return "I";
		break;
	case Major::IS:
		return "IS";
		break;
	case Major::NONE:
		return "NONE";
		break;
	}
}

void printStudent(const FMIStudent& s)
{
	std::cout << "[Name]: " << s.name << std::endl;
	std::cout << "[Age]: " << s.age << std::endl;
	std::cout << "[Grades]: ";

	for (int i = 0; i < s.gradesCount; i++)
	{
		std::cout << s.grades[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "[Major]: " << convertToStr(s.major) << std::endl;
	std::cout << "---------------------" << std::endl;
}

void printStudents(const FMIStudent* students, size_t size)
{
	for (int i = 0; i < size; i++)
	{
		printStudent(students[i]);
	}
}

void freeStudentArr(FMIStudent*& students, size_t& size)
{
	delete[] students;
	students = nullptr;

	size = 0;
}

int main()
{
	FMIStudent st = { "asd", 18, {2, 2, 2}, 3, Major::CS };
	saveStudentToFile(st, "student.txt");

	FMIStudent st2;
	readStudentFromFile(st2, "student.txt");
	std::cout << (st2.major == Major::CS) << std::endl;

	size_t size1 = 3;
	FMIStudent* students1 = new FMIStudent[size1]{ st, st, st };
	writeStudentArrayToFile("student.txt", students1, size1);
	freeStudentArr(students1, size1);

	size_t size2 = 3;
	FMIStudent* students2 = new FMIStudent[size2]{};
	readStudentArrayFromFile("student.txt", students2, size2);
	printStudents(students2, size2);
	freeStudentArr(students2, size2);

	return 0;
}