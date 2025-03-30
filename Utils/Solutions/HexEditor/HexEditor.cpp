#include "HexEditor.h"
#include <iostream>
#include <fstream>
#pragma warning (disable:4996)

namespace Utils
{
	const char* DEFAULT_FILE_NAME = "defaultFile.dat";
	const float RESIZE_FACTOR = 1.5;
	const size_t DEFAULT_CAPACITY = 16;
	const char SYMBOLS[] = "0123456789ABCDEF";
	const size_t BYTES_ON_LINE = 16;

	size_t getFileSize(std::ifstream& ifs)
	{
		size_t currPos = ifs.tellg();
		ifs.seekg(0, std::ios::end);
		size_t size = ifs.tellg();
		ifs.seekg(currPos);
		return size;
	}
}

void HexEditor::copyFrom(const HexEditor& other)
{
	fileName = new char[strlen(other.fileName) + 1];
	strcpy(fileName, other.fileName);

	size = other.size;
	capacity = other.capacity;

	buffer = new unsigned char[capacity];

	memcpy(buffer, other.buffer, size);

}

void HexEditor::free()
{
	delete[] buffer;
	buffer = nullptr;

	delete[] fileName;
	fileName;

	size = 0;
	capacity = 0;
}

void HexEditor::resize()
{
	capacity = size * Utils::RESIZE_FACTOR;

	unsigned char* newBuff = new unsigned char[capacity];

	memcpy(newBuff, buffer, size);

	delete[] buffer;

	buffer = newBuff;
}

void HexEditor::saveToFile(const char* fileName) const
{
	if (!fileName)
		return;

	std::ofstream ofs(fileName, std::ios::binary);

	if (!ofs.is_open())
	{
		return;
	}

	ofs.write((const char*)buffer, size * sizeof(unsigned char));
}

void HexEditor::printByteAsHex(unsigned char byte) const
{
	unsigned char left = byte >> 4;
	unsigned char right = byte & 15;

	std::cout << Utils::SYMBOLS[left] << Utils::SYMBOLS[right] << ' ';
}

bool HexEditor::isValidSymbol(unsigned char ch) const
{
	return (ch >= 'a' && ch <= 'z') ||
		(ch >= 'A' && ch <= 'Z') ||
		(ch >= '0' && ch <= '9');
}

HexEditor::HexEditor()
{
	size = 0;
	capacity = Utils::DEFAULT_CAPACITY;

	buffer = new unsigned char[capacity];

	fileName = new char[strlen(Utils::DEFAULT_FILE_NAME) + 1];
	strcpy(fileName, Utils::DEFAULT_FILE_NAME);
}

HexEditor::HexEditor(const HexEditor& other)
{
	copyFrom(other);
}

HexEditor& HexEditor::operator=(const HexEditor& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

HexEditor::~HexEditor()
{
	free();
}

void HexEditor::loadFile(const char* fileName)
{
	if (!fileName)
		return;

	std::ifstream ifs(fileName, std::ios::binary);

	if (!ifs.is_open())
	{
		return;
	}

	free();

	size = Utils::getFileSize(ifs);

	capacity = (size == 0) ? Utils::DEFAULT_CAPACITY : size * Utils::RESIZE_FACTOR;

	buffer = new unsigned char[capacity];

	ifs.read((char*)buffer, size * sizeof(unsigned char));

	this->fileName = new char[strlen(fileName) + 1];
	strcpy(this->fileName, fileName);
}

void HexEditor::print() const
{
	std::cout << "\n\n";
	for (int i = 0; i < size; i++)
	{
		printByteAsHex(buffer[i]);
		if ((i + 1) % Utils::BYTES_ON_LINE == 0)
			std::cout << '\n';
	}
	std::cout << "\n\n";

	for (int i = 0; i < size; i++)
	{
		if (isValidSymbol(buffer[i]))
		{
			std::cout << buffer[i];
		}
		else
		{
			std::cout << '.';
		}

		if ((i + 1) % Utils::BYTES_ON_LINE == 0)
			std::cout << '\n';
	}
}

void HexEditor::editByte(unsigned index, unsigned char byte)
{
	if (index >= size)
	{
		return;
	}

	buffer[index] = byte;
}

void HexEditor::removeByte()
{
	if (size == 0)
		return;

	size--;
}

void HexEditor::addByte(unsigned char byte)
{
	if (size == capacity)
	{
		resize();
	}

	buffer[size] = byte;
	size++;
}

void HexEditor::save() const
{
	saveToFile(fileName);
}

void HexEditor::saveAs(const char* fileName) const
{
	saveToFile(fileName);
}
