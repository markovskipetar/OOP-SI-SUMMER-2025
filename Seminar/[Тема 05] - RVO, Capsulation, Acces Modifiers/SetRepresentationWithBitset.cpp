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

	int getBuckets() const
	{
		return buckets;
	}

	int getMaxElement() const
	{
		return maxElement;
	}

	const uint8_t* getBitset() const
	{
		return bitset;
	}

	void add(int element)
	{
		if (element < 0)
		{
			std::cout << "cannot add less than 0";
			return;
		}

		if (element > maxElement)
		{
			resize(element);
		}

		int bucket = getBucketIndex(element);
		int indexInBucket = getIndexInBucket(element);

		uint8_t mask = Constants::leftmostBit;
		mask = (mask >> indexInBucket);

		bitset[bucket] = (bitset[bucket] | mask);
	}

	void remove(int element)
	{
		if (element < 0 || element > maxElement)
		{
			std::cout << "invalid element";
			return;
		}

		int bucket = getBucketIndex(element);
		int indexInBucket = getIndexInBucket(element);

		uint8_t mask = Constants::leftmostBit;
		mask = (mask >> indexInBucket);

		mask = ~mask;
		bitset[bucket] = (bitset[bucket] & mask);
	}

	void intersectWith(const Set& other)
	{
		int otherBuckets = other.getBuckets();

		if (otherBuckets > buckets)
		{
			resize(other.getMaxElement());
		}

		const uint8_t* otherBitset = other.getBitset();

		for (int i = 0; i < std::min(buckets, otherBuckets); i++)
		{
			bitset[i] = (bitset[i] & otherBitset[i]);
		}

		if (buckets > otherBuckets)
		{
			for (int i = otherBuckets; i < buckets; i++)
			{
				bitset[i] = 0;
			}
		}
	}

	void unionWith(const Set& other)
	{
		int otherBuckets = other.getBuckets();

		if (otherBuckets > buckets)
		{
			resize(other.getMaxElement());
		}

		const uint8_t* otherBitset = other.getBitset();

		for (int i = 0; i < std::min(buckets, otherBuckets); i++)
		{
			bitset[i] = (bitset[i] | otherBitset[i]);
		}
	}

	void makeComplement()
	{
		for (int i = 0; i < buckets; i++)
		{
			bitset[i] = (~bitset[i]);
		}
	}

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

	void resize(int newMaxElement)
	{
		int newBuckets = calculateRequiredBuckets(newMaxElement);

		maxElement = newMaxElement;

		uint8_t* newBitset = new uint8_t[newBuckets]{ 0 };

		for (int i = 0; i < buckets; i++)
		{
			newBitset[i] = bitset[i];
		}

		buckets = newBuckets;

		delete[] bitset;
		bitset = newBitset;
	}

	int calculateRequiredBuckets(int maxElement) const
	{
		return maxElement / Constants::elementsInBucket + 1;
	}

	void initializeBitset(int maxElement)
	{
		buckets = calculateRequiredBuckets(maxElement);

		bitset = new uint8_t[buckets]{ 0 };
	}

	int getBucketIndex(int element) const
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
	Set s1(10);
	s1.add(4);
	s1.add(5);
	s1.add(6);
	s1.add(7);
	s1.add(8);

	Set s2(5);
	s2.add(7);
	s2.add(8);
	s2.add(9);

	s2.unionWith(s1);
	s2.print(); std::cout << std::endl;

	s2.makeComplement();
	s2.print();
}
