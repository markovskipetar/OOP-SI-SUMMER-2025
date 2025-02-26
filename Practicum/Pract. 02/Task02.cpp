#include <iostream>
#include <fstream>

float calcSum(float num1, float num2, float num3) {
    return num1 + num2 + num3;
}

float calcProd(float num1, float num2, float num3) {
    return num1 * num2 * num3;
}

float readFileContentDiff(const char * fileName) {
    std::ifstream ifs(fileName);

    if (!ifs.is_open()) {
        std::cout << "Something went wrong";
        return 0.0f;
    }

    float sum, prod;
    ifs >> sum >> prod;

    return (sum - prod);
}

void saveFileContent(const char * fileName, float sum, float prod) {
    std::ofstream ofs(fileName);

    if (!ofs.is_open()) {
        std::cout << "Something went wrong";
        return;
    }
    
    ofs << sum << '\n' << prod;
}

int main() {
    float num1, num2, num3;
    std::cin >> num1 >> num2 >> num3;

    saveFileContent("file02.txt", calcSum(num1, num2, num3), calcProd(num1, num2, num3));

    std::cout << readFileContentDiff("file02.txt");
}