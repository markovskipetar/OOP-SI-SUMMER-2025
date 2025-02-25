#include <iostream>
#include <fstream>

float calcSum(float num1, float num2, float num3) {
    return num1 + num2 + num3;
}

float calcProd(float num1, float num2, float num3) {
    return num1 * num2 * num3;
}

void printDiff(float sum, float prod) {
    std::cout << sum - prod;
}

void saveSumAndProduct(const char * fileName, float sum, float prod) {
    std::ofstream ofs(fileName);

    if (!ofs.is_open()) {
        std::cout << "Something went wrong";
        return;
    }
    
    ofs << sum << '\n' << prod;
    ofs.close();
}

void readSumAndProduct(const char * fileName) {
    std::ifstream ifs(fileName);

    if (!ifs.is_open()) {
        std::cout << "Something went wrong";
        return;
    }

    float sum, prod;
    ifs >> sum >> prod;
    printDiff(sum, prod);

    ifs.close();
}

int main() {
    float num1, num2, num3;
    std::cin >> num1 >> num2 >> num3;
    saveSumAndProduct("file02.txt", calcSum(num1, num2, num3), calcProd(num1, num2, num3));
    readSumAndProduct("file02.txt");
}