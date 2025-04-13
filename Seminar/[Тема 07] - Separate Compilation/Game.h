#pragma once
#pragma warning (disable: 4996)

#include <iostream>
#include <cmath>
#include <fstream>

class Game
{
public:
	Game() = default;

	Game(const char* title, double price, bool isAvailable);
	Game(const Game& other);
	Game& operator = (const Game& other);
	~Game();

	const char* getTitle() const;
	double getPrice() const;
	bool isGameAvailable() const;
	bool isFree() const;

	void writeGameToFile(std::ofstream& file);
	void readGameFromFile(std::ifstream& file);

	void print() const;

private:
	void copyFrom(const Game& other);
	void free();

	void setTitle(const char* title);
	void setPrice(double price);
	void setIsAvailable(bool isAvailable);

	char* title = nullptr;
	double price = 0;
	bool isAvailable = false;
};

