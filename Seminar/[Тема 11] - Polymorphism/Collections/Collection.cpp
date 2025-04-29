#include "Collection.h"

Collection::Collection(const int* numbers, int size)
{
	copy(numbers, size);
}

void Collection::print(NumbersWriter* numbersWriter) const
{
	numbersWriter->write(numbers, size);
}

void Collection::copy(const int* numbers, int size)
{
	if (!numbers)
	{
		this->numbers = new int[1];
		size = 0;
	}

	this->numbers = new int[size];

	for (int i = 0; i < size; i++)
	{
		this->numbers[i] = numbers[i];
	}
}
