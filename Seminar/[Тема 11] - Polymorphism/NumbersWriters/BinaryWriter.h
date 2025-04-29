#pragma once
#include "NumbersWriter.h"
#include <fstream>

class BinaryWriter : public NumbersWriter
{
public:
	void write(const int* numbers, int size) const override;
};

