#include <iostream>
#include <fstream>

namespace Constants {
	const size_t BUFFER_SIZE = 1024;
	const size_t START_POS = 0;
	const size_t STUDENT_NAME_LENGTH = 50;
	const size_t MAX_GRADES = 10;
	const size_t STUDENT_INFO_LINES = 4;
}

enum class FMIStudentSpeciality {
	SE,
	CS,
	IS,
	I
};

struct FMIStudent {
	char name[Constants::STUDENT_NAME_LENGTH];
	int age;
	float grades[Constants::MAX_GRADES];
	FMIStudentSpeciality speciality;
};

const char* getSpecialityName(FMIStudentSpeciality speciality) {
	switch (speciality) {
	case FMIStudentSpeciality::SE:
		return "SE";
	case FMIStudentSpeciality::CS:
		return "CS";
	case FMIStudentSpeciality::IS:
		return "IS";
	case FMIStudentSpeciality::I:
		return "I";
	}
}

size_t getSpecialityCount(const char* speciality) {
	if (!strcmp(speciality, "SE")) {
		return 0;
	}
	else if (!strcmp(speciality, "CS")) {
		return 1;
	}
	else if (!strcmp(speciality, "IS")) {
		return 2;
	}
	else if (!strcmp(speciality, "I")) {
		return 3;
	}
	return -1;
}

void saveStudentToFile(const FMIStudent& student, std::ofstream& ofs) {
	if (!ofs.is_open()) {
		std::cout << "File not found" << std::endl;
		return;
	}

	ofs << student.name << '\n';

	ofs << student.age << '\n';

	for (size_t i = 0; i < Constants::MAX_GRADES; i++) {
		ofs << student.grades[i] << ' ';
	}

	ofs << '\n';
	ofs << getSpecialityName(student.speciality) << '\n';
}

void writeStudentArrayToFile(const char* filename, const FMIStudent* students, size_t size) {
	std::ofstream ofs(filename);
	if (!ofs.is_open()) {
		std::cout << "File not found" << std::endl;
		return;
	}

	for (size_t i = 0; i < size; i++) {
		saveStudentToFile(students[i], ofs);
	}

	ofs.close();
}

size_t getStudentsCountFromFile(std::ifstream& ifs) {
	if (!ifs.is_open()) {
		std::cout << "File not found" << std::endl;
		return -1;
	}

	size_t count = 0;
	size_t lines = 0;

	while (true) {
		if (ifs.eof()) {
			break;
		}
		char buffer[Constants::BUFFER_SIZE];
		ifs.getline(buffer, Constants::BUFFER_SIZE);
		lines++;
	}

	ifs.clear();
	ifs.seekg(Constants::START_POS, std::ios::beg);

	return lines / Constants::STUDENT_INFO_LINES;
}

void printStudent(FMIStudent& student) {
	std::cout << "Name: " << student.name << std::endl;
	std::cout << "Age: " << student.age << std::endl;
	std::cout << "Grades: ";
	for (size_t i = 0; i < Constants::MAX_GRADES; i++) {
		std::cout << student.grades[i] << ' ';
	}
	std::cout << std::endl;
	std::cout << "Speciality: " << getSpecialityName(student.speciality) << std::endl;
}

void readStudentFromFile(FMIStudent& student, std::ifstream& ifs) {
	if (!ifs.is_open()) {
		std::cout << "File not found" << std::endl;
		return;
	}

	ifs.getline(student.name, Constants::STUDENT_NAME_LENGTH);

	ifs >> student.age;
	ifs >> std::ws;

	for (size_t i = 0; i < Constants::MAX_GRADES; i++) {
		ifs >> student.grades[i];
	}
	ifs >> std::ws;

	char speciality[Constants::BUFFER_SIZE];
	ifs.getline(speciality, Constants::BUFFER_SIZE);
	student.speciality = FMIStudentSpeciality(getSpecialityCount(speciality));
}

void readStudentArrayFromFile(const char* filename, size_t& size) {
	std::ifstream ifs(filename);
	if (!ifs.is_open()) {
		std::cout << "File not found" << std::endl;
		return;
	}

	size = getStudentsCountFromFile(ifs);

	FMIStudent* students = new FMIStudent[size];

	for (size_t i = 0; i < size; i++) {
		readStudentFromFile(students[i], ifs);
	}

	ifs.close();

	for (size_t i = 0; i < size; i++) {
		printStudent(students[i]);
	}

	delete[] students;
}

void inputStudentData(FMIStudent& student) {
	std::cout << "Enter student name: ";
	std::cin >> std::ws;
	char name[Constants::STUDENT_NAME_LENGTH];
	std::cin.getline(name, Constants::STUDENT_NAME_LENGTH);
	strcpy_s(student.name, name);

	std::cout << "Enter student age: ";
	std::cin >> student.age;

	std::cout << "Enter student grades: ";
	for (size_t i = 0; i < Constants::MAX_GRADES; i++) {
		std::cin >> student.grades[i];
	}

	char speciality[Constants::BUFFER_SIZE];
	int specialityCount = -1;
	while (specialityCount == -1) {
		std::cout << "Enter student speciality: ";
		std::cin >> speciality;

		specialityCount = getSpecialityCount(speciality);

		if (specialityCount == -1) {
			std::cout << "Invalid speciality!" << std::endl;
		}
	}

	student.speciality = FMIStudentSpeciality(specialityCount);
}

int main() {
	std::ofstream ofs("students.txt");
	FMIStudent student;
	inputStudentData(student);
	saveStudentToFile(student, ofs);
	ofs.close();

	FMIStudent studentFromFile;
	std::ifstream ifs("students.txt");
	readStudentFromFile(studentFromFile, ifs);
	ifs.close();
	printStudent(studentFromFile);

	std::cout << "Enter the number of students: ";
	size_t size;
	std::cin >> size;
	FMIStudent* students = new FMIStudent[size];
	for (size_t i = 0; i < size; i++) {
		inputStudentData(students[i]);
	}
	writeStudentArrayToFile("students.txt", students, size);
	delete[] students;
	readStudentArrayFromFile("students.txt", size);

	/*
	Test data for a single student:

	Kristian Plamenov Petrov
	19
	5 4 4 3 6 6 6 5.5 4.75 5.5

	Test data for several students:

	Mihail Petrov Georgiev
	20
	3.5 4.5 5 6 3 4.75 5.75 6 6 6
	SE
	Teodor Bonchev Patov
	19
	6 6 6 4.5 3.5 5.67 6 6 5.5 6 
	SE
	*/
}