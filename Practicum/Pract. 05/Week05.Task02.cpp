#include <iostream>
#pragma warning(disable:4996)

namespace constants {
	constexpr char DEFAULT_NAME[] = "Default truck";
}

class Trailer {
public:
	double getMaximalLoad() const {
		return maximalLoad;
	}

	double getArea() const {
		return area;
	}

	double getCurrentLoad() const {
		return currentLoad;
	}

	void setMaximalLoad(double maximalLoad) {
		this->maximalLoad = maximalLoad;
	}

	void setArea(double area) {
		this->area = area;
	}

	void setCurrentLoad(double currentLoad) {
		if (!isCurrentLoadValid(currentLoad)) {
			currentLoad = maximalLoad;
		}

		this->currentLoad = currentLoad;
	}

	void addLoad(double weight) {
		if (isCurrentLoadValid(weight + currentLoad)) {
			currentLoad += weight;
		}
	}

	Trailer(int maximalLoad, int area, int currentLoad) {
		setMaximalLoad(maximalLoad);
		setArea(area);
		setCurrentLoad(currentLoad);
	}

	Trailer() {
		maximalLoad = 0;
		area = 0;
		currentLoad = 0;
	}

private:
	double maximalLoad;
	double area;
	double currentLoad;

	bool isCurrentLoadValid(double currentLoad) const {
		if (currentLoad > maximalLoad) {
			return false;
		}

		return true;
	}
};

class Engine {
public:
	void setPower(double power) {
		this->power = power;
	}
	void setFuelConsumption(double fuelConsumption) {
		this->fuelConsumption = fuelConsumption;
	}

	void setTankVolume(double tankVolume) {
		this->tankVolume = tankVolume;
	}

	void setCurrentFuel(double currentFuel) {
		if (!isCurrentFuelValid(currentFuel)) {
			currentFuel = tankVolume;
		}

		this->currentFuel = currentFuel;
	}

	double getPower() const {
		return power;
	}

	double getFuelConsumption() const {
		return fuelConsumption;
	}

	double getTankVolume() const {
		return tankVolume;
	}

	double getCurrentFuel() const {
		return currentFuel;
	}

	void refuel(double liters) {
		setCurrentFuel(liters + currentFuel);
	}

	void drive(double km) {
		double fuelConsumed = calculateFuelConsumptionForDriving(km);
		setCurrentFuel(currentFuel - fuelConsumed);
	}

	double getRemainingRange() const {
		double range = currentFuel / fuelConsumption * 100;
		return range;
	}

	Engine(int power, int fuelConsumption, int tankVolume, int currentFuel) {
		setPower(power);
		setFuelConsumption(fuelConsumption);
		setTankVolume(tankVolume);
		setCurrentFuel(currentFuel);
	}

	Engine() {
		power = 0;
		fuelConsumption = 0;
		tankVolume = 0;
		currentFuel = 0;
	}

private:
	double power;
	double fuelConsumption;
	double tankVolume;
	double currentFuel;

	bool isCurrentFuelValid(double currentFuel) const {
		if (currentFuel > tankVolume) {
			return false;
		}

		return true;
	}

	double calculateFuelConsumptionForDriving(double km) const {
		double fuel = km / 100 * fuelConsumption;
		return fuel;
	}
};

class Truck {
public:
	void setBrand(const char* brand) {
		size_t brandLen = strlen(brand);
		this->truckBrand = new char[brandLen + 1];
		strcpy(this->truckBrand, brand);
	}

	void setWeight(double weight) {
		this->weightWithoutTrailer = weight;
	}

	void setEngine(Engine* engine) {
		this->engine = engine;
	}

	void setTrailer(Trailer* trailer) {
		this->trailer = trailer;
	}

	const char* getBrand() const {
		return truckBrand;
	}

	double getWeight() const {
		return weightWithoutTrailer;
	}

	const Engine* getEngine() const {
		return engine;
	}

	const Trailer* getTrailer() const {
		return trailer;
	}

	void attachTrailer(Trailer* trailer) {
		setTrailer(trailer);
	}

	bool hasTrailer() const {
		return (trailer == nullptr ? false : true);
	}

	void detachTrailer() {
		delete trailer;
	}

	void drive(double km) {
		engine->drive(km);
	}

	void loadTruck(double weight) {
		if (!trailer) {
			return;
		}

		trailer->addLoad(weight);
	}

	void changeEngine(Engine* newEngine) {
		setEngine(newEngine);
	}

	Truck(const char* truckBrand, double weight, Engine* engine, Trailer* trailer) {
		setBrand(truckBrand);
		setWeight(weight);
		setEngine(engine);
		setTrailer(trailer);
	}

	Truck() {
		setBrand(constants::DEFAULT_NAME);
		setWeight(0);
		Engine engine;
		setEngine(&engine);
		setTrailer(nullptr);
	}

	~Truck() {
		delete[] truckBrand;
	}

private:
	char* truckBrand;
	double weightWithoutTrailer;
	Engine* engine;
	Trailer* trailer;

};

void test() {
	Engine engine(300, 15, 100, 50);
	Trailer trailer(5000, 30, 2000);
	Truck truck("abv", 8000, &engine, &trailer);


	truck.drive(100);
	engine.refuel(30);
	truck.loadTruck(1500);
	std::cout << engine.getCurrentFuel() << std::endl;
	std::cout << trailer.getCurrentLoad() << std::endl;
	std::cout << engine.getRemainingRange() << std::endl;

	Engine engine2(100, 200, 300, 400);
	std::cout << truck.getBrand() << std::endl;
	truck.changeEngine(&engine2);
	truck.drive(100);
	std::cout << engine2.getCurrentFuel();
}

int main()
{
	test();
}

