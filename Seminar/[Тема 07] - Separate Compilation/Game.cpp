#include "Game.h"

Game::Game(const char* title, double price, bool isAvailable)
{
	setTitle(title);
	setPrice(price);
	setIsAvailable(isAvailable);
}

Game::Game(const Game& other)
{
	copyFrom(other);
}

Game& Game::operator = (const Game& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Game::~Game()
{
	free();
}

const char* Game::getTitle() const
{
	return title;
}

double Game::getPrice() const
{
	return price;
}

bool Game::isGameAvailable() const
{
	return isAvailable;
}

bool Game::isFree() const
{
	return price == 0;
}

void Game::writeGameToFile(std::ofstream& file)
{

	int sizeOfTitle = strlen(title);

	file.write((const char*)&sizeOfTitle, sizeof(int));
	file.write((const char*)title, sizeOfTitle);

	file.write((const char*)&price, sizeof(double));
	file.write((const char*)&isAvailable, sizeof(bool));
}

void Game::readGameFromFile(std::ifstream& file)
{
	free();

	int sizeOfTitle = 0;

	file.read((char*)&sizeOfTitle, sizeof(int));
	title = new char[sizeOfTitle + 1];

	file.read((char*)title, sizeOfTitle);
	title[sizeOfTitle] = '\0';

	file.read((char*)&price, sizeof(double));
	file.read((char*)&isAvailable, sizeof(bool));
}

void Game::print() const
{
	std::cout << title << " ";
	std::cout << price << " ";

	if (isAvailable)
	{
		std::cout << "is available" << std::endl;
	}
	else
	{
		std::cout << "is not available" << std::endl;
	}
}

void Game::setTitle(const char* title)
{
	if (!title || this->title == title)
	{
		return;
	}

	int titleLength = strlen(title);

	this->title = new char[titleLength + 1];
	strcpy(this->title, title);
	this->title[titleLength] = '\0';

}

void Game::setPrice(double price)
{
	if (price < 0)
	{
		return;
	}

	this->price = price;
}

void Game::setIsAvailable(bool isAvailable)
{
	this->isAvailable = isAvailable;
}

void Game::copyFrom(const Game& other)
{
	int titleLength = strlen(other.title);

	title = new char[titleLength + 1];
	strcpy(title, other.title);
	title[titleLength] = '\0';

	price = other.price;
	isAvailable = other.isAvailable;
}

void Game::free()
{
	delete[] title;
}
