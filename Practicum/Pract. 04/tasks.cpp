#include <iostream>
#include <fstream>
#pragma warning(disable:4996)

namespace CONSTANTS
{
	constexpr size_t TASKS_MAX_SIZE = 20;
}

struct Task
{
private:
	char* name = nullptr;
	char* desc = nullptr;
	unsigned points = 0;

	void free()
	{
		delete[] name;
		name = nullptr;

		delete[] desc;
		desc = nullptr;

		points = 0;
	}

public:

	Task() = default;
	Task(const char* name, const char* desc, unsigned points)
	{
		setName(name);
		setDesc(desc);
		setPoints(points);
	}

	void setName(const char* name)
	{
		if (!name)
		{
			return;
		}

		delete[] this->name;
		size_t size = strlen(name) + 1;
		this->name = new char[size] {};
		strcpy(this->name, name);
	}

	void setDesc(const char* desc)
	{
		if (!desc)
		{
			return;
		}

		delete[] this->desc;
		size_t size = strlen(desc) + 1;
		this->desc = new char[size] {};
		strcpy(this->desc, desc);
	}

	void setPoints(unsigned points)
	{
		this->points = points;
	}

	const char* getName() const
	{
		return this->name;
	}

	const char* getDesc() const
	{
		return this->desc;
	}

	unsigned getPoints() const
	{
		return points;
	}

	void writeToFile(std::ofstream& outFile)
	{
		size_t nameSize = strlen(name);
		outFile.write((const char*)&nameSize, sizeof(size_t));
		outFile.write((const char*)name, nameSize);

		size_t descSize = strlen(desc);
		outFile.write((const char*)&descSize, sizeof(size_t));
		outFile.write((const char*)desc, descSize);

		outFile.write((const char*)&points, sizeof(unsigned));
	}

	void writeToFile(const char* fileName)
	{
		if (!fileName)
		{
			return;
		}

		std::ofstream outFile(fileName, std::ios::binary);
		if (!outFile.is_open())
		{
			return;
		}

		writeToFile(outFile);
		outFile.close();
	}


	void readFromFile(std::ifstream& inFile)
	{
		free();

		size_t nameSize = 0;
		inFile.read((char*)&nameSize, sizeof(size_t));
		name = new char[nameSize + 1] {};
		inFile.read((char*)name, nameSize);
		name[nameSize] = '\0';

		size_t descSize = 0;
		inFile.read((char*)&descSize, sizeof(size_t));
		desc = new char[descSize + 1] {};
		inFile.read((char*)desc, descSize);
		desc[descSize] = '\0';

		inFile.read((char*)&points, sizeof(unsigned));
	}

	void readFromFile(const char* fileName)
	{
		if (!fileName)
		{
			return;
		}

		std::ifstream inFile(fileName, std::ios::binary);
		if (!inFile.is_open())
		{
			return;
		}

		readFromFile(inFile);
		inFile.close();
	}

	~Task()
	{
		free();
	}

};

struct Exam
{
private:
	Task tasks[CONSTANTS::TASKS_MAX_SIZE]{};
	size_t tasksSize = 0;
	unsigned lowerBound = 0;

public:

	Exam() = default;

	void addTask(const Task& task)
	{
		if (tasksSize >= CONSTANTS::TASKS_MAX_SIZE)
		{
			return;
		}

		//tasks[tasksSize++] = task; //works if big 4 (shallow copy)

		tasks[tasksSize].setName(task.getName());
		tasks[tasksSize].setDesc(task.getDesc());
		tasks[tasksSize].setPoints(task.getPoints());

		tasksSize++;
	}

	void changeMin(unsigned lowerBound)
	{
		this->lowerBound = lowerBound;
	}

	unsigned getMax() const
	{
		unsigned total = 0;
		for (size_t i = 0; i < tasksSize; i++)
		{
			total += tasks[i].getPoints();
		}

		return total;
	}

	void writeToFile(std::ofstream& outFile)
	{
		outFile.write((const char*)&tasksSize, sizeof(size_t));
		for (size_t i = 0; i < tasksSize; i++)
		{
			tasks[i].writeToFile(outFile);
		}
	}

	void writeToFile(const char* fileName)
	{
		if (!fileName)
		{
			return;
		}

		std::ofstream outFile(fileName, std::ios::binary);
		if (!outFile.is_open())
		{
			return;
		}

		writeToFile(outFile);
		outFile.close();
	}

	void readFromFile(std::ifstream& inFile)
	{
		inFile.read((char*)&tasksSize, sizeof(size_t));
		for (size_t i = 0; i < tasksSize; i++)
		{
			tasks[i].readFromFile(inFile);
		}
	}

	void readFromFile(const char* fileName)
	{
		if (!fileName)
		{
			return;
		}

		std::ifstream inFile(fileName, std::ios::binary);
		if (!inFile.is_open())
		{
			return;
		}

		readFromFile(inFile);
		inFile.close();
	}
};

int main()
{
	Exam exam;
	Task task1("task1", "desc1", 500);
	Task task2("task2", "desc2", 500);

	exam.addTask(task1);
	exam.addTask(task2);
	exam.writeToFile("exam.bin");
	std::cout << exam.getMax() << " ";

	Exam exam2;
	exam2.readFromFile("exam.bin");
	std::cout << exam2.getMax();

	return 0;
}
