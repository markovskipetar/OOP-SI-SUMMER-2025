
#pragma warning(disable:4996)
#include <iostream>
#include <fstream>
#include <cstring>

struct Car {
    char* brand;
    int year;
    int maxSpeed;
    int* trips;
    int tripsCount;

    
    Car() : brand(nullptr), year(0), maxSpeed(0), trips(nullptr), tripsCount(0) {}

 
    Car(const char* b, int y, int m, const int* t, int count) : year(y), maxSpeed(m), tripsCount(count) {
        brand = new char[strlen(b) + 1];
        strcpy(brand, b);

        trips = new int[tripsCount];
        for (int i = 0; i < tripsCount; ++i) {
            trips[i] = t[i];
        }
    }

    
    ~Car() {
        delete[] brand;
        delete[] trips;
    }

  
    void saveToFile(const char* filename) const {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cout << "Error opening file for writing!\n";
            return;
        }
        int brandLen = strlen(brand);
        file.write((char*)&brandLen, sizeof(brandLen));
        file.write(brand, brandLen);
        file.write((char*)&year, sizeof(year));
        file.write((char*)&maxSpeed, sizeof(maxSpeed));
        file.write((char*)&tripsCount, sizeof(tripsCount));
        file.write((char*)trips, tripsCount * sizeof(int));
        file.close();
    }

    
    void loadFromFile(const char* filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cout << "Error opening file for reading!\n";
            return;
        }
        delete[]brand;
        delete[]trips;

        int brandLen;
        file.read((char*)&brandLen, sizeof(brandLen));
        brand = new char[brandLen + 1];
        file.read(brand, brandLen);
        brand[brandLen] = '\0';     
        file.read((char*)&year, sizeof(year));
        file.read((char*)&maxSpeed, sizeof(maxSpeed));
        file.read((char*)&tripsCount, sizeof(tripsCount));

        trips = new int[tripsCount];
        file.read((char*)trips, tripsCount * sizeof(int));
        file.close();
    }

    
    int totalDistance() const {
        int sum = 0;
        for (int i = 0; i < tripsCount; ++i) {
            sum += trips[i];
        }
        return sum;
    }

    
    int longestTrip() const {
        if (tripsCount == 0) {
            return 0;
        }
        int maxTrip = trips[0];
        for (int i = 1; i < tripsCount; ++i) {
            if (trips[i] > maxTrip) {
                maxTrip = trips[i];
            }
        }
        return maxTrip;
    }
};

int main() {
    int trips[] = { 120, 250, 75, 300 };
    Car car("Skoda", 2015, 200, trips, 4);

    car.saveToFile("car_data.dat");

    Car loadedCar;
    loadedCar.loadFromFile("car_data.dat");

    std::cout << "Total distance: " << loadedCar.totalDistance() << " km\n";
    std::cout << "Longest trip: " << loadedCar.longestTrip() << " km\n";

    return 0;
}