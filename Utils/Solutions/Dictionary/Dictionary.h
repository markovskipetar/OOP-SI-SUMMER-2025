#pragma once
#include "Word.h"

class Dictionary
{
	Word* words;
	int capacity;
	int size;

	void resize(int newCap);

	void free();

	void copyFrom(const Dictionary& other);

	int findIndex(const Word& word) const;

	void shiftRight(int index);
public:

	Dictionary();

	Dictionary(const Dictionary& other);

	Dictionary& operator=(const Dictionary& other);

	~Dictionary();

	void addWord(const Word& word);

	int containsWord(const Word& word) const;

	const Word* getWord(int index) const;

	void saveToFile(const char* fileName) const;

	void readFromFile(const char* fileName);

	void print() const;

	int getSize() const;
};

