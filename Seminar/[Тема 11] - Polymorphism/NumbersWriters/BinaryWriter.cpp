#include "BinaryWriter.h"

void BinaryWriter::write(const int* numbers, int size) const
{
	const char* fileName = "binaryNumbers.dat";

	std::ofstream binaryFile(fileName, std::ios::binary);

	if (!binaryFile.good())
	{
		return;
	}

	NumbersWriter::write(numbers, size);

	binaryFile.write((const char*)numbers, size * sizeof(int));
}
