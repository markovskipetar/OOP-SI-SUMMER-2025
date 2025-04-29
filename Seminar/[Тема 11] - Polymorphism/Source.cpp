#pragma once
#include <iostream>

#include "NumbersWriters/ConsoleWriter.h"
#include "NumbersWriters/ArrayWriter.h"
#include "NumbersWriters/BinaryWriter.h"

#include "Collections/NormalCollection.h"
#include "Collections/IntervalCollection.h"

// design patter: Factory
NumbersWriter* numbersWriterFactory(int writeType)
{
	switch (writeType)
	{
	case 1:
		return new ConsoleWriter();
	case 2:
		return new BinaryWriter();
	case 3:
		return new ArrayWriter();
	default:
		return nullptr;
	}
}

Collection* collectionFactory(int collectionType)
{
	switch (collectionType)
	{
	case 1:
		return new NormalCollection(10);
	case 2:
		return new IntervalCollection(5, 10);
	default:
		return nullptr;
	}
}

int main()
{
	NumbersWriter* numbersWriter = numbersWriterFactory(1);

	Collection* collection = collectionFactory(1);

	collection->add(7);

	collection->print(numbersWriter);

	delete collection;
}