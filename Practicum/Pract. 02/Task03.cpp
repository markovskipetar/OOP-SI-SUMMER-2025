#include <iostream>
#include <fstream>

bool isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

bool isWhiteSpace(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\n';
}

size_t getNumbersCount(const char * fileName) {
    std::ifstream ifs(fileName);
    size_t size = 0;
    char ch;
    bool inNumber = false;

    if (!ifs.is_open()) {
        std::cout << "Something went wrong";
        return size;
    }

    while (ifs.get(ch)) {
        if ((ch == '-' || isDigit(ch)) && !inNumber) {
            ++size;
            inNumber = true;
        } 
        else if (isWhiteSpace(ch)) {
            inNumber = false;
        }
    }

    ifs.close();
    return size;
}

bool ascending(int a, int b) {
    return a < b;
}

bool descending(int a, int b) {
    return a > b;
}

void selectionSort(int * arr, size_t size, bool (*predicate)(int, int)) {
    if (size == 0 || !arr) { 
        return;
    }
    
    for (size_t i = 0; i < size - 1; i++) {
        size_t bestIndex = i;

        for (size_t j = i + 1; j < size; j++) {
            if(predicate(arr[j], arr[bestIndex])) {
                bestIndex = j;
            }
        }
        
        if (bestIndex != i) {
            std::swap(arr[i], arr[bestIndex]);
        }
    }
}

void readNumbersFromFile(const char * fileName, int * arr, size_t size) {
    std::ifstream ifs(fileName);

    if (!ifs.is_open()) {
        std::cout << "Something went wrong";
        return;
    }

    for (size_t i = 0; i < size; i++) {
        ifs >> arr[i];
    }

    ifs.close();
}

void saveFileContent(const char * fileName, const int * arr, size_t size) {
        std::ofstream ofs(fileName); // no need of clear file method: this line sets the truncate bit to 1
    
        if (!ofs.is_open()) {
            std::cout << "Something went wrong";
            return;
        }
    
        if (!arr) { // nullptr check
            return;
        }
        
        for (size_t i = 0; i < size; i++) {
            ofs << arr[i] << " ";
        }

        ofs.close();
}

// Create this file so that the program runs properly
// Tested with: 9 5 0 1 2 4, ,5 5 -5 5 -5, 101 102 -103
int main() {
    size_t size = getNumbersCount("file03.txt");
    int * arr = new int[size];
    readNumbersFromFile("file03.txt", arr, size);
    
    selectionSort(arr, size, ascending);
    saveFileContent("ascending.txt", arr, size);

    selectionSort(arr, size, descending);
    saveFileContent("descending.txt", arr, size);

    delete [] arr;
}