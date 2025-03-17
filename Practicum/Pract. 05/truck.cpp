#include <iostream>
#pragma warning(disable:4996)

namespace CONSTANTS
{
	constexpr int DEFAULT_BRAND_SIZE = 14;
	constexpr char DEFAULT_BRAND_NAME[DEFAULT_BRAND_SIZE + 1] = "Default truck";
}

class Trailer
{
public:

	Trailer() = default;

	Trailer(double maxSurface, double maxWeight, double currWeight) :
		maxSurface(maxSurface), maxWeight(maxWeight), currWeight(currWeight){}

	void addLoad(double weight)
	{
		if (weight + currWeight <= maxWeight)
		{
			currWeight += weight;
		}
	}

	double getMaxSurface() const
	{
		return maxSurface;
	}

	double getMaxWeight() const
	{
		return maxWeight;
	}

	double getCurrWeight() const
	{
		return currWeight;
	}

private:
	double maxSurface = 100;
	double maxWeight = 1200;
	double currWeight = 0;

};


class Engine
{
public:

	Engine() = default;

	Engine(unsigned power, double litersPerKm, double capacityLiters, double currLiters):
		power(power), litersPerKm(litersPerKm), capacityLiters(capacityLiters), currLiters(currLiters){}

	unsigned getPower() const
	{
		return power;
	}

	double getLitersPerKm() const
	{
		return litersPerKm;
	}

	double getCapacityLiters() const
	{
		return capacityLiters;
	}

	double getCurrLiters() const
	{
		return currLiters;
	}

	void refuel(double liters)
	{
		if (liters + currLiters >= capacityLiters)
		{
			currLiters = capacityLiters;
			return;
		}

		currLiters += liters;
	}

	void drive(double km)
	{
		if (km * litersPerKm > currLiters)
		{
			return;
		}

		currLiters -= km * litersPerKm;
	}

	double getRemainingRange() const
	{
		return currLiters / litersPerKm;
	}

private:
	unsigned power = 400.0;
	double litersPerKm = 0.4;
	double capacityLiters = 400.0;
	double currLiters = 0.0;
};

class Truck
{
public:

	Truck()
	{
		brand = new char[CONSTANTS::DEFAULT_BRAND_SIZE + 1]{};
		strcpy(brand, CONSTANTS::DEFAULT_BRAND_NAME);

		engine = new Engine();
	}

	Truck(const char* brand, double weight, Engine* engine, Trailer* trailer) :
		weight(weight), engine(engine), trailer(trailer)
	{
		setBrand(brand);
	}

	const char* getBrand() const
	{
		return brand;
	}

	double getWeight() const
	{
		return weight;
	}

	const Engine* getEngine() const
	{
		return engine;
	}

	const Trailer* getTrailer() const
	{
		return trailer;
	}

	void attachTrailer(Trailer* trailer)
	{
		if (!trailer)
		{
			return;
		}

		delete this->trailer;
		this->trailer = trailer;
	}

	void detachTrailer()
	{
		delete trailer;
		trailer = nullptr;
	}

	bool hasTrailer() const
	{
		return trailer;
	}

	void drive(double km)
	{
		engine->drive(km);
	}

	void loadTruck(double weight)
	{
		if (!trailer)
		{
			return;
		}

		trailer->addLoad(weight);
	}

	void changeEngine(Engine* newEngine)
	{
		if (!newEngine)
		{
			return;
		}

		delete engine;
		engine = newEngine;
	}

	~Truck()
	{
		free();
	}

private:

	void setBrand(const char* brand)
	{
		if (!brand || strlen(brand) == 0 || this->brand == brand)
		{
			return;
		}

		//delete[] this->brand; for reusability
		this->brand = new char[strlen(brand) + 1] {};
		strcpy(this->brand, brand);
	}

	void free()
	{
		delete[] brand;
		brand = nullptr;

		weight = 0;

		delete engine;
		engine = nullptr;

		delete trailer;
		trailer = nullptr;
	}

	char* brand = nullptr;
	double weight = 8000.0;
	Engine* engine = nullptr;
	Trailer* trailer = nullptr;
};


int main()
{

	Truck t;
	std::cout << t.getBrand() << std::endl;

	std::cout << t.hasTrailer() << std::endl;

	Trailer* trailer = new Trailer;
	t.attachTrailer(trailer);
	std::cout << t.hasTrailer() << std::endl;
	t.loadTruck(50);
	const Trailer* trailer2 = t.getTrailer();
	std::cout << trailer->getCurrWeight() << std::endl;

	t.detachTrailer();
	std::cout << t.hasTrailer() << std::endl;

	Engine* engine = new Engine(50, 10, 50, 50);
	t.changeEngine(engine);
	std::cout << engine->getRemainingRange() << std::endl;
	t.drive(1);
	std::cout << engine->getRemainingRange() << std::endl;

	const Engine* engine2 = t.getEngine();
	std::cout << engine2->getPower() << std::endl;

	return 0;
}
