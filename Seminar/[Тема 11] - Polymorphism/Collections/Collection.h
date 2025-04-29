#pragma once
#include "NumbersWriter.h"

class Collection
{
public:
	Collection(const int* numbers, int size);

	virtual void add(int number) = 0;
	virtual void remove(int number) = 0;
	virtual int getSize() const = 0;
	virtual bool contains(int number) const = 0;
	void print(NumbersWriter* numbersWriter) const;

	virtual ~Collection()
	{
		delete[] numbers;
	}

protected:
	Collection() = default;
	int size = 0;
	int* numbers = nullptr;

private:
	void copy(const int* numbers, int size);

};

