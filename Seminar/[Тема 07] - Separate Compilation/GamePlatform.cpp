#include "GamePlatform.h"

GamePlatform::GamePlatform()
{
	countOfGames = 0;
	capacity = 8;
	games = new Game[capacity];
}

GamePlatform::GamePlatform(const GamePlatform& other)
{
	copyFrom(other);
}

GamePlatform& GamePlatform::operator = (const GamePlatform& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;

}

GamePlatform::~GamePlatform()
{
	free();
}

void GamePlatform::addGame(const Game& game)
{
	if (countOfGames == capacity)
	{
		resize(capacity * 2);
	}

	games[countOfGames] = game;
	countOfGames += 1;
}

void GamePlatform::removeGame(const Game& game)
{
	for (int i = 0; i < countOfGames; i++)
	{
		if (!strcmp(games[i].getTitle(), game.getTitle()) &&
			games[i].getPrice() == game.getPrice() &&
			games[i].isGameAvailable() == game.isGameAvailable())
		{

			std::swap(games[i], games[countOfGames - 1]);
			countOfGames -= 1;
			break;

		}
	}
}

void GamePlatform::removeGame(int index)
{
	if (index < 0 || index >= countOfGames)
	{
		return;
	}

	removeGame(games[index]);
}

void GamePlatform::printGames() const
{
	for (int i = 0; i < countOfGames; i++)
	{
		games[i].print();
	}

	std::cout << std::endl;
}

void GamePlatform::printGameByIndex(int index) const
{
	if (index < 0 || index >= countOfGames)
	{
		return;
	}

	games[index].print();
}

void GamePlatform::printCheapestGame() const
{
	int index = 0;
	double currentPrice = games[0].getPrice();

	for (int i = 1; i < countOfGames; i++)
	{
		if (games[i].getPrice() < currentPrice)
		{
			index = i;
			currentPrice = games[i].getPrice();
		}

	}

	printGameByIndex(index);
}

void GamePlatform::printMostExpensiveGame() const
{
	int index = 0;
	double currentPrice = games[0].getPrice();

	for (int i = 1; i < countOfGames; i++)
	{
		if (games[i].getPrice() > currentPrice)
		{
			index = i;
			currentPrice = games[i].getPrice();
		}

	}

	printGameByIndex(index);
}

void GamePlatform::printAllFreeGames() const
{
	for (int i = 0; i < countOfGames; i++)
	{
		if (games[i].isFree()) printGameByIndex(i);
	}
}

void GamePlatform::writeToFile(const char* fileName)
{
	std::ofstream file(fileName, std::ios::binary);

	if (!file.is_open())
	{
		return;
	}

	file.write((const char*)&countOfGames, sizeof(int));

	for (int i = 0; i < countOfGames; i++)
	{
		games[i].writeGameToFile(file);
	}

	file.close();
}

void GamePlatform::readFromFile(const char* fileName) {

	free();

	std::ifstream file(fileName, std::ios::binary);

	if (!file.is_open())
	{
		return;
	}

	file.read((char*)&countOfGames, sizeof(int));

	games = new Game[countOfGames];
	capacity = countOfGames;

	for (int i = 0; i < countOfGames; i++)
	{
		games[i].readGameFromFile(file);
	}

	file.close();
}

void GamePlatform::copyFrom(const GamePlatform& other)
{
	games = new Game[other.capacity];
	capacity = other.capacity;
	countOfGames = other.countOfGames;

	for (int i = 0; i < countOfGames; i++)
	{
		games[i] = other.games[i];
	}
}

void GamePlatform::free()
{
	delete[] games;
}

void GamePlatform::resize(int newCapacity)
{
	if (newCapacity <= capacity)
	{
		return;
	}

	Game* newGames = new Game[newCapacity];

	for (int i = 0; i < countOfGames; i++)
	{
		newGames[i] = games[i];
	}

	delete[] games;

	games = newGames;
	capacity = newCapacity;
}
