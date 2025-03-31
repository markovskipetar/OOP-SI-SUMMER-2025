#include "Word.h"

void Word::free()
{
	delete[] content;
}

void Word::copyFrom(const Word& other)
{
	content = new char[strlen(other.content) + 1];
	strcpy(content, other.content);
}

Word::Word()
{
	content = nullptr;
}

Word::Word(const Word& other)
{
	copyFrom(other);
}

Word& Word::operator=(const Word& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Word::Word(const char* content)
{
	this->content = new char[strlen(content) + 1];

	strcpy(this->content, content);
}

Word::~Word()
{
	free();
}

int Word::compare(const Word& other) const
{
	return strcmp(content, other.content);
}

void Word::saveToFile(std::ofstream& ofs) const
{
	ofs << strlen(content) << " " << content << std::endl;
}

void Word::readFromFile(std::ifstream& ifs) 
{
	free();

	int len;
	ifs >> len;
	content = new char[len + 1];
	ifs >> content;
}

void Word::print() const {
	std::cout << content << std::endl;
}