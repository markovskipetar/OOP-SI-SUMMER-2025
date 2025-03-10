#include <iostream>
#include <fstream>

namespace CONSTANTS
{
	constexpr int NUMS_IN_BYTE = 8;
}

namespace HELPER_FUNCTIONS
{
	unsigned int nextPowerOfTwo(unsigned n) 
	{
		if (n == 0)
		{
			return 1;
		}

		unsigned power = 1;
		while (power < n) 
		{
			power = power << 1;
		}

		return power;
	}
}

struct Set
{
private:
	uint8_t* buckets = nullptr;
	size_t limit = 0;
	size_t size = 0;

	int getSecondMax() const
	{
		int maxNum = getMax();
		for (int i = limit; i >= 0; i--)
		{
			if (hasElement(i) && i != maxNum)
			{
				return i;
			}
		}

		return -1;
	}

	size_t getBucketOf(unsigned el) const
	{
		return el / CONSTANTS::NUMS_IN_BYTE;
	}

	size_t getPositionOf(unsigned el) const
	{
		return el % CONSTANTS::NUMS_IN_BYTE;
	}

	size_t getNeededBucketsFor(unsigned el) const
	{
		size_t neededBuckets = el / CONSTANTS::NUMS_IN_BYTE;
		if (el % 8 != 0)
		{
			neededBuckets++;
		}

		return neededBuckets;
	}

	void deserialize(std::ifstream& inFile)
	{
		inFile.read((char*)&size, sizeof(size_t));
		
		buckets = new uint8_t[size];
		inFile.read((char*)buckets, size * sizeof(uint8_t));
		
		inFile.read((char*)&limit, sizeof(size_t));
	}

	void deserialize(const char* fileName)
	{
		if (!fileName)
		{
			return;
		}

		std::ifstream inFile(fileName, std::ios::binary);
		if (!inFile.is_open())
		{
			return;
		}

		deserialize(inFile);
		inFile.close();
	}

	void resize(size_t newSize)
	{

		uint8_t* newBuckets = new uint8_t[newSize]{};
		size_t elsToCopy = (size < newSize) ? size : newSize;

		for (size_t i = 0; i < elsToCopy; i++)
		{
			newBuckets[i] = buckets[i];
		}

		delete[] buckets;
		buckets = newBuckets;
		newBuckets = nullptr;

		size = newSize;
		limit = newSize * CONSTANTS::NUMS_IN_BYTE - 1;
	}

	void free()
	{
		delete[] buckets;
		limit = 0;
		size = 0;
	}

public:

	Set()
	{
		size = 8;
		buckets = new uint8_t[size]{}; // [0-63] 
		limit = size * CONSTANTS::NUMS_IN_BYTE - 1; //63
	}

	Set(const char* fileName)
	{
		deserialize(fileName);
	}

	bool addElement(unsigned el)
	{
		if (el > limit)
		{
			size_t neededBuckets = getNeededBucketsFor(el);
			size_t newSize = HELPER_FUNCTIONS::nextPowerOfTwo(neededBuckets);
			resize(newSize);
		}

		size_t bucket = getBucketOf(el);
		size_t pos = getPositionOf(el);
	
		if (!(buckets[bucket] & (1 << pos)))
		{
			buckets[bucket] |= (1 << pos);
			return true;
		}

		return false;
	}	

	bool deleteElement(unsigned el)
	{
		if (el == getMax())
		{
			int secondLimit = getSecondMax();
			if (secondLimit != -1)
			{
				size_t neededBuckets = getNeededBucketsFor(secondLimit);
				size_t newSize = HELPER_FUNCTIONS::nextPowerOfTwo(neededBuckets);

				std::cout << size << " " << newSize << std::endl;

				if (newSize != size)
				{
					resize(newSize);
				}
			}
		}

		size_t bucket = getBucketOf(el);
		size_t pos = getPositionOf(el);

		if (buckets[bucket] & (1 << pos))
		{
			buckets[bucket] &= ~(1 << pos);
			return true;
		}

		return false;
	}

	bool hasElement(unsigned el) const
	{
		if (el > limit)
		{
			return false;
		}

		size_t bucket = getBucketOf(el);
		size_t pos = getPositionOf(el);

		return ((buckets[bucket] & (1 << pos)) != 0);
	}

	int getMax() const
	{
		int maxNum = 0;
		for (int i = limit; i >= 0; i--)
		{
			if (hasElement(i))
			{
				return i;
			}
		}

		return -1;
	}

	void print() const
	{
		for (int i = 0; i <= limit; i++)
		{
			if (hasElement(i))
			{
				std::cout << i << " ";
			}
		}
	}

	void setUnion(const Set& other)
	{
		size_t maxLimit = (limit > other.getMax()) ? limit : other.getMax();;
		for (size_t i = 0; i <= maxLimit; i++)
		{
			if (hasElement(i) || other.hasElement(i))
			{
				addElement(i);
			}
		}
	}

	void setIntersection(const Set& other)
	{
		size_t minLimit = (limit < other.getMax()) ? limit : other.getMax();;
		for (size_t i = 0; i <= minLimit; i++)
		{
			if (hasElement(i) && other.hasElement(i))
			{
				addElement(i);
			}

			else if (hasElement(i))
			{
				deleteElement(i);
			}
		}
	}

	void serialize(std::ofstream& outFile)
	{
		outFile.write((const char*)&size, sizeof(size_t));
		outFile.write((const char*)buckets, size * sizeof(uint8_t));
		outFile.write((const char*)&limit, sizeof(size_t));
	}

	void serialize(const char* fileName)
	{
		if (!fileName)
		{
			return;
		}

		std::ofstream outFile(fileName, std::ios::binary);
		if (!outFile.is_open())
		{
			return;
		}

		serialize(outFile);
		outFile.close();
	}

	~Set()
	{
		free();
	}

};

int main()
{

	Set set;

	set.addElement(2);
	set.print();
	std::cout << std::endl;

	set.addElement(3);
	set.print();
	std::cout << std::endl;

	set.deleteElement(2);
	set.print();
	std::cout << std::endl;

	set.addElement(123);
	set.print();

	set.serialize("set.bin");

	Set set2("set.bin");
	set2.print();
	std::cout << std::endl;

	set2.addElement(5);
	set2.print();
	std::cout << std::endl;
	std::cout << set2.hasElement(5);

	std::cout << std::endl;
	std::cout << std::endl;

	set.setIntersection(set2);
	set.print();

	std::cout << std::endl;
	std::cout << std::endl;

	set.setUnion(set2);
	set.print();
	std::cout << std::endl;

	std::cout << set.getMax() << std::endl;
	set.deleteElement(123);

	return 0;
}