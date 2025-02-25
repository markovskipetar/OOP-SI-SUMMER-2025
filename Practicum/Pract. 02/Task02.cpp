#include <iostream>
#include <fstream>

namespace files {
    const char* SOURSE_FILE_NAME = "input.txt";
    const char* FILE1_NAME = "ascending.txt";
    const char* FILE2_NAME = "descending.txt";
    
}

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void selectionSort(int* arr, size_t size) {
    for (int i = 0;i < size - 1;i++) {
        int index = i;
        for (int j = i + 1;j < size;j++) {
            if (arr[j] < arr[index]) index = j;
        }

        if (index != i) swap(arr[i], arr[index]);
    }
}

void cretingFilesWithArr(const int* arr, size_t size) {
    std::ofstream ofs_ascending(files::FILE1_NAME);
    std::ofstream ofs_descending(files::FILE2_NAME);


    if (!ofs_ascending.is_open()) {
        std::cout << "Error with file: " <<files::FILE1_NAME  << std::endl;
    }

    if (!ofs_descending.is_open()) {
        std::cout << "Error with file: " << files::FILE2_NAME << std::endl;
    }

    ofs_ascending << size;
    ofs_ascending << "\n";
    for (int i = 0;i < size;i++) {
        ofs_ascending << arr[i] << " ";
    }

    ofs_descending << size;
    ofs_descending << "\n";
    for (int i = size - 1;i >= 0;i--) {
        ofs_descending << arr[i] << " ";
    }
}

void sortAndCreateFiliesForArr() {
    std::ifstream ifs(files::SOURSE_FILE_NAME);

    int sizeOfArr;
    ifs >> sizeOfArr;
    int* arr = new int[sizeOfArr];

    for (int i = 0;i < sizeOfArr;i++) {
        ifs >> arr[i];
    }

    selectionSort(arr, sizeOfArr);

    cretingFilesWithArr(arr, sizeOfArr);
}

int main()
{
    sortAndCreateFiliesForArr();
}
