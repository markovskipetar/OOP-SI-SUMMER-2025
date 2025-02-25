#include <iostream>
#include <fstream>

bool isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

bool isWhiteSpace(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\n';
}

size_t getFileSize(const char * fileName) {
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

    return size;
}

void saveArrToFile(const char * fileName, size_t size, const int * arr) {
    std::ofstream ofs(fileName);

    if (!ofs.is_open()) {
        std::cout << "Something went wrong";
        return;
    }

    if (!arr) { // nullptr check
        ofs.seekp(std::ios::out | std::ios::trunc); // Clear file
        return;
    }
    
    for (size_t i = 0; i < size; i++) {
        ofs << arr[i] << " ";
    }
    
    delete [] arr; // Deleting the "inhereted" array
}

bool ascending(int a, int b) {
    return a < b;
}

bool descending(int a, int b) {
    return a > b;
}

int * copyArr(const int * src, size_t size) {
    if (!src) { // nullptr check
        return nullptr;
    }

    int * res = new int[size];
    for (size_t i = 0; i < size; i++) {
        res[i] = src[i];
    }
    
    return res;
}

// We want to keep the original array so we return a new one
int * selectionSort(const int * arr, size_t size, bool (*predicate)(int, int)) {
    if (size == 0) { 
        return nullptr;
    }
    
    int * res = copyArr(arr, size);

    for (size_t i = 0; i < size - 1; i++) {
        size_t bestIndex = i;

        for (size_t j = i + 1; j < size; j++) {
            if(predicate(res[j], res[bestIndex])) {
                bestIndex = j;
            }
        }
        
        if (bestIndex != i) {
            std::swap(res[i], res[bestIndex]);
        }
    }

    return res;
}

void readAndSortFile(const char * fileName) {
    std::ifstream ifs(fileName);

    if (!ifs.is_open()) {
        std::cout << "Something went wrong";
        return;
    }

    size_t size = getFileSize(fileName);
    int * arr = new int[size];

    for (size_t i = 0; i < size; i++) {
        ifs >> arr[i];
    }

    saveArrToFile("ascending.txt", size, selectionSort(arr, size, ascending));
    saveArrToFile("descending.txt", size, selectionSort(arr, size, descending));

    delete [] arr;
}

// Create this file so that the program runs properly
// Tested with: 9 5 0 1 2 4, ,5 5 -5 5 -5, 101 102 -103
int main() {
    readAndSortFile("file03.txt");
}