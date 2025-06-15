#include <iostream>
#include <fstream>
#include <cstring>

struct Task {
    char name[100];
    char description[500];
    int points;

    Task() {
        strcpy(name, "");
        strcpy(description, "");
        points = 0;
    }

    Task(const char* taskName, const char* taskCondition, int taskPoints) {
        strncpy(name, taskName, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
        strncpy(description, taskCondition, sizeof(description) - 1);
        description[sizeof(description) - 1] = '\0';
        points = taskPoints;
    }
};

struct Exam {
    Task tasks[20];
    int minPoints;
    int taskCount;

    Exam(int minPoints) : minPoints(minPoints), taskCount(0) {}

    void addTask(const Task& task) {
        if (taskCount < 20) {
            tasks[taskCount++] = task;
        }
        else {
            std::cout << "Cannot add more tasks, exam is full!\n";
        }
    }

    void writeToFile(const char* fileName) {
        std::ofstream file(fileName);
        if (!file.is_open()) {
            std::cout << "Error opening file for writing!\n";
            return;
        }
        file << minPoints << "\n";
        file << taskCount << "\n";
        for (int i = 0; i < taskCount; i++) {
            file << tasks[i].name << "\n";
            file << tasks[i].description << "\n";
            file << tasks[i].points << "\n";
        }
        file.close();
    }

    void readFromFile(const char* fileName) {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            std::cout << "Error opening file for reading!\n";
            return;
        }
        file >> minPoints;
        file >> taskCount;
        file.ignore();
        for (int i = 0; i < taskCount; i++) {
            file.getline(tasks[i].name, sizeof(tasks[i].name));
            file.getline(tasks[i].description, sizeof(tasks[i].description));
            file >> tasks[i].points;
            file.ignore(); 
        }
        file.close();
    }

    void changeMin(int newMinPoints) {
        minPoints = newMinPoints;
    }

    int getMax() const {
        int total = 0;
        for (int i = 0; i < taskCount; i++) {
            total += tasks[i].points;
        }
        return total;
    }
};

int main() {
    Exam exam(50);
    exam.addTask(Task("Task1", "Solve X problem", 10));
    exam.addTask(Task("Task2", "Solve Y problem", 15));
    exam.writeToFile("exam.txt");
    exam.readFromFile("exam.txt");
    std::cout << "Max points: " << exam.getMax() << std::endl;
    return 0;
}

