#include "Dictionary.h"

void Dictionary::resize(int newCap)
{
	capacity = newCap;

	Word* temp = new Word[capacity];

	for (int i = 0; i < size; i++) {
		temp[i] = words[i];
	}

	delete[] words;
	words = temp;
}

void Dictionary::free()
{
	delete[] words;
}

void Dictionary::copyFrom(const Dictionary& other)
{
	size = other.size;
	capacity = other.capacity;
	words = new Word[capacity];
	for (int i = 0; i < size; i++) {
		words[i] = other.words[i];
	}
}

int Dictionary::findIndex(const Word& word) const
{
	int i = size - 1;
	while (i >= 0 && word.compare(words[i]) < 0) {
		i--;
	}
	return i + 1;
}

void Dictionary::shiftRight(int index)
{
	for (int i = size; i > index; i--) {
		words[i] = words[i - 1];
	}
}

Dictionary::Dictionary()
{
	size = 0;
	capacity = 8;
	words = new Word[capacity];
}

Dictionary::Dictionary(const Dictionary& other)
{
	copyFrom(other);
}

Dictionary& Dictionary::operator=(const Dictionary& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Dictionary::~Dictionary()
{
	free();
}

void Dictionary::addWord(const Word& word)
{
	if (containsWord(word) != -1) {
		return;
	}

	if (size == capacity) {
		resize(capacity * 2);
	}
	
	int where = findIndex(word);
	shiftRight(where);
	words[where] = word;
	size++;
}

int Dictionary::containsWord(const Word& word) const
{
	int left = 0;
	int right = size - 1;
	while (left <= right) {
		int mid = left + (right - left) / 2;

		int result = words[mid].compare(word);

		if (result == 0) return mid;

		else if (result < 0) {
			left = mid + 1;
		}

		else {
			right = mid - 1;
		}
	}
	return -1;
}

const Word* Dictionary::getWord(int index) const
{
	if (index >= size) {
		return nullptr;
	}

	return &words[index];
}

void Dictionary::saveToFile(const char* fileName) const
{
	std::ofstream ofs(fileName);

	if (!ofs.is_open()) {
		return;
	}

	ofs << capacity << " " << size << std::endl;
	for (int i = 0; i < size; i++) {
		words[i].saveToFile(ofs);
	}
}

void Dictionary::readFromFile(const char* fileName)
{
	std::ifstream ifs(fileName);

	if (!ifs.is_open()) {
		return;
	}

	free();

	ifs >> capacity >> size;
	words = new Word[capacity];
	for (int i = 0; i < size; i++) {
		words[i].readFromFile(ifs);
	}
}

void Dictionary::print() const
{
	for (int i = 0; i < size; i++) {
		std::cout << i << " ";
		words[i].print();
	}
}

int Dictionary::getSize() const
{
	return size;
}
