#include <iostream>
#include <fstream>

namespace Constants
{
	constexpr int elementsInBucket = 8;
	constexpr uint8_t leftmostBit = (1 << 7);
}

class Set
{
public:
	Set()
	{
		bitset = nullptr;
		buckets = -1;
		maxElement = -1;
	}

	Set(int maxElement)
	{
		if (setMaxElement(maxElement))
		{
			initializeBitset(maxElement);
		}
	}

	void add(int element)
	{
		// TO DO: ADD resize and validation

		int bucket = getBucket(element);
		int indexInBucket = getIndexInBucket(element);

		uint8_t mask = Constants::leftmostBit;
		mask = (mask >> indexInBucket);

		bitset[bucket] = (bitset[bucket] | mask);
	}

	void remove(int element)
	{
		// TO DO: ADD validation

		int bucket = getBucket(element);
		int indexInBucket = getIndexInBucket(element);

		uint8_t mask = Constants::leftmostBit;
		mask = (mask >> indexInBucket);

		mask = ~mask;
		bitset[bucket] = (bitset[bucket] & mask);
	}

	// TO DO: add complement()
	// TO DO: add intersect()
	// TO DO: add union()

	void print() const
	{
		int number = 0;

		for (int i = 0; i < buckets; i++)
		{
			uint8_t mask = Constants::leftmostBit;

			for (int j = 0; j < Constants::elementsInBucket; j++)
			{
				bool isIncluded = (bitset[i] & mask);

				if (isIncluded)
				{
					std::cout << number << " ";
				}

				(mask = mask >> 1);

				number++;
			}
		}
	}

	~Set()
	{
		delete[] bitset;
	}

private:
	uint8_t* bitset;
	int buckets;
	int maxElement;

	bool setMaxElement(int maxElement)
	{
		if (maxElement > 0)
		{
			this->maxElement = maxElement;
			return true;
		}

		return false;
	}

	void initializeBitset(int maxElement)
	{
		buckets = maxElement / Constants::elementsInBucket + 1;

		bitset = new uint8_t[buckets]{ 0 };
	}

	int getBucket(int element) const
	{
		return element / Constants::elementsInBucket;
	}

	int getIndexInBucket(int element) const
	{
		return element % Constants::elementsInBucket;
	}
};

int main()
{
	Set s(10);

	s.add(5);
	s.add(8);
	s.add(2);

	s.print();

	s.remove(8);

	std::cout << std::endl;

	s.print();
}
