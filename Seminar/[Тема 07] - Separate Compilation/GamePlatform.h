#pragma once
#include "Game.h"

class GamePlatform
{
public:
	GamePlatform();
	GamePlatform(const GamePlatform& other);
	GamePlatform& operator = (const GamePlatform& other);
	~GamePlatform();

	void addGame(const Game& game);
	void removeGame(const Game& game);
	void removeGame(int index);

	void printGames() const;
	void printGameByIndex(int index) const;
	void printCheapestGame() const;
	void printMostExpensiveGame() const;
	void printAllFreeGames() const;

	void writeToFile(const char* fileName);
	void readFromFile(const char* fileName);

private:
	void copyFrom(const GamePlatform& other);
	void free();

	void resize(int newCapacity);

	Game* games = nullptr;
	int countOfGames = 0;
	int capacity = 8;
};
