#pragma once
#include "NumbersWriter.h"
#include <iostream>

class ConsoleWriter : public NumbersWriter
{
public:
	void write(const int* numbers, int size) const override;
};

