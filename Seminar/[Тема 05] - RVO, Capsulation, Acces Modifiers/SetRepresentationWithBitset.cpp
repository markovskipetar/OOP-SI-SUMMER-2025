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




























//constexpr int16_t blockSize = 32;
//constexpr int16_t endOfChainIndex = -1;
//
////struct Block
////{
////	int16_t next;
////	uint16_t length;
////	char text[28];
////};
////
////void prepareBinaryFile()
////{
////	std::ofstream ofs("blocks.dat", std::ios::binary);
////
////	Block b0{ 4,3 };
////	strcpy(b0.text, "C++");
////	ofs.write((const char*)&b0, sizeof(Block));
////
////	Block b1{ 0,6 };
////	strcpy(b1.text, "si-oop");
////	ofs.write((const char*)&b1, sizeof(Block));
////
////	Block b2{ 5,3 };
////	strcpy(b2.text, "The");
////	ofs.write((const char*)&b2, sizeof(Block));
////
////	Block b3{ 3,5 };
////	strcpy(b3.text, "Test");
////	ofs.write((const char*)&b3, sizeof(Block));
////
////	Block b4{ 2,2 };
////	strcpy(b4.text, "Is");
////	ofs.write((const char*)&b4, sizeof(Block));
////
////	Block b5{ -1,8 };
////	strcpy(b5.text, "Greatest");
////	ofs.write((const char*)&b5, sizeof(Block));
////
////	Block b6{ 2,5 };
////	strcpy(b6.text, "dummy");
////	ofs.write((const char*)&b6, sizeof(Block));
////}
//
//int getMessageLength(std::ifstream& ifs)
//{
//	int intitalIfsPosition = ifs.get();
//
//	int16_t nextBlockIndex = 0;
//	uint16_t currentMessageLength = 0;
//
//	int messageLength = 0;
//
//	while (true)
//	{
//		ifs.seekg(nextBlockIndex * blockSize);
//
//		ifs.read((char*)&nextBlockIndex, sizeof(int16_t));
//		ifs.read((char*)&currentMessageLength, sizeof(uint16_t));
//
//		messageLength += currentMessageLength;
//
//		if (nextBlockIndex == endOfChainIndex)
//		{
//			break;
//		}
//	}
//
//	ifs.seekg(intitalIfsPosition);
//
//	return messageLength;
//}
//
//const char* readMessage(int messageLength, std::ifstream& ifs)
//{
//	char* message = new char[messageLength + 1];
//	char* messageIterator = message;
//
//	int16_t nextBlockIndex = 0;
//	uint16_t currentMessageLength = 0;
//
//	while (true)
//	{
//		ifs.seekg(nextBlockIndex * blockSize);
//
//		ifs.read((char*)&nextBlockIndex, sizeof(int16_t));
//		ifs.read((char*)&currentMessageLength, sizeof(uint16_t));
//
//		ifs.read(messageIterator, currentMessageLength);
//		messageIterator += currentMessageLength;
//
//		if (nextBlockIndex == endOfChainIndex)
//		{
//			break;
//		}
//	}
//
//	message[messageLength] = '\0';
//
//	return message;
//}
//
//int main()
//{
//	std::ifstream ifs("blocks.dat", std::ios::binary);
//
//	if (!ifs.good())
//	{
//		std::cout << "error";
//		return -1;
//	}
//
//	int messageLength = getMessageLength(ifs);
//
//	const char* message = readMessage(messageLength, ifs);
//
//	std::cout << message;
//
//	delete message;
//}