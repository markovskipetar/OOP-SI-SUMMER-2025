#include <iostream>
#include <fstream>
#pragma warning(disable:4996)

struct Car
{
private:
	char* brand = nullptr;
	unsigned year = 0;
	unsigned maxSpeed = 0;
	int* travels = nullptr;
	size_t travelsCount = 0;

	void free()
	{
		delete[] brand;
		brand = nullptr;

		year = 0;

		maxSpeed = 0;

		delete[] travels;
		travels = nullptr;
		travelsCount = 0;
	}

public:

	Car() = default;

	Car(const char* brand, unsigned year, unsigned maxSpeed, const int* travels, size_t travelsCount)
	{
		setBrand(brand);
		setYear(year);
		setMaxSpeed(maxSpeed);
		setTravels(travels, travelsCount);
	}

	void setBrand(const char* brand)
	{
		if (!brand || brand == this->brand)
		{
			return;
		}

		delete[] this->brand;
		size_t size = std::strlen(brand) + 1;
		this->brand = new char[size] {};
		std::strcpy(this->brand, brand);
	}

	void setYear(unsigned year)
	{
		this->year = year;
	}

	void setMaxSpeed(unsigned maxSpeed)
	{
		this->maxSpeed = maxSpeed;
	}

	void setTravels(const int* travels, size_t travelsCount)
	{
		if (!travels || travels == this->travels || travelsCount == 0)
		{
			return;
		}
		
		delete[] this->travels;
		this->travels = new int[travelsCount] {};
		for (size_t i = 0; i < travelsCount; i++)
		{
			this->travels[i] = travels[i];
		}
		
		this->travelsCount = travelsCount;
	}

	const char* getBrand() const
	{
		return this->brand;
	}
	
	unsigned getYear() const
	{
		return this->year;
	}

	unsigned getMaxSpeed() const
	{
		return this->maxSpeed;
	}

	const int* getTravels() const
	{
		return this->travels;
	}
	
	void saveToBinary(std::ofstream& outFile) const
	{
		size_t brandSize = strlen(brand);
		outFile.write((const char*)&brandSize, sizeof(size_t));
		outFile.write((const char*)brand, brandSize);

		outFile.write((const char*)&year, sizeof(unsigned));
		outFile.write((const char*)&maxSpeed, sizeof(unsigned));

		outFile.write((const char*)&travelsCount, sizeof(size_t));
		outFile.write((const char*)travels, sizeof(int) * travelsCount);
	}

	void saveToBinary(const char* fileName) const
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

		saveToBinary(outFile);
		outFile.close();
	}


	void readFromBinary(std::ifstream& inFile)
	{
		free(); //if car exists

		size_t brandSize = 0;
		inFile.read((char*)&brandSize, sizeof(size_t));
		brand = new char[brandSize + 1];
		inFile.read((char*)brand, brandSize);
		brand[brandSize] = '\0';

		inFile.read((char*)&year, sizeof(unsigned));
		inFile.read((char*)&maxSpeed, sizeof(unsigned));

		inFile.read((char*)&travelsCount, sizeof(size_t));
		travels = new int[travelsCount];
		inFile.read((char*)travels, sizeof(int) * travelsCount);
	}

	void readFromBinary(const char* fileName)
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

		readFromBinary(inFile);
		inFile.close();
	}

	unsigned getTotalKmsDriven() const
	{
		if (travelsCount == 0)
		{
			return 0;
		}

		unsigned kmsDriven = 0;
		for (size_t i = 0; i < travelsCount; i++)
		{
			kmsDriven += travels[i];
		}

		return kmsDriven;
	}

	unsigned getLongestTravel() const
	{
		if (travelsCount == 0)
		{
			return 0;
		}

		unsigned longestTravel = travels[0];
		for (size_t i = 1; i < travelsCount; i++)
		{
			if (travels[i] > longestTravel)
			{
				longestTravel = travels[i];
			}
		}

		return longestTravel;
	}

	void printInfo() const
	{
		std::cout << "Brand: " << brand << std::endl;
		std::cout << "Year: " << year << std::endl;
		std::cout << "Max Speed: " << maxSpeed << " km/h" << std::endl;
		std::cout << "Total KMs: " << getTotalKmsDriven() << " km" << std::endl;
		std::cout << "Longest Travel: " << getLongestTravel() << " km" << std::endl;
	}

	~Car()
	{
		free();
	}
};

int main()
{
	int travels[] = { 242, 4252, 402 };
	Car car("car1", 2018, 250, travels, 3);
	car.printInfo();
	car.saveToBinary("car.bin");

	Car car2;
	car2.readFromBinary("car.bin");
	car2.printInfo();

	return 0;
}
