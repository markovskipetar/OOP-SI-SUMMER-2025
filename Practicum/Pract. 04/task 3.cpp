#include <iostream>
#include <fstream>
#include <sstream>

struct Set {
    int* elements;
    size_t size;
    size_t capacity;

    Set() : elements(new int[2]), size(0), capacity(2) {}

    Set(const char* fileName) : elements(nullptr), size(0), capacity(0) {
        deserialize(fileName);
    }

    ~Set() {
        delete[] elements;
    }

    void resize() {
        capacity *= 2;
        int* newElements = new int[capacity];
        for (size_t i = 0; i < size; ++i) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
    }

    bool addElement(int element) {
        for (size_t i = 0; i < size; ++i) {
            if (elements[i] == element) {
                return false;
            }
        }
        if (size == capacity) {
            resize();
        }
        elements[size++] = element;
        return true;
    }

    bool deleteElement(int element) {
        for (size_t i = 0; i < size; ++i) {
            if (elements[i] == element) {
                elements[i] = elements[size - 1];
                --size;
                return true;
            }
        }
        return false;
    }

    void print() const {
        for (size_t i = 0; i < size; ++i) {
            std::cout << elements[i] << " ";
        }
        std::cout << std::endl;
    }

    void serialize(const char* fileName) const {
        std::ofstream outFile(fileName, std::ios::binary);
        if (!outFile.is_open()) {
            std::cout << "Error opening file for writing!" << std::endl;
            return;
        }
        outFile.write((char*)&size, sizeof(size));
        outFile.write((char*)elements, size * sizeof(int));
        outFile.close();
    }

    void deserialize(const char* fileName) {
        std::ifstream inFile(fileName, std::ios::binary);
        if (!inFile.is_open()) {
            std::cout << "Error opening file for reading!" << std::endl;
            return;
        }
        size_t newSize;
        inFile.read((char*)&newSize, sizeof(newSize));
        int* newElements = new int[newSize];
        inFile.read((char*)newElements, newSize * sizeof(int));
        delete[] elements;
        elements = newElements;
        size = newSize;
        capacity = newSize;
        inFile.close();
    }

    void setUnion(const Set& other) {
        for (size_t i = 0; i < other.size; ++i) {
            addElement(other.elements[i]);
        }
    }

    void setIntersection(const Set& other) {
        int* intersection = new int[size];
        size_t newSize = 0;
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < other.size; ++j) {
                if (elements[i] == other.elements[j]) {
                    intersection[newSize++] = elements[i];
                    break;
                }
            }
        }
        delete[] elements;
        elements = intersection;
        size = newSize;
        capacity = newSize;
    }
};

int main() {
    Set mySet;
    mySet.addElement(1);
    mySet.addElement(2);
    mySet.addElement(3);
    mySet.print();

    mySet.serialize("set_data.dat");

    Set newSet("set_data.dat");
    newSet.print();

    Set anotherSet;
    anotherSet.addElement(2);
    anotherSet.addElement(3);
    anotherSet.addElement(4);

    mySet.setUnion(anotherSet);
    mySet.print();

    mySet.setIntersection(anotherSet);
    mySet.print();

    return 0;
}


