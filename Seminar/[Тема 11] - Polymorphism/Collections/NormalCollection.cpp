#include "NormalCollection.h"

NormalCollection::NormalCollection(int capacity)
	:Collection(nullptr, 0)
{
	capacity = 1;
}

void NormalCollection::add(int number)
{
	if (size == capacity)
	{
		resize();
	}

	numbers[size++] = number;
}

void NormalCollection::remove(int number)
{
	for (int i = 0; i < size; i++)
	{
		if (numbers[i] == number)
		{
			// shiftLeft(i);
			break;
		}
	}
}

int NormalCollection::getSize() const
{
	return size;
}

bool NormalCollection::contains(int number) const
{
	for (int i = 0; i < size; i++)
	{
		if (numbers[i] == number)
		{
			return true;
		}
	}

	return false;
}
