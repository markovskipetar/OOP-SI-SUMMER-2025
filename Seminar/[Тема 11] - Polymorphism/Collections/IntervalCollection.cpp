#include "IntervalCollection.h"

IntervalCollection::IntervalCollection(int start, int end)
	:Collection()
{
	numbers = new int[end - start + 1] {0};
	size = end - start + 1;

	this->start = start;
	this->end = end;
}

void IntervalCollection::add(int number)
{
	if (number < start || number > end)
	{
		return;
	}

	int index = number - start;

	numbers[index]++;
}

void IntervalCollection::remove(int number)
{
	if (number < start || number > end)
	{
		return;
	}

	int index = number - start;

	if (numbers[index] == 0)
	{
		return;
	}

	numbers[index]--;
}

int IntervalCollection::getSize() const
{
	int numbersCount = 0;

	for (int i = 0; i < size; i++)
	{
		numbersCount += numbers[i];
	}

	return numbersCount;
}

bool IntervalCollection::contains(int number) const
{
	if (number < start || number > end)
	{
		return false;
	}

	int index = number - start;

	return numbers[index] != 0;
}
