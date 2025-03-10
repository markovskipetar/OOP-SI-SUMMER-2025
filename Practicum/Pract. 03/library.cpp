#include <iostream>
#include <fstream>

namespace CONSTANTS
{
	constexpr size_t TITLE_MAX_SIZE = 20;
	constexpr size_t AUTHOR_NAME_MAX_SIZE = 20;
	constexpr size_t BOOKS_MAX_SIZE = 20;
}

struct Book
{
	char title[CONSTANTS::TITLE_MAX_SIZE]{};
	char author[CONSTANTS::AUTHOR_NAME_MAX_SIZE]{};
	unsigned year = 0;
	unsigned copies = 0;
};

struct Library
{
	Book books[CONSTANTS::BOOKS_MAX_SIZE]{};
	size_t booksCount = 0;
};

void addBook(Library& lib, const Book& book)
{
	if (lib.booksCount >= CONSTANTS::BOOKS_MAX_SIZE)
	{
		return;
	}

	lib.books[lib.booksCount++] = book;
}

Book lookFor(const Library& lib, const char* title)
{
	if (!title)
	{
		return {};
	}

	for (size_t i = 0; i < lib.booksCount; i++)
	{
		if (!strcmp(lib.books[i].title, title))
		{
			return lib.books[i];
		}
	}

	return {};
}

void printBook(const Book& book)
{
	std::cout << "----[Title]: " << book.title << " "
			  << "----[Author]: " << book.author << " "
			  << "----[Published]: " << book.year << " "
		   	  << "----[Copies]: " << book.copies << std::endl;
}

void printLib(const Library& lib)
{
	std::cout << "Library:" << std::endl;
	for (size_t i = 0; i < lib.booksCount; i++)
	{
		printBook(lib.books[i]);
	}
	
	std::cout << "---------------------------------------------" << std::endl;
}

void saveLibToBinary(std::ofstream& outFile, const Library& lib)
{
	outFile.write((const char*)&lib, sizeof(Library));
}

void saveLibToBinary(const char* fileName, const Library& lib)
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

	saveLibToBinary(outFile, lib);
	outFile.close();
}

Library readLibFromBinary(std::ifstream& inFile)
{
	Library lib;
	inFile.read((char*)&lib, sizeof(Library));
	return lib;
}

Library readLibFromBinary(const char* fileName)
{
	if (!fileName)
	{
		return {};
	}

	std::ifstream inFile(fileName, std::ios::binary);
	if (!inFile.is_open())
	{
		return {};
	}

	Library lib = readLibFromBinary(inFile);

	inFile.close();
	return lib;
}

#include <iostream>
#include <fstream>

int main()
{
	Library lib = {
		{
			{"book1", "author1", 2025, 10},
			{"book2", "author2", 2024, 15},
		},

		2
	};

	Book book3 = { "book3", "author3", 2025, 20 };
	addBook(lib, book3);

	printLib(lib);

	saveLibToBinary("library.bin", lib);

	Library lib2 = readLibFromBinary("library.bin");
	printLib(lib2);

	Book book3Cpy = lookFor(lib, "book3");
	printBook(book3Cpy);

	return 0;

}