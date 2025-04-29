#pragma once
#include <iostream>

class NumbersWriter
{
public:
	virtual void write(const int* numbers, int size) const = 0
	{
		std::cout << "Numbers succesfully wrote!";
	}

	virtual ~NumbersWriter() = default;
};

