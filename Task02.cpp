#include <iostream>
#include <fstream>
#include <cstring>

#pragma warning(disable:4996)

namespace CONSTANTS
{
	constexpr size_t EXAM_TASK_LIMIT = 20;
	constexpr size_t BUFFER = 1024;
}

struct Task {
	char * title;
	size_t titleSize;
	char * description;
	size_t descriptionSize;
	int points;

	Task() {
		title = nullptr;
		titleSize = 0;
		description = nullptr;
		descriptionSize = 0;
		points = 0;
	}

	Task(const char * title, const char * description, int points) {
		titleSize = strlen(title) + 1;
		this->title = new char[titleSize];

		descriptionSize = strlen(description) + 1;
		this->description = new char[descriptionSize];

		strcpy(this->title, title);
		strcpy(this->description, description);

		this->points = points;
	}

	void changeTitle(const char * newTitle) {
		titleSize = strlen(newTitle) + 1;
		delete [] title;
		title = new char[titleSize];
		strcpy(title, newTitle);
	}

	void changeDescription(const char * newDescription) { 
		descriptionSize = strlen(newDescription) + 1;
		delete [] description;
		description = new char[descriptionSize];
		strcpy(description, newDescription);
	}

	void changePoints(int newPoints) { 
		points = newPoints;
	}

	void writeToFile(std::ofstream& ofs) const {
		ofs << title << " (" << points << ") " << std::endl << description << std::endl << std::endl;
	}

	void readFromFile(std::ifstream& ifs) {
		readTextFromFile(ifs, title, titleSize, '(');
		ifs >> points;
		ifs.ignore(CONSTANTS::BUFFER, '\n');
		readTextFromFile(ifs, description, descriptionSize, '\n');
		ifs >> std::ws;
	}
	
	void readTextFromFile(std::ifstream& ifs, char*& text, size_t& textSize, char delimiter) {
		char buffer[CONSTANTS::BUFFER];
		ifs.getline(buffer, CONSTANTS::BUFFER, delimiter);
		textSize = strlen(buffer);
		delete [] text;
		text = new char[textSize + 1];
		strcpy(text, buffer);
	}

	~Task() {
		delete [] title;
		delete [] description;
	}
};

struct Exam {
	Task tasks[CONSTANTS::EXAM_TASK_LIMIT];
	size_t tasksSize;
	int minPointToPass;

	Exam() {
		tasksSize = 0;
		minPointToPass = 0;
	}

	Exam(int minPointToPass) {
		tasksSize = 0;
		this->minPointToPass = minPointToPass;
	}

	void addTask(const char * title, const char * description, int points) { 
		tasks[tasksSize].changeTitle(title);
		tasks[tasksSize].changeDescription(description);
		tasks[tasksSize].changePoints(points);
		tasksSize++;
	}

	void addTask(const Task &task) { 
		addTask(task.title, task.description, task.points);
	}
	

	void writeToFile(const char* fileName) const{ 
		std::ofstream ofs(fileName);

		if (!ofs.is_open()) {
			std::cerr << "Error: Cannot open file!\n";
			return;
		}

		ofs << minPointToPass << " points at least to pass" << std::endl;

		for (size_t i = 0; i < tasksSize; i++) {
			tasks[i].writeToFile(ofs);
		}

		ofs.close();
	}

	void readFromFile(const char* fileName) { 
		std::ifstream ifs(fileName);
		if (!ifs.is_open()) {
			std::cerr << "Error: Cannot open file!\n";
			return;
		}
		
		int fileMinPoints = 0;
		ifs >> fileMinPoints;
		changeMinPointToPass(fileMinPoints);
		ifs.ignore(CONSTANTS::BUFFER, '\n');
	
		tasksSize = 0;
	
		while (true) {
			Task task;
			task.readFromFile(ifs);
			addTask(task);			

			if (ifs.eof() || this->tasksSize >= CONSTANTS::EXAM_TASK_LIMIT) {
				break;
			}
		}
	}
	

	void changeMinPointToPass(int newMinPoints) { 
		this->minPointToPass = newMinPoints;
	}

	int getMaxPoints() const { 
		int sum = 0;
		for (size_t i = 0; i < tasksSize; i++) {
			sum += tasks[i].points;
		}

		return sum;		
	}
};

int main() {
	Task task1("Problem 1", "What was my grade?", 1);
	Task task2("Problem 2", "What is my grade?", 1);
	Task task3("Problem 3", "What will be my grade?", 2);

	Exam exam1(2);
	Exam exam2;
	
	exam1.addTask(task1);
	exam1.writeToFile("exam1.txt");

	task2.changePoints(2);
	exam1.addTask(task2);
	exam1.writeToFile("exam1.txt");

	exam2.readFromFile("exam1.txt");
	exam2.writeToFile("exam2.txt");

	task3.changeTitle("Task 3");
	exam1.addTask(task3);
	exam1.writeToFile("exam1.txt");
}