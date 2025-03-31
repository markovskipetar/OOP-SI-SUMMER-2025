#pragma once
#pragma warning(disable:4996)
#include <fstream>
#include <iostream>

class Word
{
	char* content;

	void free();

	void copyFrom(const Word& other);

public:
	Word();

	Word(const Word& other);

	Word& operator=(const Word& other);

	Word(const char* content);

	~Word();

	int compare(const Word& other) const;

	void saveToFile(std::ofstream& ofs) const;

	void readFromFile(std::ifstream& ifs);

	void print() const;
};