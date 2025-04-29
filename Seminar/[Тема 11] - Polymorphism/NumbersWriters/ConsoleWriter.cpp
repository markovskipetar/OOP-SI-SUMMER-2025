#include "ConsoleWriter.h"

void ConsoleWriter::write(const int* numbers, int size) const
{
	NumbersWriter::write(numbers, size);

	for (int i = 0; i < size; i++)
	{
		std::cout << numbers[i] << " ";
	}
}
