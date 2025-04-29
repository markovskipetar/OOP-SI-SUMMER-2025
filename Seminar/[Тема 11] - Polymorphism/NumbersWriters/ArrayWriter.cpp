#include "ArrayWriter.h"

void ArrayWriter::write(const int* numbers, int size) const
{
	const char* fileName = "ArrayNumbers.arr";

	std::ofstream arrayWriter(fileName);

	if (!arrayWriter.good())
	{
		return;
	}

	NumbersWriter::write(numbers, size);

	arrayWriter << "[";

	for (int i = 0; i < size; i++)
	{
		arrayWriter << numbers[i];

		if (i != size - 1)
		{
			arrayWriter << ",";
		}
	}

	arrayWriter << "]";
}
